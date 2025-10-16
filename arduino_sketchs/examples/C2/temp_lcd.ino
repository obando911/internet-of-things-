// C++ code
//
/*
  LiquidCrystal Library - Hello World

   Demonstrates the use of a 16x2 LCD display.
  The LiquidCrystal library works with all LCD
  displays that are compatible with the  Hitachi
  HD44780 driver. There are many of them out
  there, and you  can usually tell them by the
  16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * LCD R/W pin to ground
  * LCD VSS pin to ground
  * LCD VCC pin to 5V
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008  by David
  A. Mellis
  library modified 5 Jul 2009  by Limor Fried
  (http://www.ladyada.net)
  example added 9 Jul 2009  by Tom Igoe
  modified 22 Nov 2010  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>

// Inicializa LCD con los pines RS, E, D4, D5, D6, D7
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;      // TMP36
const int ledPin = 13;         // LED
const int motorPin = 10;       // Motor (ventilador)

int sensor_value;
float temperature;

void setup() {
  lcd_1.begin(16, 2);         // Inicializa la LCD 16x2
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  Serial.begin(9600);

  lcd_1.setCursor(0, 0);
  lcd_1.print("Temp: ");
}

void loop() {
  sensor_value = analogRead(sensorPin);
  float voltage = sensor_value * (5.0 / 1023.0);  // OJO: es 1023, no 1024
  temperature = (voltage - 0.5) * 100.0;

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  // Mostrar temperatura en LCD
  lcd_1.setCursor(0, 1);
  lcd_1.print("Temp: ");
  lcd_1.print(temperature, 1);
  lcd_1.print((char)223);  // símbolo de grado
  lcd_1.print("C   ");     // Limpiar restos

  // -------------------------
  // Validaciones de control
  // -------------------------

  if (temperature <= 10) {
    // LED parpadea
    digitalWrite(motorPin, LOW);     // Motor apagado
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  else if (temperature >= 11 && temperature <= 25) {
    // Todo apagado
    digitalWrite(ledPin, LOW);
    digitalWrite(motorPin, LOW);
    delay(1000);
  }
  else if (temperature >= 26) {
    // Motor y LED encendidos
    digitalWrite(ledPin, HIGH);
    digitalWrite(motorPin, HIGH);
    delay(1000);
  }
}
