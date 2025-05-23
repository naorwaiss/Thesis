#include "RTCom.h"

#include <assert.h>

namespace qn = qindesign::network;

qn::EthernetUDP Udp(RTCOM_UDP_PACKETS_QUEUE_SIZE);

//! PUBLIC METHODS

RTCom::RTCom(const SocketAddress &bindAddress, const RTComConfig &config)
    : bindAddress(bindAddress), config(config) {
    RTComUtils::getTeensyMAC(macAddress);
    lastLifecycleUpdate = millis();
}

void RTCom::begin() {
    config.validate();
    beginEthernet();
}

void RTCom::process() {
    // Get the most recent incoming packet if available and handle it
    getAndHandleIncomingPacket();

    RTComSession *pSession;
    std::map<SocketAddress, RTComSession *>::iterator sessionsIterator;
    for (sessionsIterator = sessions.begin(); sessionsIterator != sessions.end();) {
        pSession = sessionsIterator->second;
        // If the session's last sign of life is older than the maximum allowed inactivity duration, disconnect and remove the session.
        // Otherwise, handle the session's ping routine and move to the next session.
        if (pSession->getLastSignOfLife() > config.sessionMaxInactivityDuration) {
            sessionsIterator = disconnectSessionIterator(sessionsIterator);
        } else {
            sessionsIterator->second->handlePingSendRoutine(config.pingInterval, config.pingAbortTimeout);
            ++sessionsIterator;
        }
    }

    // Check if it is time to update the lifecycle, if it is set new time to `lastLifecycleUpdate`
    const uint32_t now = millis();
    if (now - lastLifecycleUpdate > config.lifecycleInterval) {
        updateLifecycle();
        lastLifecycleUpdate = now;
    }
}

void RTCom::sendTo(const uint8_t *bytes, size_t size, SocketAddress &address) {
    sendPacket(bytes, size, address, RTComPacketType::RAW);
}

void RTCom::sendTo(const char *dataBuffer, SocketAddress &address) {
    // Calculates the size of the null-terminated string
    size_t size = strlen(dataBuffer);

    // Creates a byte array to hold the string data
    uint8_t bytes[size];

    // Copies the string data into the byte array
    memcpy(bytes, dataBuffer, size);

    // Sends the byte array as a RAW packet to the specified address
    sendPacket(bytes, size, address, RTComPacketType::RAW);
}

void RTCom::sendToTyped(const uint8_t *bytes, size_t size, SocketAddress &address, uint8_t dataType) {
    // Creates a new byte array with size + 1 to accommodate the `dataType` byte
    uint8_t newBytes[size + 1];

    // Sets the first byte to the dataType (preceding the data payload)
    newBytes[0] = dataType;

    // Copies the original bytes starting from the second byte of the new array
    memcpy(newBytes + 1, bytes, size);

    // Sends the new byte array with the dataType byte at the beginning
    sendPacket(newBytes, size + 1, address, RTComPacketType::TYPED);
}

void RTCom::sendToTyped(const char *dataBuffer, SocketAddress &address, uint8_t dataType) {
    // Calculates the size of the null-terminated string
    size_t size = strlen(dataBuffer);

    // Creates a new byte array with size + 1 to accommodate the `dataType` byte
    uint8_t bytes[size + 1];

    // Sets the first byte to the dataType (preceding the data payload)
    bytes[0] = dataType;

    // Copies the string data into the byte array starting from the second byte of the new array
    memcpy(bytes + 1, dataBuffer, size);

    // Sends the new byte array with the dataType byte at the beginning
    sendPacket(bytes, size + 1, address, RTComPacketType::TYPED);
}

void RTCom::onConnection(const OnConnectionCallback &onConnectionCallback) {
    this->onConnectionCallback = onConnectionCallback;
}

void RTCom::pingTo(SocketAddress &address, uint8_t pingSequence) {
    // Send ping
    uint8_t pingData[] = {RTComCONType::PING, pingSequence};
    sendPacket(pingData, sizeof(pingData), address, RTComPacketType::CONNECTION);
}

bool RTCom::isSessionConnected(RTComSession *pSession) {
    if (pSession == nullptr)
        return false;
    return findSession(pSession) != sessions.end();
}

bool RTCom::disconnectSession(RTComSession *pSession) {
    size_t sessionsCount = sessions.size();
    disconnectSessionIterator(findSession(pSession));
    return sessions.size() < sessionsCount;
}

RTCom::~RTCom() {
    // Free up all sessions from memory
    std::map<SocketAddress, RTComSession *>::iterator sessionsIterator;
    for (sessionsIterator = sessions.begin(); sessionsIterator != sessions.end();)
        delete sessionsIterator->second;
    sessions.clear();
}

//! PRIVATE METHODS

void RTCom::beginEthernet() {
    // Assert if already initialized
    assert(!rtcomBegan && "RTCom Already initialized.");

    // Checking if an ethernet connection can be made (hardware-wise).
    while (!RTComUtils::hasPhysicalEthernet()) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_NO_ETHERNET);
        delay(1000);  // Small delay to avoid log flooding and give time for hardware check
    }

    // Attempting to initialize Ethernet connection
    while (!qn::Ethernet.begin(bindAddress.ip, qn::Ethernet.subnetMask(), qn::Ethernet.gatewayIP())) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_ETHERNET_FAIL);
        delay(1000);  // Small delay to avoid log flooding and give time to retry connection
    }

    // UDP setup
    Udp.begin(bindAddress.port);
    rtcomBegan = true;

    RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SERVER_BEGIN, bindAddress.port);
#ifdef RTCOM_DEBUG_MODE
    RTComUtils::printNetworkInfo();  // Print network info if in debug mode
#endif
}

void RTCom::getAndHandleIncomingPacket() {
    int packetSize;  // This will only be -1(`RTCOM_NO_PACKET_SIZE`) when there is no packet
    while ((packetSize = Udp.parsePacket()) != RTCOM_NO_PACKET_SIZE) {
        // Get packet address
        SocketAddress remoteAddress = SocketAddress(Udp.remoteIP(), Udp.remotePort());

        // Get packet data
        const uint8_t *packetData = Udp.data();
        if (packetData == NULL)
            continue;

        // Check if address is a session one
        SessionsIterator sessionIterator = sessions.find(remoteAddress);

        // No such sesson exists
        if (sessionIterator == sessions.end()) {
            if (packetSize == RTCOM_CONNECTION_PACKET_SIZE)  // The packet size to establish a connection
                handleUnknownPacket(remoteAddress, packetData, packetSize);
        } else {
            handleSessionPacket(*sessionIterator->second, packetData, packetSize);
        }
    }

    // Makes sure the packet queue is cleared
    Udp.flush();
}

void RTCom::handleUnknownPacket(SocketAddress &address, const uint8_t *data, size_t size) {
    // If cannot create a session do nothing
    if (!canCreateSession(address))
        return;

    // If the packet is not from a session, only process connection-related packets (e.g., SYN, SYN-ACK, ACK).
    if (data[0] != RTComPacketType::CONNECTION)
        return;

    uint8_t connectionProtocolType = data[1];

    // Received SYN
    if (connectionProtocolType == RTComCONType::HANDSHAKE_SYN) {
        // Send SYN_ACK
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_CONNECTION_RECV_SYN, address.toString());
        sendCON(RTComCONType::HANDSHAKE_SYN_ACK, address);

        // Start time for when sent
        ackPendingAddresses.insert(std::pair(address, millis()));
        return;
    }

    // Received ACK
    if (connectionProtocolType == RTComCONType::HANDSHAKE_ACK) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_CONNECTION_RECV_ACK, address.toString());
        // Check for a ACK pending in that address
        auto ackPendingIterator = ackPendingAddresses.find(address);
        if (ackPendingIterator == ackPendingAddresses.end())  // No ACK pending found in that address
            return;

        // Get the ACK timeout
        uint32_t ackTimeout = millis() - ackPendingIterator->second;

        // If the current time is within the timeout period, create a session between them,
        // remove the address from `ackPendingAddresses`, and invoke `onConnectionCallback` if assigned.
        // Otherwise, if the ACK response took too long, treat it as a SYN and resend the SYN-ACK handshake.
        if (ackTimeout < RTCOM_CONNECTION_HANDSHAKE_TIMEOUT) {
            // CREATE A NEW SESSION USING HEAP MEMORY
            RTComSession *session = new RTComSession(address, *this);

            // Insert session to sessions paired with its address
            sessions.insert(std::pair(address, session));

            // Remove address from the ack pending addresses
            ackPendingAddresses.erase(address);

            // If there is an on connection callback assigned call it with the newly created session
            if (onConnectionCallback != nullptr)
                onConnectionCallback(*session);
        } else {
            RTCOM_DEBUG_PRINT(RTCOM_DEBUG_CONNECTION_RECV_ACK_TIMED_OUT, address.toString(), ackTimeout, RTCOM_CONNECTION_HANDSHAKE_TIMEOUT);

            // Treat the failed ACK as a SYN and resend SYN-ACK
            sendCON(RTComCONType::HANDSHAKE_SYN_ACK, address);

            // Restart the time
            ackPendingAddresses[address] = millis();
        }
    }
}

void RTCom::handleSessionPacket(RTComSession &session, const uint8_t *data, size_t size) {
    // Set new last sign of life for every received packet from session
    session.updateLastSignOfLife();

    uint8_t packetType = data[0];
    if (packetType == RTComPacketType::CONNECTION) {
        switch (data[1]) {
            case RTComCONType::PONG:  // Received pong
                session.receivedPong(data[2]);
                return;

            case RTComCONType::HANDSHAKE_SYN:  // Trying to connected when already connected
                sendCON(RTComCONType::HANDSHAKE_SYN_ACK, session.address);
                return;

            case RTComCONType::HANDSHAKE_ACK:  // Reconnected
                session.handleReconnect();
                return;

            default:
                // unsupported/invalid connection type 
                return;
        }
    } else if (packetType == RTComPacketType::RAW) {
        // Call on receive callback with the data after packet type
        session.callOnReceive(data + 1, size - 1);
    } else if (packetType == RTComPacketType::TYPED) {
        // If packet type is of typed packet, call registered callback if exists or
        // onDefault if not with data after the packet and data types
        if (size == 1)
            return;
        uint8_t dataType = data[1];
        if (session.onReceiveTypedRegisters[dataType] != nullptr)
            session.onReceiveTypedRegisters[dataType](data + 2, size - 2);
        else {
            session.callOnDefault(data + 2, size - 2);
        }
    }
    //* If not of type CONNECTION/RAW/TYPED, then consider the packet as invalid and ignore it.
}

void RTCom::sendPacket(const uint8_t *bytes, size_t size, SocketAddress &address, const RTComPacketType &packetType) {
    Udp.beginPacket(address.ip, address.port);
    Udp.write(packetType);
    Udp.write(bytes, size);
    Udp.endPacket();
}

void RTCom::sendCON(RTComCONType conType, SocketAddress &address) {
    uint8_t conData[] = {conType};
    sendPacket(conData, 1, address, RTComPacketType::CONNECTION);
}

bool RTCom::canCreateSession(SocketAddress &address) const {
    // Check if `maxSessions` is set (non-zero). If it is 0, it means it is not set, so move to `allowedStaticAddresses`.
    if (config.maxSessions != 0)
        return sessions.size() < config.maxSessions;

    // If `maxSessions` is not set then check if address is in the allowed static IPs list
    for (const SocketAddress &addr : config.allowedStaticAddresses) {
        if (addr == address)
            return true;  // Address is allowed
    }
    return false;  // Address is not allowed
}

void RTCom::updateLifecycle() {
    const uint32_t now = millis();
    uint32_t ackTimeout;
    std::map<SocketAddress, uint32_t>::iterator ackIterator;
    for (ackIterator = ackPendingAddresses.begin(); ackIterator != ackPendingAddresses.end();) {
        ackTimeout = now - ackIterator->second;
        if (ackTimeout > RTCOM_CONNECTION_HANDSHAKE_TIMEOUT) {
            // Removes from the ack pending addresses
            RTCOM_DEBUG_PRINT(RTCOM_DEBUG_LIFECYCLE_ACK_TIMED_OUT_CLEAR, ackIterator->first.toString());
            ackIterator = ackPendingAddresses.erase(ackIterator);
        } else {
            ++ackIterator;
        }
    }
}

SessionsIterator RTCom::findSession(RTComSession *pSession) {
    return sessions.find(pSession->address);
}

SessionsIterator RTCom::disconnectSessionIterator(SessionsIterator sessionsIterator) {
    if (sessionsIterator == sessions.end())
        return sessionsIterator;
    RTComSession *pSession = sessionsIterator->second;
    if (pSession == nullptr)
        return sessionsIterator;

    if (pSession->onDisconnectCallback != nullptr)
        pSession->onDisconnectCallback();

    // Send disconnect msg
    sendCON(RTComCONType::TERMINATE, pSession->address);

    // Free session from memory
    delete pSession;

    // Remove the session and return the next sessions iterator
    return sessions.erase(sessionsIterator);
}
