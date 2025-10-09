#include<DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
#define LED_RED 13
float humidity, temperature;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
pinMode(LED_RED, OUTPUT);

dht.begin();
Serial.begin(9600);
Serial.println(":: Hello to whether Station ::");
}

void loop() {
  // put your main code here, to run repeatedly:
humidity = dht.readHumidity();
temperature = dht.readTemperature();
Serial.print("Humidity: ");
Serial.print(humidity);
Serial.println("%");
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.println(" °C");
delay(2000);

//NaN: Not a number
}
