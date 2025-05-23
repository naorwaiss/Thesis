#include "RTComUtils.h"

namespace RTComUtils {
using namespace qindesign::network;

void getTeensyMAC(uint8_t *pMacAddress) {
    for (uint8_t i = 0; i < 2; i++)
        pMacAddress[i] = (HW_OCOTP_MAC1 >> ((1 - i) * 8)) & 0xFF;
    for (uint8_t i = 0; i < 4; i++)
        pMacAddress[i + 2] = (HW_OCOTP_MAC0 >> ((3 - i) * 8)) & 0xFF;
}

bool hasPhysicalEthernet() {
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
        return false;
    

    //////////! IGNORE USING TEENSY !//////////
    // if (Ethernet.linkStatus() == LinkOFF)
    // {
    //     Serial.println("Ethernet cable is not connected.");
    //     return false;
    // }
    return true;
}

void printNetworkInfo() {
    IPAddress ip = Ethernet.localIP();
    printf("    Local IP    = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);

    ip = Ethernet.subnetMask();
    printf("    Subnet mask = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);

    ip = Ethernet.gatewayIP();
    printf("    Gateway     = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);

    ip = Ethernet.dnsServerIP();
    printf("    DNS         = %u.%u.%u.%u\r\n", ip[0], ip[1], ip[2], ip[3]);

    byte mac[6];
    Ethernet.macAddress(mac);
    printf("    MAC Address = %02X:%02X:%02X:%02X:%02X:%02X\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

}  // namespace RTComUtils
