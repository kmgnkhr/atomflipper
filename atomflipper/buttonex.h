// Copyright 2020 kmgnkhr

#ifndef BUTTONEX_H_
#define BUTTONEX_H_

#include "utility/Button.h"

namespace M5Ex {

class ButtonEx {
 public:
  explicit ButtonEx(Button* button);
  void begin();
  int scan();
  bool isReadyForSleep() const;
 private:
  Button& button_;
  int phase_;
  uint32_t last_period_, begin_time_;

  ButtonEx(const ButtonEx&);
  void operator=(const ButtonEx&);
};

}  // namespace M5Ex

#endif  // BUTTONEX_H_
