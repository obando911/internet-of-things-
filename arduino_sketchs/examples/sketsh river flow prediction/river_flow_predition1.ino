// C++ code
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  // Inicializa los pines
  pinMode(4, OUTPUT);  // LED verde
  pinMode(8, OUTPUT);  // LED amarillo
  pinMode(13, OUTPUT); // LED rojo

  // Inicia la comunicación serial
  Serial.begin(9600);  // Esto es necesario para ver los mensajes en el monitor serial
}

void loop()
{
  long distance = readUltrasonicDistance(2, 3);  // Lee la distancia en microsegundos
  float distanceCm = 0.01723 * distance;  // Convierte a centímetros (distancia en cm)

  // Imprime la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // LED verde (distancia entre 190 y 320 cm)
  if (distanceCm > 190 && distanceCm < 320) {
    digitalWrite(4, HIGH);  // Enciende LED verde
  } else {
    digitalWrite(4, LOW);  // Apaga LED verde
  }

  // LED amarillo (distancia entre 90 y 189 cm)
  if (distanceCm > 90 && distanceCm < 189) {
    digitalWrite(8, HIGH);  // Enciende LED amarillo
  } else {
    digitalWrite(8, LOW);  // Apaga LED amarillo
  }

  // LED rojo (distancia menor a 89 cm)
  if (distanceCm > 0 && distanceCm < 89) {
    digitalWrite(13, HIGH);  // Enciende LED rojo
    Serial.println("¡Advertencia! ¡Nivel de agua Alto!");  // Muestra mensaje de advertencia
  } else {
    digitalWrite(13, LOW);  // Apaga LED rojo
  }

  delay(1000); // Delay para mejorar el rendimiento de la simulación
}
