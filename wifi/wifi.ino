#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial ESP8266(0, 1); // RX, TX
unsigned char check_connection=0;                                      
unsigned char times_check=0;

void setup() {
  Serial.begin(115200); // Start up Serial
  ESP8266.begin(115200); // Start up ESP8266

   ESP8266.print("***VER:");
delay(2000);
ESP8266.println("AT+RST");
 delay(1000);
 ESP8266.println("AT+GMR");
delay(1000);
ESP8266.println("AT+CWMODE=3");
delay(1000);
ESP8266.println("AT+CWLAP");
delay(1000);
}


void loop() 
{

  // Test if the ESP8266 connects to the Wi-Fi
Serial.println("Connecting to Wifi");
   while(check_connection==0)
  {
    Serial.print(".");
  ESP8266.print("AT+CWJAP=\"GhostNetwork\",\"AdamWifi\"\r\n"); // Wi-Fi Name & Password
  ESP8266.setTimeout(5000);
 if(ESP8266.find("WIFI CONNECTED\r\n")==1)
 {
 Serial.println("WIFI CONNECTED");
 break;
 }
 times_check++;
 if(times_check>3) 
 {
  times_check=0; // Loops to try and connect to the Wi-Fi again
  Serial.println (" ");
   Serial.println("Trying to Reconnect..");
  }
  } 

  while(1);
}