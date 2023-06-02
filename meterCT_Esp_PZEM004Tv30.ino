#include <ESP8266WiFi.h>//esp8266 library 
#include <ESP8266WebServer.h>//for wifi set the network 
#include <WiFiManager.h> //for wifi set the network         
#include <FirebaseESP8266.h>//for send data for firbase and save there
//#include <FirebaseArduino.h>
WiFiManager wifiManager;
FirebaseData fbdo;
#include <EEPROM.h>
#include <PZEM004Tv30.h>
PZEM004Tv30 pzem(14, 12); // Software Serial pin 11 (RX) & 12 (TX)
#define FIREBASE_HOST "meter-f0619-default-rtdb.firebaseio.com" //account of firbase for all project
#define FIREBASE_AUTH "Wwmy0iVBrZP73ZHEWyUXwaIeFDS5DxF0CmpsZu0D" //auth for all proejct
String a;
float pricethn;
float price1hn;
float price2hn;
float pricethns;
float price1hns;
float price2hns;
float price3hns;
float pricetcn;
float price1cn;
float price2cn;
float pricetsi;
float price1si;
float price2si;
float kwh;
float pf;
void setup() {
  Serial.begin(9600);
  //wifiManager.resetSettings();    //Uncomment this to wipe WiFi settings from EEPROM on boot.  Comment out and recompile/upload after 1 boot cycle.
  wifiManager.autoConnect("Smart Space");
  WiFi.begin(WiFi.SSID(), WiFi.psk());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED   ) {
    Serial.print(".");
    delay(300);
    EEPROM.begin(512);
  EEPROM.get(0, kwh);
  }
  Firebase.reconnectWiFi(true);
}

void loop() {
  float voltage = pzem.voltage();
  if (voltage != NAN) {
    Firebase.setFloat(fbdo, "Voltage", voltage);
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println("V");
  } else {
    Serial.println("Error reading voltage");
  }

  float current = pzem.current();
  if (current != NAN) {
    Firebase.setFloat(fbdo, "Current", current);
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println("A");
  } else {
    Serial.println("Error reading current");
  }

  float power = pzem.power();
  if (current != NAN) {
    Firebase.setFloat(fbdo, "Power", power);
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println("W");
  } else {
    Serial.println("Error reading power");
  }

  float energy = pzem.energy();
  if (current != NAN) {
    Firebase.setFloat(fbdo, "Energy", energy);
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println("kWh");
  } else {
    Serial.println("Error reading energy");
  }

  float frequency = pzem.frequency();
  if (current != NAN) {
    Firebase.setFloat(fbdo, "Frequency", frequency);
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println("Hz");
  } else {
    Serial.println("Error reading frequency");
  }

   pf = pzem.pf();
  if (current != NAN) {
    Firebase.setFloat(fbdo, "PF", pf);
    Serial.print("PF: ");
    Serial.println(pf);
  } else {
    Serial.println("Error reading power factor");
  }
  Serial.println();
  kwh = kwh + (energy * 0.0000016667);
  Serial.println(kwh);
  Firebase.setFloat(fbdo, "KWh", kwh);
  if(Firebase.getString(fbdo, "i")){
    if (fbdo.stringData() == "1") { //////////////////////////////////////////////////////////////////////////////////Home
    if ( kwh <= 1000.0) {
      price1hn = kwh * (0.12);
    }
    if ( kwh > 1000.0 ) {

      price2hn = (kwh - 1000) * (0.15);
      if (price1hn == 0) {
        price1hn = 120;
      }
    }
    pricethn = price1hn + price2hn;
    Firebase.setFloat(fbdo, "/pricethn", pricethn);
  }
  
  } 
if(Firebase.getString(fbdo, "i")){
  if (fbdo.stringData() == "2") { /////////////////////////////////////////////////////////////////////////Home new Support
    if ( kwh <= 300.0) {
      price1hns = kwh * (0.05);
    }
    if ( kwh > 300.0 && kwh <= 600.0) {

      price2hns = (kwh - 300) * (0.10);
      if (price1hns == 0) {
        price1hns = 15;
      }
    }
    if ( kwh > 600) {

      price3hns = (kwh - 600) * (0.20);
      if (price1hns == 0 && price2hns == 0) {
        price1hns = 15;
        price1hns = 30;
      }
    }
    pricethns = price1hns + price2hns + price3hns ;
    Firebase.setFloat(fbdo, "/pricethns", pricethns);
    if (kwh > 50 && kwh <= 200) {
      pricethns = price1hns - 2.5;
    }
    if (kwh > 200 && kwh <= 600) {
      pricethns = (price1hns + price2hns) - 2;
    }
}
 
  }
  if(Firebase.getString(fbdo, "i")){
    if (fbdo.stringData() == "3") { ///////////////////////////////////////////////////////////////////////Commerical
    if ( kwh <= 2000.0) {
      price1cn = kwh * (0.12);
    }
    if (kwh > 2000.0) {
      price2cn = (kwh - 2000) * 0.152;
      if (price1cn == 0) {
        price1cn = 240;
      }
    }
    pricetcn = price1cn + price2cn;
    Firebase.setFloat(fbdo, "/pricetcn", pricetcn);
  }  
  
  } 
if(Firebase.getString(fbdo, "i"))
 if (fbdo.stringData() == "4") { ///////////////////////////////////////////////////////////////////////small industrial
    if ( kwh <= 10000.0) {
      price1si = kwh * (0.60);
    }
    if ( kwh > 10000.0 ) {

      price2si = (kwh - 10000) * (0.68);
      if (price1si == 0) {
        price1si = 6000;
      }
    }
    pricetsi = price1si + price2si;
    Firebase.setFloat(fbdo, "/pricetsi", pricetsi);
  }
  EEPROM.put(0, kwh);
}
