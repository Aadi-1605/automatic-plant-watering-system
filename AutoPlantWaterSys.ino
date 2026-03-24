// -------------------------------------------
// SMART PLANT WATERING SYSTEM (1 sec pause)
// Relay = ACTIVE HIGH (HIGH = ON)
// Sensor YL-38/39: LOW = wet, HIGH = dry
// Buzzer keeps beeping with a 1 sec pause while soil is dry
// -------------------------------------------

int sensorPin = A0;
int relayPin = 7;
int redLed = 8;
int buzzerPin = 9;
int whiteLed = 10;

int threshold = 600;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, LOW); // Pump OFF
  digitalWrite(redLed, LOW);
  digitalWrite(whiteLed, LOW);

  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(sensorPin);
  Serial.print("Soil Value: ");
  Serial.println(sensorValue);

  bool isSoilDry = (sensorValue >= threshold);

  // ============================
  // SOIL DRY
  // ============================
  if (isSoilDry) {
    digitalWrite(relayPin, HIGH);   // Pump ON
    digitalWrite(redLed, HIGH);
    digitalWrite(whiteLed, LOW);
    Serial.println("Soil DRY -> Pump ON -> Buzzer Beeping");

    tone(buzzerPin, 1500);   // 1.5 kHz tone
    delay(300);              // 0.3 sec beep
    noTone(buzzerPin);
    delay(1000);             // >>> 1 sec pause <<<
  }

  // ============================
  // SOIL WET
  // ============================
  else {
    digitalWrite(relayPin, LOW);   // Pump OFF
    digitalWrite(redLed, LOW);
    digitalWrite(whiteLed, HIGH);
    noTone(buzzerPin);

    Serial.println("Soil WET -> Pump OFF");

    delay(500);
  }
}
