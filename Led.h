#ifndef LED_H
#define LED_H

enum State {
  ON,
  OFF,
  BLINKING,
  BLINKING_ON,
  BLINKING_OFF,
};

class Led {
  const byte pin;
  int state = State::OFF;
  int previousState = State::OFF;
  int remainingBlinks = 0;
  int blinkInterval = 200;
  unsigned long last_blink_time = 0;
  unsigned long timeSinceLastBlink = 0;
  
  public:
    Led(byte attachToPin) : pin(attachToPin) {};

    void setup() {
      pinMode(pin, OUTPUT);
    }

    void loop() {
      switch (state) {
        case State::ON:
          // Serial.println("LED ON");
          digitalWrite(pin, HIGH);
          break;
        case State::OFF:
          // Serial.println("LED OFF");
          digitalWrite(pin, LOW);
          break;
        case State::BLINKING:
          // Serial.println("LED BLINKING");
          state = State::BLINKING_ON;
          break;
        case State::BLINKING_ON:
          timeSinceLastBlink = millis() - last_blink_time;
          // Serial.print("LED BLINKING_ON - ");
          // Serial.print("BLINK: remainingBlinks = ");
          // Serial.print(remainingBlinks);
          // Serial.print(" timeSinceLastBlink: ");
          // Serial.println(timeSinceLastBlink);  
          if (remainingBlinks > 0 && timeSinceLastBlink > blinkInterval) {
            // remainingBlinks--;
            digitalWrite(pin, HIGH);
            last_blink_time = millis();
            state = State::BLINKING_OFF;

            // Serial.print("BLINK-ON: remainingBlinks = ");
            // Serial.println(remainingBlinks);
          }
          break;
        case State::BLINKING_OFF:
          timeSinceLastBlink = millis() - last_blink_time;
          // Serial.print("LED BLINKING_OFF - ");
          // Serial.print("BLINK: remainingBlinks = ");
          // Serial.print(remainingBlinks);
          // Serial.print(" timeSinceLastBlink: ");
          // Serial.println(timeSinceLastBlink);  
          if (remainingBlinks > 0 && timeSinceLastBlink > blinkInterval) {
            remainingBlinks--;
            last_blink_time = millis();
            // blink off
            digitalWrite(pin, LOW);
            state = State::BLINKING_ON;

            // Serial.print("BLINK-OFF: remainingBlinks = ");
            // Serial.println(remainingBlinks);
          }

          // if no blinks left, reset state to previous state
          // otherwise, set to blinking on
          if (remainingBlinks <= 0) {
            state = previousState;
            remainingBlinks = 0;
            // Serial.println("UPDATE TO PREVIOUS STATE");
          }
          break;
      }
    }

    void on() {
      state = State::ON;
    }

    void off() {
      state = State::OFF;
    }

    void blink(byte blinkCount) {
      remainingBlinks = blinkCount;
      // Serial.print("BLINK: remainingBlinks = ");
      // Serial.println(remainingBlinks);
      previousState = state;
      state = State::BLINKING;
    }
};

#endif