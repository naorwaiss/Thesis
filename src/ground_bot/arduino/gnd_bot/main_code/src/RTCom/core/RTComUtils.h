// RTComUtils.h
#ifndef RTCOM_UTILS_H
#define RTCOM_UTILS_H

#include <Arduino.h>
#include <QNEthernet.h>
#include <imxrt.h>

namespace RTComUtils {

/// @brief Gets teensy MAC address.
/// @param pMacAddress pointer to store the teensy mac address to.
void getTeensyMAC(uint8_t *pMacAddress);

/// @brief Makes sure there can be an ethernet connection.
/// @return `true` if a connection can be established; otherwise, `false`.
bool hasPhysicalEthernet();

/**
 * @brief Prints the current network configuration using `qindesign::network::Ethernet`.
 *
 * This function retrieves and prints the following network information:
 * - Local IP address
 * - Subnet mask
 * - Gateway IP address
 * - DNS server IP address
 *
 * The information is printed to the serial output for debugging or monitoring purposes.
 */
void printNetworkInfo();

}  // namespace RTComUtils

#endif  // RTCOM_UTILS_H