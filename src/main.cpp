// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 
 

//  I Gunjan Chaudhary, 000831804 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else.

// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

uint8_t tempSensorAddress [8];
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 


  if(DS18B20.getAddress(tempSensorAddress, 0)){
    Serial.println("temperature Application");
    Serial.print("Found DS18B20 sensor with address: " );
  }
  else{
    Serial.println("Could not detect the sensor. Please try reconnecting!!");
    exit(0);
  }

  for (int i=0; i< 8; i++)
  {
    Serial.printf("%02X ", tempSensorAddress[i]);
  
  }
} 
 
void loop() { 
  float finalTemp; 
  String judgement;    //variable to store the final judgement string
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  finalTemp = DS18B20.getTempCByIndex(0); 

 if (finalTemp<10.0)
  {
      judgement = "Cold!";
  }
  else if(finalTemp >10.0 && finalTemp <= 15.0){
    judgement = "Cool";
  }
  else if(finalTemp >15.0 && finalTemp <= 25.0){
    judgement = "Perfect";
  }
  else if(finalTemp >25.0 && finalTemp <= 30.0){
    judgement = "Warm";
  }
  else if(finalTemp >30.0 && finalTemp <= 35.0){
    judgement = "Hot";
  }
  else if(finalTemp >35.0){
    judgement = "Too Hot!";
  }

  // print the temp to the USB serial monitor 
  Serial.println( "Current temperature is: " + String(finalTemp) + " \xB0""C or " + judgement); 
 
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
} 