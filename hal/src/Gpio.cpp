/**
 * @file    gpio.cpp
 * @brief
 * @date    11 wrz 2016
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

#include "Gpio.h"

namespace mkstm32 {

void Gpio::enableGpioClock(GpioPortName port) {

  unsigned int bit;

  switch (port) {
  case GPIO_PORT_A:
    bit = RCC_AHB1ENR_GPIOAEN;
    break;

  case GPIO_PORT_B:
    bit = RCC_AHB1ENR_GPIOBEN;
    break;

  case GPIO_PORT_C:
    bit = RCC_AHB1ENR_GPIOCEN;
    break;

  case GPIO_PORT_D:
    bit = RCC_AHB1ENR_GPIODEN;
    break;

  case GPIO_PORT_E:
    bit = RCC_AHB1ENR_GPIOEEN;
    break;

  default:
    return;

  }

  RCC->AHB1ENR |= bit;
  bit &= RCC->AHB1ENR;
}

GPIO_TypeDef* Gpio::getGpioType(GpioPortName port) {

  switch (port) {
  case GPIO_PORT_A:
    return GPIOA;
  case GPIO_PORT_B:
    return GPIOB;
  case GPIO_PORT_C:
    return GPIOC;
  case GPIO_PORT_D:
    return GPIOD;
  case GPIO_PORT_E:
    return GPIOE;
  default:
    return GPIOA;
  }
}

}


