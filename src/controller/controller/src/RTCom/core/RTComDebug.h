// RTComDebug.h
#ifndef RTCOM_DEBUG_H
#define RTCOM_DEBUG_H

#ifdef RTCOM_DEBUG_MODE
  // If debug mode is enabled, define RTCOM_DEBUG_PRINT to print formatted messages.
  #define RTCOM_DEBUG_PRINT(msg, ...) Serial.printf("[RTCom] " msg, ##__VA_ARGS__)
#else
  // If debug mode is not enabled, define RTCOM_DEBUG_PRINT as a no-op.
  #define RTCOM_DEBUG_PRINT(msg, ...)
#endif

#define RTCOM_DEBUG_NO_ETHERNET "No physical Ethernet connection detected (Ethernet shield was not found).\r\n"
#define RTCOM_DEBUG_ETHERNET_FAIL "Failed to configure Ethernet with the provided IP, subnet, or gateway. Retrying...\r\n"
#define RTCOM_DEBUG_SERVER_BEGIN "Server started on port: %d.\r\n"
#define RTCOM_DEBUG_LIFECYCLE_ACK_TIMED_OUT_CLEAR "*Lifecycle* CLEARED TIMED OUT {_ACK_} PENDING ADDRESS %s.\r\n"
#define RTCOM_DEBUG_CONNECTION_RECV_SYN "\b\b::Connection(%s)] RECEIVED {_SYN_}, Sending {_SYN_ACK_}...\r\n"
#define RTCOM_DEBUG_CONNECTION_RECV_ACK "\b\b::Connection(%s)] RECEIVED {_ACK_}, validating & creating session...\r\n"
#define RTCOM_DEBUG_CONNECTION_RECV_ACK_TIMED_OUT "\b\b::Connection(%s)] RECEIVED {_ACK_} ~TIMED OUT~ (%dms > %dms) Resending {_SYN_ACK_}...\r\n"
#define RTCOM_DEBUG_SESSION_CONNECTED "\b\b::Session(%s)] CONNECTED.\r\n"
#define RTCOM_DEBUG_SESSION_RECONNECTED "\b\b::Session(%s)] RECONNECTED.\r\n"
#define RTCOM_DEBUG_SESSION_PING_CHANGE "\b\b::Session(%s)] PING CHANGE, ping=%d\r\n"
#define RTCOM_DEBUG_SESSION_PING_ABORT "\b\b::Session(%s)] PING ABORTED, re-pinging...\r\n"
#define RTCOM_DEBUG_SESSION_WRONG_PING_SEQ "\b\b::Session(%s)] NOT THE SAME PING SEQUANCE: %d <-> %d\r\n"
#define RTCOM_DEBUG_SESSION_DISCONNECT "\b\b::Session(%s)] DISCONNECTED (last_sign_of_life=%d).\r\n"


#endif  // RTCOM_DEBUG_H
