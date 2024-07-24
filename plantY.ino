#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL3mFOUENAl"
#define BLYNK_TEMPLATE_NAME "smart plant"
#define BLYNK_AUTH_TOKEN "YjiRtRDm5mWKZ6B5_mz0hHmMjc9HP0v-"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DPIN 4        //Pin to connect DHT sensor (GPIO number) D2
#define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type
#define soil_moisture_pin A0
#define relay_pin 7



DHT dht(DPIN,DTYPE);

char ssid[] = "Siya <3";
char pass[] = "Siya@wifi!";


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


void setup() {
  Serial.begin(9600);

  //pinMode(relay_pin, OUTPUT);
  //digitalWrite(relay_pin, LOW);

  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  delay(2000);

  Blynk.run();
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V0, temperature);
  


  float tc = dht.readTemperature(false);  //Read temperature in C
  float tf = dht.readTemperature(true);   //Read Temperature in F
  float hu = dht.readHumidity();          //Read Humidity

  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, ");
  Serial.print(tf);
  Serial.print(" F, Hum: ");
  Serial.print(hu);
  Serial.println("%");



  Serial.println(analogRead(soil_moisture_pin));
  Blynk.virtualWrite(V2, analogRead(soil_moisture_pin));

  

}