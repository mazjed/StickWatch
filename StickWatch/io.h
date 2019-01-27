#ifndef _IO_H_
#define _IO_H_

#include "config.h"

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile int interruptCounter = 0;

// declare key event callback function
void onKeyDown();
void onKeyUp();

void setPinModes() {
  // pinMode(BtnPin, INPUT_PULLDOWN);  // m5stick其实硬件上自带了 外部上拉电阻，貌似可以不要下面这行
  pinMode(BtnPin, INPUT_PULLUP);
  pinMode(LedPin, OUTPUT);
  pinMode(BuzzerPin, OUTPUT);

  pinMode(BatterySensorPin, INPUT);
  // analogReadResolution(12); // no need
}

void readBatteryVoltage(float *batteryVoltage, int *dacValue) {
  int sum = 0;
  for (int i = 0; i < SamplesCount; i++) {
    sum + = analogRead(BatterySensorPin);
  }
  int value = sum / SamplesCount;
  *dacValue = value;
  *batteryVoltage = (20.0 + 68.0) / 68.0 * 3.3 * value / 4096.0;
}

/**
  void IRAM_ATTR handle_btn_isr() {
  // TODO need mutex?
  //portENTER_CRITICAL_ISR(&mux);
  if (digitalRead(BtnPin) == LOW) {
    Serial.println("handle_btn_isr: button key down");
    onKeyDown();
  } else {
    Serial.println("handle_btn_isr: button key up");
    onKeyUp();
  }
  interruptCounter++;
  //portEXIT_CRITICAL_ISR(&mux);
  }

  void attachButtonEvent() {
  attachInterrupt(digitalPinToInterrupt(BtnPin), handle_btn_isr, CHANGE);
  }
*/

void buzzer() {
  for (int i = 0; i < 200; i++) {
    digitalWrite(BuzzerPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(BuzzerPin, LOW);
    delayMicroseconds(980);
  }
}

void led(boolean on, int milliseconds) {
  digitalWrite(LedPin, on ? 1 : 0);
  delay(milliseconds);
}

void flashLed(int milliseconds) {
  for (int i = 0; i < milliseconds / 200; i++) {
    digitalWrite(LedPin, 1);
    delay(100);
    digitalWrite(LedPin, 0);
    delay(100);
  }
}

#endif // _IO_H_
