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

#include "Led.h"
#include "Gpio.h"

using namespace mkstm32;

int main(void) {

  Gpio orangeLedGpio(Gpio::GPIO_PORT_D, 12, Gpio::GPIO_MODE_OUT_PUSH_PULL);

  Led orangeLed(orangeLedGpio);
  orangeLed.on();

  while(1) {

  }

  return 0;
}