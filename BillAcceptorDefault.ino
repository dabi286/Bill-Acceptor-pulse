#define billAcceptor 8
int pulseCount = 0;
unsigned long lastPulseTime = 0;
bool waiting = false;

void setup() {
  Serial.begin(9600);
  pinMode(billAcceptor, INPUT_PULLUP);
}

void loop() {
  // Read pulse
  if (digitalRead(billAcceptor) == LOW) {
    pulseCount++;
    lastPulseTime = millis();
    delay(100); // debounce
  }

 
  if (pulseCount > 0 && millis() - lastPulseTime > 1000) {
    int billValue = pulseCount * 10; 
    Serial.println("Bill: " + String(billValue));
    pulseCount = 0;
  }

  // Reset from serial
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "reset") {
      pulseCount = 0;
    }
  }
}