#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Set GPIO pin where the relay is connected
const int relayPin = 5;  // D1 pin on NodeMCU

WiFiServer server(80);

void setup() {
  // Initialize the relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Initially turn OFF the relay

  // Start Serial for debugging
  Serial.begin(115200);
  
  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Once connected, print the IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("New Client.");
  String currentLine = "";
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      Serial.write(c);
      
      // Check if the line ends with the HTTP request
      if (c == '\n') {
        // If the current line is blank, send a response
        if (currentLine.length() == 0) {
          // HTTP headers
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          // HTML page
          client.println("<html><body><h1>Home Automation</h1>");
          client.println("<p><a href=\"/ON\"><button>Turn ON</button></a></p>");
          client.println("<p><a href=\"/OFF\"><button>Turn OFF</button></a></p>");
          client.println("</body></html>");
          
          // End of HTTP response
          client.println();
          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
      
      // Check the request and control the relay
      if (currentLine.endsWith("GET /ON")) {
        digitalWrite(relayPin, HIGH);  // Turn ON relay
        Serial.println("Relay ON");
      }
      if (currentLine.endsWith("GET /OFF")) {
        digitalWrite(relayPin, LOW);  // Turn OFF relay
        Serial.println("Relay OFF");
      }
    }
  }

  // Close the connection
  client.stop();
  Serial.println("Client Disconnected.");
}