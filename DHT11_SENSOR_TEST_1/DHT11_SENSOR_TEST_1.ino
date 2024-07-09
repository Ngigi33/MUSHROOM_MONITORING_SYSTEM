#include "DHT.h"
#define DHTPin 4
#define DHTTYPE DHT11

DHT dht(DHTPin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(1000);
  // put your main code here, to run repeatedly:
  float hum = dht.readHumidity();      //Read the moisture content in %.
  float temp = dht.readTemperature();  //Read the temperature in degrees Celsius

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed reception");
    return;
    //Returns an error if the ESP32 does not receive any measurements
  }


  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print("%  Temperature: ");
  Serial.print(temp);
  Serial.println("°C, ");
}
