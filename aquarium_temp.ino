//START OF CODE
#include <ESP8266WiFi.h>              // installs drivers for board
#include <BlynkSimpleEsp8266.h>       // installs drivers for blynk

#include <OneWire.h>                  // installs drivers for one wire
#include <DallasTemperature.h>        // installs drivers for DS18B20
#define ONE_WIRE_BUS 4                // Sets up pin D2 on WEMOS D1 Mini for reading sensor
OneWire oneWire(ONE_WIRE_BUS);        
DallasTemperature sensors(&oneWire);

#include <SimpleTimer.h>              // installs timer driver
SimpleTimer timer;

// Variables to gather data //
float s1;     // Sensor 1 temp 
int ct1;      
float ft1;     
int ft2;

char auth[] = "PUT YOUR BLYNK AUTH CODE HERE"; // Put your Auth Token here.
char ssid[] = "YOUR WIFI SSID";   // wireless
char pass[] = "YOUR WIFI PASSOWRD"; // wireless


void setup() {
timer.setInterval(15000, getTemps);           // Sets timer interval in miliseconds - 15000 = 15 seconds.  too often and blynk will hang
Blynk.begin(auth, ssid, pass); // wireless    // connects to your wifi
}

void getTemps() {
  sensors.requestTemperatures();            // reads the temperature
  s1 = sensors.getTempCByIndex(0);          // sets the variable s1
  s1 = (s1*10);                             // some sums to reduce simplifiy the temp to one decimal place
  ct1 = s1;                                 // and add a reading in Farenheit as well as celcius
  s1 = ct1;                                 // as US and old school Brits still like to read 'F on their tanks!
  s1 = (s1/10);
  ft1 = ((1.8 * s1) +32);
  ft1 = (ft1*10);
  ft2 = ft1;
  ft1 = ft2;
  ft1 = (ft1/10);

  Blynk.virtualWrite(V1, s1);               // Create a Virtual Pin variable for Blynk in Celcius
  Blynk.virtualWrite(V2, s1);               // Create a duplicate V pin in case you want a 2nd display on Blynk
  Blynk.virtualWrite(V3, ft1);              // Create a Virtual Pin variable for Blynk in Farenheit.
}

void loop() {
  Blynk.run();                              // Runs Blynk
  timer.run();                              // Fetches data as per the interval set above
}

//END OF CODE
