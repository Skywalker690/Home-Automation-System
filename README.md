Explanation:

1. Wi-Fi Setup: Replace "your_SSID" and "your_PASSWORD" with your Wi-Fi credentials.


2. Relay Control: The relay is connected to GPIO pin 5 (D1). You can change this based on your wiring.


3. Web Server: The ESP8266 hosts a simple web server that serves an HTML page with two buttons—ON and OFF. Clicking on these buttons will toggle the relay.



How it Works:

Connect the ESP8266 to your Wi-Fi network.

Once connected, the IP address will be printed in the Serial Monitor.

Open the IP address in a browser (e.g., 192.168.1.x).

You'll see two buttons on the webpage: "Turn ON" and "Turn OFF".

Clicking "Turn ON" sends a request to /ON, which turns on the relay (and the connected appliance).

Clicking "Turn OFF" sends a request to /OFF, which turns off the relay.


This is a basic example of IoT-based home automation that can be expanded to control multiple devices or integrated with voice assistants like Google Assistant or Alexa.
