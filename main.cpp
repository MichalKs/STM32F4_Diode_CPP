/**
 * @file    main.cpp
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

#include <SystemControl.h>
#include "Led.h"
#include "Gpio.h"

using namespace mkstm32;

int main(void) {

  const int BLINK_DELAY = 500;

  SystemControl::init();

  Led orangeLed(Gpio::GPIO_PORT_D, Gpio::GPIO_PIN_NO_13, Led::ACTIVE_HIGH);
  orangeLed.on();

  while(1) {
    orangeLed.on();
    SystemControl::delayMillis(BLINK_DELAY);
    orangeLed.off();
    SystemControl::delayMillis(BLINK_DELAY);
  }

  return 0;
}
