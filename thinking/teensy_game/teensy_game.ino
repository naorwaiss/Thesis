#include <NativeEthernet.h>

// Network configuration
byte mac[] = { 0x04, 0xE9, 0xE5, 0x01, 0x02, 0x03 }; // MAC Address
IPAddress ip(192, 168, 1, 177);                     // Teensy IP Address
unsigned int port = 5000;                           // Communication port

EthernetServer server(port); // Create a server on the specified port
EthernetClient client;       // Global client for persistent connection

unsigned long lastMessageTime = 0; // Last time a message was sent
const unsigned long messageInterval = 1000; // Time interval between messages (1 second)

void setup() {
  Serial.begin(9600);

  // Initialize Ethernet
  Ethernet.begin(mac, ip);

  Serial.print("Teensy IP Address: ");
  Serial.println(Ethernet.localIP());

  // Start the server
  server.begin();
  Serial.println("Server is running and waiting for clients...");
}

void loop() {
  // Check for a new client or maintain existing connection
  if (!client || !client.connected()) {
    client = server.available();
    if (client) {
      Serial.println("Client connected!");
    }
  }

  // Handle incoming data if client is connected
  if (client && client.connected()) {
    handleIncomingMessages();
    sendHelloWorldPeriodically();
  }
}

void handleIncomingMessages() {
  while (client.available() >= 4) {
    uint32_t message_length = 0;
    for (int i = 0; i < 4; i++) {
      message_length = (message_length << 8) | client.read();
    }
    Serial.print("Message length: ");
    Serial.println(message_length);

    // Wait for the rest of the message
    while (client.available() < message_length);

    char message[message_length + 1];
    for (uint32_t i = 0; i < message_length; i++) {
      message[i] = client.read();
    }
    message[message_length] = '\0'; // Null-terminate the string

    Serial.print("Received message: ");
    Serial.println(message);
  }
}

void sendHelloWorldPeriodically() {
  if (millis() - lastMessageTime > messageInterval) {
    if (client.connected() && client.availableForWrite() > 0) {
      const char* message = "Hello World";
      uint32_t message_length = strlen(message);

      // Send message length
      client.write((uint8_t*)&message_length, sizeof(message_length));

      // Send the message
      client.write((const uint8_t*)message, message_length);

      Serial.println("Sent 'Hello World' to client.");

      lastMessageTime = millis(); // Update last message time
    }
  }
}
