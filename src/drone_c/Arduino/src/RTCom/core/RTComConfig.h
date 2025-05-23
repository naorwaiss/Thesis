// RTComConfig.h
#ifndef RTCOM_CONFIG_H
#define RTCOM_CONFIG_H

#include <vector>

#include <assert.h>

#include "SocketAddress.h"

// Default configuration values for various RTCom settings
#define RTCOM_CONFIG_DEFAULT_MAX_SESSIONS 1                       // Only 1 session is allowed at once
#define RTCOM_CONFIG_DEFAULT_PING_INTERVAL 100                    // Ping every 100 milliseconds
#define RTCOM_CONFIG_DEFAULT_PING_ABORT_TIMEOUT 200               // After 200 milliseconds, it aborts and retries ping
#define RTCOM_CONFIG_DEFAULT_SESSION_MAX_INACTIVITY_DURATION 500  // After 500 milliseconds of no activity, disconnect
#define RTCOM_CONFIG_DEFAULT_LIFECYCLE_INTERVAL 10000             // After 10 seconds run lifecycle checks

/// @brief Configuration structure for RTCom settings.
///
/// This structure holds either the maximum number of allowed sessions (`maxSessions`) or a list of allowed static addresses (`allowedStaticAddresses`),
/// but not both. If `maxSessions` is set, the number of sessions is limited. If `allowedStaticAddresses` is set, it defines the specific addresses
/// that are permitted to connect.
struct RTComConfig {
    /// @brief Maximum number of allowed sessions.
    ///
    /// If set to 0, this value is considered "not set". In this case,
    /// the `allowedStaticAddresses` must be provided.
    const unsigned short maxSessions = 0;

    /// @brief List of allowed static addresses.
    ///
    /// If this is set, the `maxSessions` value cannot be set (i.e., `maxSessions` must remain 0).
    /// This list defines the specific addresses that are permitted to connect and only those addresses.
    const std::vector<SocketAddress> allowedStaticAddresses = {};

    /// @brief Interval between pings in milliseconds (default is 100ms).
    const unsigned int pingInterval;

    /// @brief Timeout before aborting a ping if no response (default is 200ms).
    const unsigned int pingAbortTimeout;

    /// @brief Maximum allowed inactivity duration for a session before disconnecting (default is 500ms).
    const unsigned int sessionMaxInactivityDuration;

    const unsigned int lifecycleInterval;

    /// @brief Constructor to initialize the configuration with default or provided values.
    RTComConfig(
        const unsigned short maxSessions = RTCOM_CONFIG_DEFAULT_MAX_SESSIONS,
        const unsigned int pingInterval = RTCOM_CONFIG_DEFAULT_PING_INTERVAL,
        const unsigned int pingAbortTimeout = RTCOM_CONFIG_DEFAULT_PING_ABORT_TIMEOUT,
        const unsigned int sessionMaxInactivityDuration = RTCOM_CONFIG_DEFAULT_SESSION_MAX_INACTIVITY_DURATION,
        const unsigned int lifecycleInterval = RTCOM_CONFIG_DEFAULT_LIFECYCLE_INTERVAL)
        : maxSessions(maxSessions),
          pingInterval(pingInterval),
          pingAbortTimeout(pingAbortTimeout),
          sessionMaxInactivityDuration(sessionMaxInactivityDuration),
          lifecycleInterval(lifecycleInterval) {}

    /// @brief Constructor to initialize with a list of allowed static addresses along with other values.
    RTComConfig(
        const std::vector<SocketAddress> &allowedStaticAddresses,
        const unsigned int pingInterval = RTCOM_CONFIG_DEFAULT_PING_INTERVAL,
        const unsigned int pingAbortTimeout = RTCOM_CONFIG_DEFAULT_PING_ABORT_TIMEOUT,
        const unsigned int sessionMaxInactivityDuration = RTCOM_CONFIG_DEFAULT_SESSION_MAX_INACTIVITY_DURATION,
        const unsigned int lifecycleInterval = RTCOM_CONFIG_DEFAULT_LIFECYCLE_INTERVAL)
        : allowedStaticAddresses(allowedStaticAddresses),
          pingInterval(pingInterval),
          pingAbortTimeout(pingAbortTimeout),
          sessionMaxInactivityDuration(sessionMaxInactivityDuration),
          lifecycleInterval(lifecycleInterval) {}

    void validate() {
        assert((maxSessions > 0 || !allowedStaticAddresses.empty()) && "Either Max sessions must be a positive non-zero value, or must have at least one static address allowed.");
        assert(pingInterval < pingAbortTimeout && "Ping interval can't be longer or the same as the ping abort time.");
        assert(pingInterval < sessionMaxInactivityDuration && "Ping interval can't be longer or the same as the session max inactivity duration.");
    }
};

#endif  // RTCOM_CONFIG_H
