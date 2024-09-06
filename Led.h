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
  int blinkInterval = 150;
  unsigned long last_blink_time = 0;
  unsigned long timeSinceLastBlink = 0;

  private:
    void blinkOn() {
      timeSinceLastBlink = millis() - last_blink_time;

      if (remainingBlinks > 0 && timeSinceLastBlink > blinkInterval) {
        digitalWrite(pin, HIGH);
        last_blink_time = millis();
        state = State::BLINKING_OFF;
      }
    }

    void blinkOff() {
      timeSinceLastBlink = millis() - last_blink_time;

      if (remainingBlinks > 0 && timeSinceLastBlink > blinkInterval) {
        remainingBlinks--;
        last_blink_time = millis();
        // blink off
        digitalWrite(pin, LOW);
        state = State::BLINKING_ON;
      }

      // if no blinks left, reset state to previous state
      // otherwise, set to blinking on
      if (remainingBlinks <= 0) {
        state = previousState;
        remainingBlinks = 0;
      }
    }
  
  public:
    Led(byte attachToPin) : pin(attachToPin) {};

    void setup() {
      pinMode(pin, OUTPUT);
    }

    void loop() {
      switch (state) {
        case State::ON:
          digitalWrite(pin, HIGH);
          break;
        case State::OFF:
          digitalWrite(pin, LOW);
          break;
        case State::BLINKING:
          state = State::BLINKING_ON;
          break;
        case State::BLINKING_ON:
          blinkOn();
          break;
        case State::BLINKING_OFF:
          blinkOff();
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
      previousState = state;
      state = State::BLINKING;
    }
};

#endif