// SocketAddress.h
#ifndef SOCKET_ADDRESS_H
#define SOCKET_ADDRESS_H

#include <cstdio>

#include <IPAddress.h>

/// @brief Represents a socket address with IP:PORT.
struct SocketAddress {
    const IPAddress ip;
    const uint16_t port;

    /// @brief Constructs a `SocketAddress`.
    /// @param ip IP address of type `IPAddress`.
    /// @param port Port number of type `uint16_t`.
    SocketAddress(const IPAddress &ip, uint16_t port) : ip(ip), port(port) {}

    /// @brief Compares this `SocketAddress` with another for equality.
    /// @param other Another `SocketAddress` to compare against.
    /// @return `true` if both addresses are equal, `false` otherwise.
    bool operator==(const SocketAddress &other) const {
        return ip == other.ip && port == other.port;
    }

    /// @brief Compares this `SocketAddress` with another for inequality.
    /// @param other Another `SocketAddress` to compare against.
    /// @return `true` if both addresses are not equal, `false` otherwise.
    bool operator!=(const SocketAddress &other) const {
        return !(*this == other);
    }

    // Defined as an equality for the map to use this as a key
    bool operator<(const SocketAddress &other) const {
        if (ip != other.ip) {
            for (int i = 0; i < 4; i++) {
                if (ip[i] != other.ip[i]) {
                    return ip[i] < other.ip[i];
                }
            }
        }
        return port < other.port;
    }

    inline const char *toString() const {
        snprintf(SocketAddress::toStringBuffer, sizeof(SocketAddress::toStringBuffer), "%d.%d.%d.%d:%d", ip[0], ip[1], ip[2], ip[3], port);
        return SocketAddress::toStringBuffer;
    }

    inline operator const char *() const {
        return toString();
    }

   private:
    /// @brief Static buffer, shared by all instances of the struct for storing the formatted string
    inline static char toStringBuffer[32];
};

#endif  // SOCKET_ADDRESS_H
