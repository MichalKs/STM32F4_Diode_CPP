/**
 * @file    Gpio.h
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
#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <stm32f4xx.h>

namespace mkstm32 {

class Gpio {

public:
  enum GpioPortName {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,

  };

  enum GpioMode {
    GPIO_MODE_IN,
    GPIO_MODE_OUT_OPEN_DRAIN,
    GPIO_MODE_OUT_PUSH_PULL,
  };

  Gpio(GpioPortName gpioPort, int gpioPin, GpioMode gpioMode) {
    this->gpioPort = gpioPort;
    this->gpioPin = gpioPin;
    this->gpioMode = gpioMode;

    enableGpioClock(gpioPort);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = 1<<(uint16_t)gpioPin;

    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  }

  Gpio(const Gpio& model) {
    this->gpioPort = model.gpioPort;
    this->gpioPin = model.gpioPin;
    this->gpioMode = model.gpioMode;
  }

  void on() {
    HAL_GPIO_WritePin(GPIOD, 1<<(uint16_t)gpioPin, GPIO_PIN_SET);
  }
  void off() {
    HAL_GPIO_WritePin(GPIOD, 1<<(uint16_t)gpioPin, GPIO_PIN_RESET);
  }

private:

  void enableGpioClock(GpioPortName port) {

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

  GpioPortName gpioPort;
  int gpioPin;
  GpioMode gpioMode;
};

}



#endif /* INC_GPIO_H_ */
