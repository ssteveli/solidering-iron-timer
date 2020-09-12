#include <Arduino.h>
#include <Bounce2.h>
#include <Ticker.h>

#define BUTTON_PIN 2
#define SWITCH_PIN 4
#define LED_PIN 13

Bounce * button = new Bounce();

int powerState = LOW;

void powerOff() {
  powerState = LOW;
  digitalWrite(LED_PIN, powerState);
  digitalWrite(SWITCH_PIN, powerState);
}

Ticker timer(powerOff, 1000 * 60 * 30);

void setup() {
  button->attach(BUTTON_PIN , INPUT_PULLUP);
  button->interval(25);             

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, OUTPUT);
  digitalWrite(LED_PIN, powerState);
  digitalWrite(SWITCH_PIN, powerState);
}

void loop() {
  bool needToToggle = false;
  button->update();
  timer.update();

  if (button->fell()) {
    needToToggle = true;
  }
  
  if (needToToggle) {
    if (powerState == LOW) {
      timer.start();
    } else {
      timer.stop();
    }

    powerState = !powerState;
    digitalWrite(LED_PIN, powerState);
    digitalWrite(SWITCH_PIN, powerState);
  }
}