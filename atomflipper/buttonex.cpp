// Copyright 2020 kmgnkhr

#include "buttonex.h"

namespace {

enum ScanPhase {
  kIdle,
  kWaitRelease,
  kWaitPress,
};

const uint32_t kSleepInterval = 5*60*1000;
const uint32_t kDetectTerm = 150;

}  // namespace

M5Ex::ButtonEx::ButtonEx(Button* button) : button_(*button) {
}

void M5Ex::ButtonEx::begin() {
  phase_ = kIdle;
  last_period_ = begin_time_ = ::millis();
}

int M5Ex::ButtonEx::scan() {
  const auto now = ::millis();
  const auto delta = now - last_period_;

  auto clicks = 0;
  auto next = phase_;

  switch (phase_) {
    case kIdle:
      if (button_.wasPressed()) {
        next = kWaitRelease;
      }
      break;
    case kWaitRelease:
      if (button_.wasReleased()) {
        next = kWaitPress;
      } else if (delta > kDetectTerm) {
        clicks = 1;
      }
      break;
    case kWaitPress:
      if (button_.wasPressed()) {
        clicks = 2;
      } else if (delta > kDetectTerm) {
        clicks = 1;
      }
      break;
  }

  if (clicks > 0) {
    next = kIdle;
  }

  if (next != phase_) {
    phase_ = next;
    last_period_ = now;
  }
  return clicks;
}

bool M5Ex::ButtonEx::isReadyForSleep() const {
  auto last = button_.lastChange();
  if (last <= 0) {
    last = begin_time_;
  }
  return (::millis() - last) > kSleepInterval;
}
