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

/**
 * @brief
 * @param gpioPort Port name
 * @param gpioPin Pin number
 * @param gpioMode Mode of GPIO
 */
Gpio::Gpio(GpioPortName gpioPort, GpioPin gpioPin, GpioMode gpioMode,
    GpioSpeed gpioSpeed, GpioOutputType gpioOutputType,
    GpioPull gpioPull, GpioAlternateFunction gpioAlternateFunction) {

  this->gpioPort = gpioPort;
  this->gpioPin = (1 << gpioPin);
  this->gpioMode = gpioMode;

  enableGpioClock(gpioPort);

  unsigned int moderRegisterValue = getGpioType(gpioPort)->MODER;
  moderRegisterValue &= ~(GPIO_MODER_MODER0 << (gpioPin * 2));
  moderRegisterValue |= (gpioMode << (gpioPin * 2));
  getGpioType(gpioPort)->MODER = moderRegisterValue;

  unsigned int outputTypeRegisterValue = getGpioType(gpioPort)->OTYPER;
  outputTypeRegisterValue &= ~(GPIO_OTYPER_ODR_0 << gpioPin);
  outputTypeRegisterValue |= (gpioOutputType << gpioPin);
  getGpioType(gpioPort)->OTYPER = outputTypeRegisterValue;

  unsigned int speedTypeRegisterValue = getGpioType(gpioPort)->OSPEEDR;
  speedTypeRegisterValue &= ~(GPIO_OSPEEDER_OSPEEDR0 << (gpioPin*2));
  speedTypeRegisterValue |= (gpioSpeed << gpioPin);
  getGpioType(gpioPort)->OSPEEDR = speedTypeRegisterValue;

  const int ARFL_REGISTER_RANGE = 7;
  if (gpioPin <= ARFL_REGISTER_RANGE) {
    unsigned int alternateFunctionRegisterValue = getGpioType(gpioPort)->AFR[0];
    alternateFunctionRegisterValue &= ~(0xf << (gpioPin*4));
    alternateFunctionRegisterValue |= (gpioAlternateFunction << (gpioPin*4));
    getGpioType(gpioPort)->AFR[0] = alternateFunctionRegisterValue;
  } else {
    unsigned int alternateFunctionRegisterValue = getGpioType(gpioPort)->AFR[1];
    alternateFunctionRegisterValue &= ~(0xf << (gpioPin*4));
    alternateFunctionRegisterValue |= (gpioAlternateFunction << (gpioPin*4));
    getGpioType(gpioPort)->AFR[1] = alternateFunctionRegisterValue;
  }


}

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


