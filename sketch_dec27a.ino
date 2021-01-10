//Reading Temperature, Humidity and Pressure through internet
//Author: Sadat Rafi
//Created On: 11 January 2021
// ArduinoJson 6.0

//First Open an Account on :https://home.openweathermap.org/
//https://arduinojson.org/v6/doc/upgrade/

#include <ESP8266WiFi.h>       // Add ESP8266WiFi library from 'Manage Library' option
#include <ESP8266HTTPClient.h> // Add ESP8266HTTPClient library from 'Manage Library' option
#include <ArduinoJson.h>       // Add ArduinoJson library from 'Manage Library' option
 
// set Wi-Fi SSID and password
const char *ssid = "Tenda_9CAA98";
const char *password = "0#556*2delta";
 
void setup(void)
{
  Serial.begin(115200);
  delay(1000); 
  WiFi.begin(ssid, password); 
  Serial.print("Connecting.");
  while ( WiFi.status() != WL_CONNECTED )
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");  
}
 
void loop()
{
  if (WiFi.status() == WL_CONNECTED)            //Check WiFi connection status
  {
    HTTPClient http;                            //Declare an object of class HTTPClient
 
    // Request weather info according to zip code
    http.begin("http://api.openweathermap.org/data/2.5/weather?zip=2200,BD&appid=911297d64bc235e65dfd4f439f58c9e6"); 
    int httpCode = http.GET();
    // Requesting complete
    //Paste the URL in google chrome for checking if everything is ok
    
    if (httpCode > 0)                           // Check the respose from the weather server
    {
      String payload = http.getString();        //Get the request response payload
      DynamicJsonDocument doc(2048);            //https://arduinojson.org/v6/api/dynamicjsondocument/
      DeserializationError error = deserializeJson(doc,payload);
      if (error) 
      {
        Serial.print("DeserializeJson() Failed !! Error Code: ");
        Serial.println(error.c_str());
        return;
      }
      float temp = (float)(doc["main"]["temp"]) - 273.15; // get temperature in °C
      int humidity = doc["main"]["humidity"]; // get humidity in %
      float pressure = (float)(doc["main"]["pressure"]) / 1000; // get pressure in bar

      Serial.print("Temperature: ");Serial.println(temp);
      Serial.print("Humidity: ");Serial.println(humidity);
      Serial.print("Pressure: ");Serial.println(pressure);     
    } 
    http.end(); 
  }
  delay(6000);
}
