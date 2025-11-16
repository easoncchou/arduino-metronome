#define BUZZER_PIN 8   // Passive buzzer on pin 8
#define BEEP_DURATION 100  // How long the beep lasts (ms)

enum MetronomeState {
  STATE_SLOW,
  STATE_MEDIUM,
  STATE_FAST
};

MetronomeState currentState = STATE_MEDIUM;

unsigned long beatInterval = 60000UL / 120;  // Time between beats (ms)
unsigned long previousMillis = 0;            // Last beat time
bool isBeeping = false;                      // Track if buzzer is on
unsigned long beepStartTime = 0;             // When beep started

const int buttonPin = 2;
bool wasPressed = false;  // stores previous button state
bool isButtonPressed();

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() {
  if (isButtonPressed()) {
    // ------------------------------
    //   STATE TRANSITIONS
    // ------------------------------
      switch (currentState) {
  	    case STATE_OFF:
          currentState = STATE_SLOW;
          break;
        case STATE_SLOW:
          currentState = STATE_MEDIUM;
          break;
        case STATE_MEDIUM:
          currentState = STATE_FAST;
          break;
        case STATE_FAST:
          currentState = STATE_OFF;
          break;
      }
      // ------------------------------
      //   STATE OUTPUT ACTIONS (after transition)
      // ------------------------------
      switch (currentState) {
  	    case STATE_OFF:
          isOff = true;
          break;
        case STATE_SLOW:
          isOff = true;
          beatInterval = 60000UL / 60;
          break;
        case STATE_MEDIUM:
          isOff = true;
          beatInterval = 60000UL / 120;
          break;
        case STATE_FAST:
          isOff = true;
          beatInterval = 60000UL / 180;
          break;
      }
    }


  unsigned long currentMillis = millis();

  // --- Handle starting a beat ---
  if (isOff == false) {
    if (!isBeeping && currentMillis - previousMillis >= beatInterval) {
      previousMillis = currentMillis;
      tone(BUZZER_PIN, 1000); // Start beep at 1kHz
      digitalWrite(LED_BUILTIN, HIGH); // Use the builtin led to test silently
      isBeeping = true;
      beepStartTime = currentMillis;
    }
  
    // --- Handle stopping the beep ---
    if (isBeeping && currentMillis - beepStartTime >= BEEP_DURATION) {
      noTone(BUZZER_PIN); // Stop beep
      digitalWrite(LED_BUILTIN, LOW);
      isBeeping = false;
    }
  }
}

// Detects rising edge: returns true once when button goes from LOW → HIGH
bool isButtonPressed() {
  bool buttonState = digitalRead(buttonPin);
  bool pressed = false;

  if (buttonState && !wasPressed) {
    // Button just pressed
    pressed = true;
  }

  wasPressed = buttonState;  // update last state
  return pressed;
}
