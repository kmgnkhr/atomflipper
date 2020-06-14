// Copyright 2020 kmgnkhr

#include <M5Atom.h>
#include <BleKeyboard.h>

#include "buttonex.h"

namespace {

BleKeyboard bleKeyboard("AtomFlipper");

M5Ex::ButtonEx button(&M5.Btn);

void enter_sleep() {
  pinMode(GPIO_NUM_39, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_39, LOW);
  esp_deep_sleep_start();
}

}  // namespace

void setup() {
  M5.begin(false, false, true);
  M5.dis.setBrightness(5);
  M5.dis.clear();

  switch (esp_sleep_get_wakeup_cause()) {
    case ESP_SLEEP_WAKEUP_EXT0:
    case ESP_SLEEP_WAKEUP_EXT1:
    case ESP_SLEEP_WAKEUP_TIMER:
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
    case ESP_SLEEP_WAKEUP_ULP:
    case ESP_SLEEP_WAKEUP_GPIO:
    case ESP_SLEEP_WAKEUP_UART:
      break;
    default:
      enter_sleep();
      break;
  }
  bleKeyboard.begin();
  button.begin();
  M5.dis.drawpix(0, 0xff0000);
}

void loop() {
  M5.update();

  if (button.isReadyForSleep()) {
    M5.dis.clear();
    delay(100);
    enter_sleep();
  }

  switch (button.scan()) {
    case 1:
      bleKeyboard.write(KEY_LEFT_ARROW);
      break;
    case 2:
      bleKeyboard.write(KEY_RIGHT_ARROW);
      break;
  }
}
