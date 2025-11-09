#define BUZZER_PIN 8   // Passive buzzer on pin 8
#define BPM 120        // Beats per minute
#define BEEP_DURATION 100  // How long the beep lasts (ms)

unsigned long beatInterval = 60000UL / BPM;  // Time between beats (ms)
unsigned long previousMillis = 0;            // Last beat time
bool isBeeping = false;                      // Track if buzzer is on
unsigned long beepStartTime = 0;             // When beep started

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Handle starting a beat ---
  if (!isBeeping && currentMillis - previousMillis >= beatInterval) {
    previousMillis = currentMillis;
    tone(BUZZER_PIN, 1000); // Start beep at 1kHz
    isBeeping = true;
    beepStartTime = currentMillis;
  }

  // --- Handle stopping the beep ---
  if (isBeeping && currentMillis - beepStartTime >= BEEP_DURATION) {
    noTone(BUZZER_PIN); // Stop beep
    isBeeping = false;
  }

  // (You can do other tasks here, like read buttons or update LEDs)
}
