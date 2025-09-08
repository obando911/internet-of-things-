int const LED_ROJO = 13;
int const LED_AMARILLO = 12;
int const LED_VERDE = 11;
int const BTN = 7;   // Pulsador en pin 7 (INPUT_PULLUP)

char opt;
int btnState;
int lastBtnState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Control de acciones por pulsador
int accion = 0;

// Variables para intermitencia sin delay
unsigned long prevMillis = 0;
int estadoBlink = LOW;

void setup() {
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);

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

void ejecutarAccion(int a) {
  // Apagar todos primero
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);

  switch (a) {
    case 1: // LED rojo
      digitalWrite(LED_ROJO, HIGH);
      break;
    case 2: // LED verde
      digitalWrite(LED_VERDE, HIGH);
      break;
    case 3: // LED amarillo
      digitalWrite(LED_AMARILLO, HIGH);
      break;
    case 4: // Todos apagados
      break;
    case 5: // Todos encendidos
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      break;
    case 6: // Intermitencia sin delay
      unsigned long currentMillis = millis();
      if (currentMillis - prevMillis >= 500) {
        prevMillis = currentMillis;
        estadoBlink = !estadoBlink;
        digitalWrite(LED_ROJO, estadoBlink);
        digitalWrite(LED_AMARILLO, estadoBlink);
        digitalWrite(LED_VERDE, estadoBlink);
      }
      break;
  }
}

void loop() {
  // =======================
  // Gestión Serial (igual que antes)
  // =======================
  if (Serial.available() > 0) {
    menu();
    opt = Serial.read();

    if (opt == '1') digitalWrite(LED_ROJO, HIGH);
    if (opt == '2') digitalWrite(LED_ROJO, LOW);
    if (opt == '3') digitalWrite(LED_AMARILLO, HIGH);
    if (opt == '4') digitalWrite(LED_AMARILLO, LOW);
    if (opt == '5') digitalWrite(LED_VERDE, HIGH);
    if (opt == '6') digitalWrite(LED_VERDE, LOW);
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
      // Intermitencia con delay (solo si se activa desde Serial)
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

  // =======================
  // Gestión Pulsador (con debounce)
  // =======================
  int reading = digitalRead(BTN);
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && btnState == HIGH) {
      // Cambio válido: avanzar a la siguiente acción
      accion++;
      if (accion > 6) accion = 1; // Ciclo
    }
    btnState = reading;
  }
  lastBtnState = reading;

  // Ejecutar acción del pulsador
  ejecutarAccion(accion);
}
