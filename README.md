# Electrical Meter with Esp and PZEM004Tv30

The smart meter is an advanced metering device that records electricity consumption in a more detailed and accurate manner compared to traditional meters. Provides real-time data on energy usage, consumption, actual current drawn, and bill value. The Arduino programming language was mainly used to program the device. The PZEM004Tv30 and ESP8266 were used for monitoring through a mobile application. The Blink platform was used to create the prototype application.


## Component

1- The PZEM004Tv30 is an electrical energy monitoring module. It is commonly used to measure various electrical parameters in a circuit, such as voltage, current, power, energy, and frequency.The PZEM004Tv30 module typically operates with an AC voltage range of 80V to 260V and can measure current up to 100A. It uses a non-invasive method for current measurement, which means you don't need to break or interrupt the circuit to measure the current flowing through it.By utilizing the PZEM004Tv30 module, you can monitor and measure electrical parameters in real-time, making it useful for applications such as power monitoring, energy management, smart home systems, and more.


![PZEM-004-module](https://github.com/IbraheemAljolani/Arduino-EnergyMeter/assets/124505345/e784e55a-cf5c-4523-a7ea-f825a1481781)


2- The ESP8266 is a highly popular and widely used Wi-Fi module or system-on-a-chip (SoC) that combines a microcontroller with Wi-Fi capabilities.The ESP8266 is widely used in IoT projects for a range of applications such as home automation, sensor monitoring, data logging, smart appliances, and more. It offers a cost-effective and efficient solution for adding wireless connectivity to various devices and systems.


![71ZUXpbgc1L](https://github.com/IbraheemAljolani/Arduino-EnergyMeter/assets/124505345/aec83bcc-8a5d-4a1b-ac06-0b5a3c5c260e)


## Services

1- Firebase is a comprehensive mobile and web development platform provided by Google that is used to interconnect the meter and application for data transmission. Firebase provides a NoSQL cloud-hosted database that allows developers to store and synchronize data in real-time across multiple clients. It uses a real-time synchronization mechanism, enabling immediate updates to be propagated to all connected clients and Firebase includes built-in authentication services that support various authentication methods such as email/password, phone number, Google, Facebook, Twitter, and more. This simplifies user authentication and enables secure access control for your application.

2- Blynk is a software platform that enables developers to easily and quickly create Internet of Things (Internet of Things) applications that were relied upon to create the prototype of the mobile application.


![Untitled design](https://github.com/IbraheemAljolani/Arduino-EnergyMeter/assets/124505345/084bc1f7-bc18-4871-aaa0-27fc8c0740a0)


## Here's a breakdown of the code

1. Libraries:
   - ESP8266WiFi: Library for connecting to a Wi-Fi network using ESP8266.
   - ESP8266WebServer: Library for creating a web server on ESP8266.
   - WiFiManager: Library for managing Wi-Fi connections and network settings.
   - FirebaseESP8266: Library for interacting with Firebase using ESP8266.
   - EEPROM: Library for reading and writing to EEPROM memory.

2. Global Variables:
   - Various float variables for storing price values and power consumption readings.

3. Setup Function:
   - Initializes the serial communication for debugging purposes.
   - Configures and connects to the Wi-Fi network using the saved credentials or enters the Wi-Fi setup mode if credentials are not available.
   - Initializes the Firebase connection using the provided Firebase project credentials.
   - Waits until the Wi-Fi connection is established.

4. Loop Function:
   - Reads the voltage, current, power, energy, frequency, and power factor from the PZEM004Tv30 power meter.
   - Sends the readings to Firebase and prints them to the serial monitor.
   - Calculates the cumulative energy consumption (kWh) by adding the current energy value to the previous value.
   - Checks the Firebase data for a specific command (value "i") and performs corresponding calculations based on the received command.
   - Updates the Firebase data with the calculated prices.
   - Stores the updated energy consumption value (kWh) in EEPROM memory.
