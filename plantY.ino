#define BLYNK_PRINT Serial //directs Blynk library debug output to the Serial Monitor

//authenticate and identify Blynk project

#define BLYNK_TEMPLATE_ID "TMPL3mFOUENAl"
#define BLYNK_TEMPLATE_NAME "smart plant"
#define BLYNK_AUTH_TOKEN "YjiRtRDm5mWKZ6B5_mz0hHmMjc9HP0v-"

//libraries for Wi-Fi and Blynk
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//includes the DHT sensor library
#include "DHT.h"

#define DPIN 4        //Pin to connect DHT sensor (GPIO number) D2
#define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type

// Define the analog pin for soil moisture sensor and digital pin for relay
#define soil_moisture_pin A0
#define relay_pin 7


// Create an instance of the DHT sensor
DHT dht(DPIN,DTYPE);

// Wi-Fi credentials
char ssid[] = "abc";
char pass[] = "def";


//BLYNK_WRITE(V3)
  //{
  //  int pinValue = param.asInt();

    //if(pinValue == 1){
      //digitalWrite(relay_pin, HIGH);
    //}
    //else{
      //digitalWrite(relay_pin, LOW);
    //}
  //}

// Setup function runs once when the device starts
void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud for debugging

  //pinMode(relay_pin, OUTPUT);
  //digitalWrite(relay_pin, LOW);

  // Initialize serial communication at 9600 baud for debugging
  dht.begin();

  // Connect to Blynk server
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// Main loop function runs repeatedly
void loop() {
  delay(2000); // Pause for 2 seconds between readings

  Blynk.run(); // Process incoming Blynk commands

  //Read humidity and temperature from the DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

    // Send humidity and temperature data to Blynk virtual pins
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V0, temperature);
  

// Read temperature in Celsius and Fahrenheit, and humidity
  float tc = dht.readTemperature(false);  //Read temperature in C
  float tf = dht.readTemperature(true);   //Read Temperature in F
  float hu = dht.readHumidity();          //Read Humidity

  // Print temperature in Celsius and Fahrenheit, and humidity to the Serial Monitor
  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, ");
  Serial.print(tf);
  Serial.print(" F, Hum: ");
  Serial.print(hu);
  Serial.println("%");

  // Read and print soil moisture level to the Serial Monitor
  Serial.println(analogRead(soil_moisture_pin));

   // Send soil moisture data to Blynk virtual pin
  Blynk.virtualWrite(V2, analogRead(soil_moisture_pin));

  

}
