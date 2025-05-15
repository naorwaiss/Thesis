// RTComSession.h
#ifndef RTCOM_SESSION_H
#define RTCOM_SESSION_H

#include <vector>
#include <functional>

#include "SocketAddress.h"

#define RTCOM_SESSION_NUMBER_OF_RECEIVE_TYPED_REGISTERS 255
#define RTCOM_SESSION_PING_AVG_MEASURE_SIZE 5

class RTCom;  // Forward declaration of RTCom class

using OnReceiveCallback = std::function<void(const uint8_t *bytes, size_t size)>;
using OnPingChangeCallback = std::function<void(const uint16_t ping)>;
using OnDisconnectCallback = std::function<void()>;

class RTComSession {
   public:
    /// @brief Socket Address.
    SocketAddress address;

    /// @brief Array of 255 registers to callbacks for every first byte data type.
    OnReceiveCallback onReceiveTypedRegisters[RTCOM_SESSION_NUMBER_OF_RECEIVE_TYPED_REGISTERS] = {nullptr};

    /// @brief On disconnect callback.
    OnDisconnectCallback onDisconnectCallback = nullptr;

    /// @brief Ping with session, measured as an average of the last `RTCOM_SESSION_PING_AVG_MEASURE_SIZE` pings.
    uint16_t ping = 0;

    /// @brief Initializes a session with the given address.
    /// @param address The session address reference.
    /// @param rtcomSocket The RTCom socket instance reference.
    RTComSession(SocketAddress &address, RTCom &rtcomSocket);

    /// @brief Sends raw data to the session address.
    /// @param bytes A pointer to a raw array of unsigned bytes to be sent.
    /// @param size The number of bytes in the array.
    void emit(const uint8_t *bytes, size_t size);

    /// @brief Sends the given null-terminated string to the session address.
    /// @param dataBuffer Null-terminated string to send.
    void emit(const char *dataBuffer);

    /// @brief Sends byte data to the session address with additional type information.
    /// @param bytes A pointer to a raw array of unsigned bytes to be sent.
    /// @param size The number of bytes in the array.
    /// @param dataType An identifier for the type of data being emitted.
    void emitTyped(const uint8_t *bytes, size_t size, uint8_t dataType);

    /// @brief Sends a null-terminated string to the session address with additional type information.
    /// @param dataBuffer Null-terminated string to send.
    /// @param dataType An identifier for the type of data being emitted.
    void emitTyped(const char *dataBuffer, uint8_t dataType);

    void onReceive(const OnReceiveCallback &onReceiveCallback);

    /// @brief Registers a callback for handling received data of a specific type.
    /// @param dataType The type of data to listen for.
    /// @param onReceiveCallback The callback function to invoke when data of the specified type is received.
    /// The callback should match the signature: `void callback(const uint8_t *bytes, size_t size);`
    void on(uint8_t dataType, const OnReceiveCallback &onReceiveCallback);

    /// @brief Registers a default callback for handling data when no specific type is matched.
    /// @param onReceiveCallback The callback function to invoke when no matching data type has a callback.
    /// The callback should match the signature: `void callback(const uint8_t *bytes, size_t size);`
    void onDefault(const OnReceiveCallback &onReceiveCallback);

    /// @brief Sets the callback function that will get triggered on ping change.
    /// @param onPingChangeCallback Callback function passed with the updated ping.
    void onPingChange(const OnPingChangeCallback &onPingChangeCallback);

    /// @brief Sets the callback function triggered on session disconnect.
    /// @param onDisconnectCallback Callback function passed.
    void onDisconnect(const OnDisconnectCallback &onDisconnectCallback);

    /// @brief Destructor of session from memory.
    ~RTComSession();

    //! PRIVATE FRIENDLY METHODS (should be later implemented in such way that are not accessible to the session).

    /// @brief Sets a callback function triggered on receiving raw packets with no type.
    /// @param bytes A pointer to a raw array of unsigned bytes to be sent.
    /// @param size The number of bytes in the array.
    void callOnReceive(const uint8_t *bytes, size_t size);

    /// @brief Sets a callback function triggered on receiving typed packet that is not registered.
    /// @param bytes A pointer to a raw array of unsigned bytes to be sent.
    /// @param size The number of bytes in the array.
    void callOnDefault(const uint8_t *bytes, size_t size);

    /// @brief Manages periodic Ping sending and retries if needed.
    ///
    /// Sends a Ping if the ping interval has passed or if the previous ping was aborted.
    ///
    /// @param pingInterval Time between consecutive pings in milliseconds.
    /// @param pingAbortTimeout Timeout after which a ping is considered aborted.
    void handlePingSendRoutine(unsigned int pingInterval, unsigned int pingAbortTimeout);

    /// @brief Handles the reception of a Pong message and updates the round-trip time (RTT) metrics.
    ///
    /// This function is called when a Pong message is received. It verifies that the sequence number of
    /// the Pong message matches the expected sequence number. The function calculates the round-trip time
    /// based on the time difference between when the Ping was sent and the Pong was received, updates
    /// the average ping time, and triggers a callback if the ping value has changed.
    ///
    /// @param pongSequence The sequence number of the received Pong message. This should match the sequence
    /// number of the corresponding Ping message to ensure correct pairing.
    void receivedPong(uint8_t pongSequence);

    /// @brief The time passed since the last sign of life.
    /// @return The passed time in milliseconds since the last sign of life.
    unsigned int getLastSignOfLife();

    /// @brief Updates `lastSignOfLifeTimestamp` to the current time.
    void updateLastSignOfLife();

    /// @brief Handle reconnected session.
    void handleReconnect();

    //! add received ping also when using as client

   private:
    /// @brief RTCom socket reference.
    RTCom &rtcomSocket;

    /// @brief On receiving raw packets.
    OnReceiveCallback onReceiveRawCallback = nullptr;

    /// @brief Default receive register callback if not matched on the registers.
    OnReceiveCallback onDefaultReceiveRegister = nullptr;

    /// @brief On ping change callback with the updated ping value.
    OnPingChangeCallback onPingChangeCallback = nullptr;

    /// @brief Timestamp after sending a ping.
    uint32_t pingTimestamp = 0;

    /// @brief Ping sequence number ranging from 0-255 to insure pong on the corresponding ping message.
    uint8_t pingSequence = 0;

    /// @brief The ping delay timestamp after every succesful ping, 0 when waiting for ping response (pong).
    uint32_t pingDelayTimestamp = 0;

    /// @brief Average ping out of the successful pings.
    uint32_t pingAvg[RTCOM_SESSION_PING_AVG_MEASURE_SIZE] = {0};

    /// @brief Index to assign the ping time to on the average array.
    uint8_t currentPingAvgIndex = 0;

    /// @brief Setting the first session ping to set all the pingAvg values to it.
    bool firstPing = true;

    /// @brief Stores the timestamp for every receive from the session to check if disconnected.
    uint32_t lastSignOfLifeTimestamp = 0;

    /// @brief Sends a ping to the session address.
    void sendPing();
};

#endif  // RTCOM_SESSION_H