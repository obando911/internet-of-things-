# 🌡️ Control de Temperatura con Arduino UNO, LCD y Motor DC

Este proyecto utiliza un **sensor de temperatura TMP36**, un **display LCD 16x2**, un **LED** y un **motor DC (ventilador)** controlado automáticamente según la temperatura ambiente.

El sistema mide la temperatura, la muestra en la pantalla LCD y en el monitor serial, y enciende o apaga el ventilador y el LED según el rango de temperatura detectado.

---

## 🧩 Componentes utilizados

| Componente | Descripción |
|-------------|-------------|
| Arduino UNO | Microcontrolador principal |
| TMP36 | Sensor analógico de temperatura |
| LCD 16x2 | Pantalla para mostrar la temperatura |
| Potenciómetro 10kΩ | Ajuste del contraste del LCD |
| Motor DC | Simula el ventilador |
| Transistor NPN (2N2222 o TIP120) | Control del motor |
| Diodo 1N4007 | Protección contra corriente inversa |
| LED + resistencia 220Ω | Indicador visual |
| Protoboard y cables | Conexión del circuito |

---

## ⚙️ Funcionamiento

1. El sensor **TMP36** mide la temperatura ambiente y envía una señal analógica al pin **A0** del Arduino.  
2. El Arduino convierte la señal a voltaje y calcula la temperatura en grados Celsius.  
3. La temperatura se muestra en el **LCD 16x2** y también se envía al **monitor serial**.  
4. Dependiendo del rango de temperatura:
   - 🌡️ **≤ 10°C:** El LED parpadea y el motor se apaga.  
   - 🌡️ **11°C – 25°C:** Todo permanece apagado (modo reposo).  
   - 🌡️ **≥ 26°C:** El LED y el motor se encienden (simulando ventilación).

---

## 🔌 Conexiones principales

| Elemento | Pin Arduino | Descripción |
|-----------|--------------|-------------|
| TMP36 | A0 | Señal analógica |
| LED | 13 | Indicador visual |
| Motor (Base transistor) | 10 | Control de velocidad ON/OFF |
| LCD RS | 12 | Control de registro |
| LCD E | 11 | Habilitación |
| LCD D4–D7 | 5, 4, 3, 2 | Líneas de datos |
| Potenciómetro | Entre VCC y GND | Ajusta contraste LCD |

🔸 El transistor NPN se usa como interruptor del motor.  
🔸 Se recomienda conectar el **diodo 1N4007 en paralelo** con el motor (cátodo al positivo) para proteger el circuito.

---

## 🖥️ Código fuente

El programa está desarrollado en **Arduino IDE**.  
Archivo principal: `main.ino`

```cpp
#include <LiquidCrystal.h>

// Inicializa LCD con los pines RS, E, D4, D5, D6, D7
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

const int sensorPin = A0;      // TMP36
const int ledPin = 13;         // LED
const int motorPin = 10;       // Motor (ventilador)

int sensor_value;
float temperature;

void setup() {
  lcd_1.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Temp: ");
}

void loop() {
  sensor_value = analogRead(sensorPin);
  float voltage = sensor_value * (5.0 / 1023.0);
  temperature = (voltage - 0.5) * 100.0;

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  lcd_1.setCursor(0, 1);
  lcd_1.print("Temp: ");
  lcd_1.print(temperature, 1);
  lcd_1.print((char)223);
  lcd_1.print("C   ");

  if (temperature <= 10) {
    digitalWrite(motorPin, LOW);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
  }
  else if (temperature >= 11 && temperature <= 25) {
    digitalWrite(ledPin, LOW);
    digitalWrite(motorPin, LOW);
    delay(1000);
  }
  else if (temperature >= 26) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(motorPin, HIGH);
    delay(1000);
  }
}
# internet-of-things-
