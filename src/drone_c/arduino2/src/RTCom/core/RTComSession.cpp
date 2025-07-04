#include "RTComSession.h"

#include <assert.h>

#include "../RTCom.h"

//! PUBLIC METHODS

RTComSession::RTComSession(SocketAddress &address, RTCom &rtcomSocket)
    : address(address), rtcomSocket(rtcomSocket), lastSignOfLifeTimestamp(millis()) {
    RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_CONNECTED, address.toString());
    sendPing();
}

void RTComSession::emit(const uint8_t *bytes, size_t size) {
    rtcomSocket.sendTo(bytes, size, address);
}

void RTComSession::emit(const char *dataBuffer) {
    rtcomSocket.sendTo(dataBuffer, address);
}

void RTComSession::emitTyped(const uint8_t *bytes, size_t size, uint8_t dataType) {
    rtcomSocket.sendToTyped(bytes, size, address, dataType);
}

void RTComSession::emitTyped(const char *dataBuffer, uint8_t dataType) {
    rtcomSocket.sendToTyped(dataBuffer, address, dataType);
}

void RTComSession::onReceive(const OnReceiveCallback &onReceiveCallback) {
    onReceiveRawCallback = onReceiveCallback;
}

void RTComSession::on(uint8_t dataType, const OnReceiveCallback &onReceiveCallback) {
    onReceiveTypedRegisters[dataType] = onReceiveCallback;
}

void RTComSession::onDefault(const OnReceiveCallback &onReceiveCallback) {
    onDefaultReceiveRegister = onReceiveCallback;
}

void RTComSession::onPingChange(const OnPingChangeCallback &onPingChangeCallback) {
    this->onPingChangeCallback = onPingChangeCallback;
}

void RTComSession::onDisconnect(const OnDisconnectCallback &onDisconnectCallback) {
    this->onDisconnectCallback = onDisconnectCallback;
}

RTComSession::~RTComSession() {
    RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_DISCONNECT, address.toString(), getLastSignOfLife());
}

//! PRIVATE FRIENDLY

void RTComSession::callOnReceive(const uint8_t *bytes, size_t size) {
    if (onReceiveRawCallback != nullptr)
        onReceiveRawCallback(bytes, size);
}

void RTComSession::callOnDefault(const uint8_t *bytes, size_t size) {
    if (onDefaultReceiveRegister != nullptr) {
        onDefaultReceiveRegister(bytes, size);
    }
}

void RTComSession::handlePingSendRoutine(unsigned int pingInterval, unsigned int pingAbortTimeout) {
    uint32_t now = millis();

    // `pingDelayTimestamp` is 0 only when in the process of sending a ping
    if (pingDelayTimestamp != 0) {
        if (now - pingDelayTimestamp > pingInterval)
            sendPing();
    } else if (now - pingTimestamp > pingAbortTimeout) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_PING_ABORT, address.toString());
        sendPing();
    }
}

void RTComSession::receivedPong(uint8_t pongSequence) {
    if (pingSequence != pongSequence) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_WRONG_PING_SEQ, address.toString(), pingSequence, pongSequence);
        return;
    }

    uint32_t now = millis();

    // Get the successful ping time
    uint32_t pingTime = now - pingTimestamp;

    // Set ping delay timestamp of the current timestamp
    pingDelayTimestamp = now;

    // If first ping set all `pingAvg` cells to it, else, set on cell index and cycle.
    if (firstPing) {
        firstPing = false;
        std::fill(pingAvg, pingAvg + RTCOM_SESSION_PING_AVG_MEASURE_SIZE, pingTime);
    } else {
        pingAvg[currentPingAvgIndex] = pingTime;
        currentPingAvgIndex = (currentPingAvgIndex + 1) % RTCOM_SESSION_PING_AVG_MEASURE_SIZE;
    }

    // Set `ping` to the new average ping
    int pingSum = 0;
    for (int i = 0; i < RTCOM_SESSION_PING_AVG_MEASURE_SIZE; i++)
        pingSum += pingAvg[i];

    int newPing = pingSum / RTCOM_SESSION_PING_AVG_MEASURE_SIZE;

    // If ping changed and onPingChangeCallback was set
    if (ping != newPing && onPingChangeCallback != nullptr) {
        RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_PING_CHANGE, address.toString(), newPing);
        onPingChangeCallback(newPing);
    }

    ping = newPing;
}

unsigned int RTComSession::getLastSignOfLife() {
    return millis() - lastSignOfLifeTimestamp;
}

void RTComSession::updateLastSignOfLife() {
    lastSignOfLifeTimestamp = millis();
}

void RTComSession::handleReconnect() {
    RTCOM_DEBUG_PRINT(RTCOM_DEBUG_SESSION_RECONNECTED, address.toString());
    sendPing();
}

//! PRIVATE METHODS

void RTComSession::sendPing() {
    // Sends ping to session address, pingSequence++ to get 0 to 255 wrapping with bit overflow
    rtcomSocket.pingTo(address, ++pingSequence);

    // Measure time after sending the ping.
    pingTimestamp = millis();

    // Set the delay between each ping to 0 to indicate its waiting for a pong response
    pingDelayTimestamp = 0;
}
