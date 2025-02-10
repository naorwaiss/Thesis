// RTCom.h
#ifndef RTCOM_H
#define RTCOM_H

#include <Arduino.h>
#include <QNEthernet.h>

#include <map>
#include <vector>

#include "core/SocketAddress.h"
#include "core/RTComUtils.h"
#include "core/RTComConfig.h"
#include "core/RTComSession.h"
#include "core/RTComDebug.h"


#define RTCOM_UDP_TX_PACKET_MAX_SIZE 4096  // 4 KB buffer size
#define RTCOM_UDP_PACKETS_QUEUE_SIZE 100   // 100 packets on queue before reading them

#define RTCOM_NO_PACKET_SIZE -1                  // No packet returns -1
#define RTCOM_CONNECTION_PACKET_SIZE 2           // The packet size to establish a connection
#define RTCOM_CONNECTION_HANDSHAKE_TIMEOUT 1500  // Waits a 1.5 seconds before aborting the syn-ack connection

using SessionsIterator = std::map<SocketAddress, RTComSession *>::iterator;

using OnConnectionCallback = void (*)(RTComSession &session);

/// @brief RTCom packet types `CONNECTION/RAW/TYPED`.
///
/// This is the first byte on the payload to indicate the RTCom packet type.
enum RTComPacketType {
    CONNECTION = 0x01,  // Reserved for connection type messages
    RAW = 0x02,         // Reserved for sending raw data
    TYPED = 0x03        // Reserved for sending typed data
};

/// @brief RTCom connection packet types.
///
/// This is all the connection types that follows the `RTComPacketType::CONNECTION` first byte.
enum RTComCONType {
    HANDSHAKE_SYN = 0x01,
    HANDSHAKE_SYN_ACK = 0x02,
    HANDSHAKE_ACK = 0x03,
    PING = 0x10,
    PONG = 0x11,
    TERMINATE = 0xFF
};

/// @brief RTCom - Real-Time Communication.
class RTCom {
   public:
    /// @brief The RTCom bind address <`SocketAddress`>.
    const SocketAddress &bindAddress;

    /// @brief The RTCom bind MAC address <`uint8_t[6]`>.
    uint8_t macAddress[6];

    /// @brief
    /// @param bindAddress the socket address <`SocketAddress`> to bind the RTCom.
    /// @param config RTCom Configuration.
    RTCom(const SocketAddress &bindAddress, const RTComConfig &config = RTComConfig());

    /// @brief Initializing Ethernet with the constructed address and validates config parameters.
    void begin();

    /// @brief Processes RTCom operations by retrieving and handling the most recent incoming packet,
    /// and performing lifecycle updates.
    ///
    /// This method first calls `getAndHandleIncomingPacket` to check for and handle any incoming packets.
    /// It then calls `updateLifecycle` every few seconds to manage lifecycle-related tasks and cleanups.
    void process();

    /// @brief Sends the given bytes to the specified address, regardless of whether a session is established.
    /// @param bytes Raw array of unsigned bytes to send.
    /// @param size The array size.
    /// @param address The address to send the packet to.
    void sendTo(const uint8_t *bytes, size_t size, SocketAddress &address);

    /// @brief Sends the given null-terminated string to the specified address, regardless of whether a session is established.
    /// @param dataBuffer Null-terminated string to send.
    /// @param address The address to send the packet to.
    void sendTo(const char *dataBuffer, SocketAddress &address);

    /// @brief Sends the given bytes to the specified address with a specific send data type, regardless of whether a session is established.
    /// @param bytes Raw array of unsigned bytes to send.
    /// @param size The array size.
    /// @param address The address to send the packet to.
    /// @param dataType An identifier for the type of data being sent.
    void sendToTyped(const uint8_t *bytes, size_t size, SocketAddress &address, uint8_t dataType);

    /// @brief Sends the given null-terminated string to the specified address with a specific data type, regardless of whether a session is established.
    /// @param dataBuffer Null-terminated string to send.
    /// @param address The address to send the packet to.
    /// @param dataType An identifier for the type of data being sent.
    void sendToTyped(const char *dataBuffer, SocketAddress &address, uint8_t dataType);

    /// @brief On connection callback that returns the the `OnConnectionCallback` with the newly created session.
    /// @param onConnectionCallback
    void onConnection(const OnConnectionCallback &onConnectionCallback);

    /// @brief Sends a ping to the given address.
    /// @param address The address it pings to.
    /// @param pingSequence The ping sequence to identify the ping.
    void pingTo(SocketAddress &address, uint8_t pingSequence);

    /// @brief Returns whether the given session pointer is a session and is connected.
    /// @param pSession The session pointer.
    /// @return True only if `pSession` is pointing to an actual session that is also connected.
    bool isSessionConnected(RTComSession *pSession);

    /// @brief Disconnects given session if has such session.
    /// @param pSession RTCom Session pointer to delete.
    /// @return True if session was deleted, otherwise, returns false.
    bool disconnectSession(RTComSession *pSession);

    /// @brief Destructor responsible for freeing sessions from memory.
    ~RTCom();

   private:
    bool rtcomBegan = false;
    RTComConfig config;
    std::map<SocketAddress, uint32_t> ackPendingAddresses = {};
    std::map<SocketAddress, RTComSession *> sessions = {};

    OnConnectionCallback onConnectionCallback = nullptr;

    uint32_t lastLifecycleUpdate;

    /// @brief Initializing Ethernet.
    void beginEthernet();

    /// @brief Retrieves the most recent incoming packet if available, processes it by calling relevant handlers, and then clears the buffer.
    ///
    /// This method invokes handlers such as `handleUnknownPacket` and `handleSessionPacket` to process the packet.
    void getAndHandleIncomingPacket();

    /// @brief Handles a packet that is not registered.
    /// @param address Packet address.
    /// @param data Pointer to packet data in bytes <`uint8_t`>.
    /// @param size The size of the data.
    void handleUnknownPacket(SocketAddress &address, const uint8_t *data, size_t size);

    /// @brief Handles a packet that in a session.
    /// @param session Session Object.
    /// @param data Pointer to packet data in bytes <`uint8_t`>.
    /// @param size The size of the data.
    void handleSessionPacket(RTComSession &session, const uint8_t *data, size_t size);

    /// @brief Sends a packet of bytes to an address.
    /// @param bytes Raw array of unsigned bytes to send.
    /// @param size The array size.
    /// @param address The address to send the packet to.
    /// @param packetType The packet type `CONNECTION/RAW/TYPED`.
    ///
    /// This method is the core packet sending method, all packets sends & emits use this.
    ///
    /// Note: this method should not be used outside of the `RTCom` class.
    void sendPacket(const uint8_t *bytes, size_t size, SocketAddress &address, const RTComPacketType &packetType);

    /// @brief Quick way of sending a packet of type `CONNECTION`.
    /// @param conType Connection type of the packet to send.
    /// @param address Address to send the connection packet to.
    ///
    /// Note: this method should not be used outside of the `RTCom` class.
    void sendCON(RTComCONType conType, SocketAddress &address);

    /// @brief Checks if a session can be created with the given address.
    ///
    /// This method verifies whether a session can be created by checking if the maximum number of sessions has been reached
    /// or if the address is in the list of allowed static IPs.
    ///
    /// @param address The socket address to check.
    /// @return True if a session can be created with this address, meaning either the maximum number of sessions has not
    /// been reached or the address is an allowed static IP.
    bool canCreateSession(SocketAddress &address) const;

    /// @brief Updates the RTCom lifecycle by cleaning up unnecessary memory from disconnected sessions and handling late ACK pending addresses.
    void updateLifecycle();

    /// @brief Finds the given session pointer in the `sessions` map and returns an iterator (`SessionsIterator`) to the session if found.
    /// If not found, the iterator will be equal to `sessions.end()`.
    /// @param pSession A pointer to the session to search for.
    /// @return An iterator (`SessionsIterator`) pointing to the found session, or `sessions.end()` if not found.
    SessionsIterator findSession(RTComSession *pSession);

    /// @brief Disconnects the session pointed to by the given iterator in the `sessions` map.
    /// @param sessionsIterator An iterator pointing to the session to disconnect.
    /// @return The iterator pointing to the next session after disconnecting, or the original iterator if no session was disconnected.
    SessionsIterator disconnectSessionIterator(SessionsIterator sessionsIterator);
};

#endif  // RTCOM_H
