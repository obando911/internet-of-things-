int const LED_ROJO = 13;      // LED1
int const LED_AMARILLO = 12;  // LED2
int const LED_VERDE = 11;     // LED3

char opt;

void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  Serial.begin(9600);
  Serial.println("   :: WELCOME ::   ");
  Serial.println("Press any key to show menu ");
}

void menu() {
  Serial.println("      MAIN MENU      ");
  Serial.println("[1] turn on led red ");
  Serial.println("[2] turn off led red ");
  Serial.println("[3] turn on led yellow ");
  Serial.println("[4] turn off led yellow ");
  Serial.println("[5] turn on led green ");
  Serial.println("[6] turn off led green ");
  Serial.println("[7] turn on all ");
  Serial.println("[8] turn off all ");
  Serial.println("[9] intermitence ");
  Serial.println("Press any option: ");
}

void loop() {
  if (Serial.available() > 0) {
    menu();
    opt = Serial.read();

    if (opt == '1') {
      digitalWrite(LED_ROJO, HIGH);
    }
    if (opt == '2') {
      digitalWrite(LED_ROJO, LOW);
    }
    if (opt == '3') {
      digitalWrite(LED_AMARILLO, HIGH);
    }
    if (opt == '4') {
      digitalWrite(LED_AMARILLO, LOW);
    }
    if (opt == '5') {
      digitalWrite(LED_VERDE, HIGH);
    }
    if (opt == '6') {
      digitalWrite(LED_VERDE, LOW);
    }
    if (opt == '7') {
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
    }
    if (opt == '8') {
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);
    }
    if (opt == '9') {
      for (int i = 0; i < 5; i++) {
        digitalWrite(LED_ROJO, HIGH);
        digitalWrite(LED_AMARILLO, HIGH);
        digitalWrite(LED_VERDE, HIGH);
        delay(500);
        digitalWrite(LED_ROJO, LOW);
        digitalWrite(LED_AMARILLO, LOW);
        digitalWrite(LED_VERDE, LOW);
        delay(500);
      }
    }
  }
}
