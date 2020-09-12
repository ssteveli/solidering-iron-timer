#include <Arduino.h>
#include <Bounce2.h>
#include <Ticker.h>

#define BUTTON_PIN 2
#define SWITCH_PIN 4
#define LED_PIN 13

Bounce * button = new Bounce();

int ledState = LOW;

void powerOff() {
  ledState = LOW;
  digitalWrite(LED_PIN, ledState);
  digitalWrite(SWITCH_PIN, ledState);
}

Ticker timer(powerOff, 1000 * 60 * 30);

void setup() {
  button->attach(BUTTON_PIN , INPUT_PULLUP);
  button->interval(25);             

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  digitalWrite(SWITCH_PIN, ledState);
}

void loop() {
  bool needToToggleLed = false;
  button->update();
  timer.update();

  if (button->fell()) {
    needToToggleLed = true;
  }
  
  if ( needToToggleLed ) {
    if (ledState == LOW) {
      timer.start();
    } else {
      timer.stop();
    }

    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    digitalWrite(SWITCH_PIN, ledState);
  }
}