#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//------- WI-FI details ----------//
char ssid[] = "Harsh"; //SSID here
char pass[] = "12345678"; // Passowrd here
//--------------------------------//

//----------- Channel details ----------------//
unsigned long Channel_ID =  1686765; // Your Channel ID
const char * myWriteAPIKey = "I62DXNQAMQJG13IQ"; //Your write API key
//-------------------------------------------//

const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;

String value = "";
int value_1 = 0;
int value_2 = 0;
int value_3 = 0;
int x, y;
WiFiClient  client;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  internet();
}


void loop() {
  // put your main code here, to run repeatedly:
  internet();
  if (Serial.available() > 0)
  {
    delay(100);
    while (Serial.available() > 0)
    {
      value = Serial.readString();
      if (value[0] == '*')
      {
        if (value[5] == '#')
        {
         //Serial.println(value);
          value_1 = ((value[1] - 0x30) * 10);
          value_2 = ((value[2] - 0x30) * 10+(value[3] - 0x30));
          value_3 = ((value[4] - 0x30) *10);

         }
      }
    }
  }
  upload();
}


void internet()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
  }
}


void upload()
{
  ThingSpeak.writeField(Channel_ID, Field_Number_1, value_1, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_2, value_2, myWriteAPIKey);
  delay(15000);
  ThingSpeak.writeField(Channel_ID, Field_Number_3, value_3, myWriteAPIKey);
  delay(15000);
  value = "";
}
