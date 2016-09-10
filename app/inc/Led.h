/**
 * @file    Led.h
 * @brief
 * @date    10 wrz 2016
 * @author  Michal Ksiezopolski
 *
 *
 * @verbatim
 * Copyright (c) 2014 Michal Ksiezopolski.
 * All rights reserved. This program and the
 * accompanying materials are made available
 * under the terms of the GNU Public License
 * v3.0 which accompanies this distribution,
 * and is available at
 * http://www.gnu.org/licenses/gpl.html
 * @endverbatim
 */
#ifndef APP_INC_LED_H_
#define APP_INC_LED_H_

#include "Gpio.h"

namespace mkstm32 {

class Led {

public:

  enum LedState {
    LED_OFF,
    LEN_ON
  };

  Led(Gpio gpio): gpio(gpio) {

  }

  void on() {
    gpio.on();
  }

  void off() {
    gpio.off();
  }

private:

  Gpio gpio;

};

}

#endif /* APP_INC_LED_H_ */
