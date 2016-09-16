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

#include <stm32f407xx.h>

namespace mkstm32 {

/**
 * @brief GPIO pin class
 */
class Gpio {

public:
  /**
   * @brief Port name
   */
  enum GpioPortName {
    GPIO_PORT_A,//!< GPIO_PORT_A
    GPIO_PORT_B,//!< GPIO_PORT_B
    GPIO_PORT_C,//!< GPIO_PORT_C
    GPIO_PORT_D,//!< GPIO_PORT_D
    GPIO_PORT_E,//!< GPIO_PORT_E
  };
  /**
   * @brief Gpio mode
   */
  enum GpioMode {
    GPIO_MODE_IN = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALTERNATE = 2,
    GPIO_MODE_ANALOGUE = 3,
  };

  enum GpioOutputType {
    GPIO_PUSH_PULL = 0,
    GPIO_OPEN_DRAIN = 1,
  };

  enum GpioSpeed {
    GPIO_LOW_SPEED = 0,
    GPIO_MEDIUM_SPEED = 1,
    GPIO_FAST_SPEED = 2,
    GPIO_HIGH_SPEED = 3,
  };
  /**
   * @brief
   * @param gpioPort Port name
   * @param gpioPin Pin number
   * @param gpioMode Mode of GPIO
   */
  Gpio(GpioPortName gpioPort, unsigned int gpioPin, GpioMode gpioMode,
      GpioSpeed gpioSpeed = GPIO_LOW_SPEED,
      GpioOutputType gpioOutputType = GPIO_PUSH_PULL) {

    this->gpioPort = gpioPort;
    this->gpioPin = (1 << gpioPin);
    this->gpioMode = gpioMode;

    enableGpioClock(gpioPort);

    unsigned int moderRegisterValue = getGpioType(gpioPort)->MODER;
    moderRegisterValue &= ~(GPIO_MODER_MODER0 << (gpioPin * 2u));
    moderRegisterValue |= (gpioMode << (gpioPin * 2u));
    getGpioType(gpioPort)->MODER = moderRegisterValue;

    unsigned int outputTypeRegisterValue = getGpioType(gpioPort)->OTYPER;
    outputTypeRegisterValue &= ~(GPIO_OTYPER_ODR_0 << gpioPin);
    outputTypeRegisterValue |= (gpioOutputType << gpioPin);
    getGpioType(gpioPort)->OTYPER = outputTypeRegisterValue;

    unsigned int speedTypeRegisterValue = getGpioType(gpioPort)->OSPEEDR;
    speedTypeRegisterValue &= ~(GPIO_OSPEEDER_OSPEEDR0 << gpioPin);
    speedTypeRegisterValue |= (gpioSpeed << gpioPin);
    getGpioType(gpioPort)->OSPEEDR = speedTypeRegisterValue;

  }
  /**
   * @brief Set GPIO high
   */
  void on() {
    getGpioType(gpioPort)->BSRR = (gpioPin << 16);
  }
  /**
   * @brief Set GPIO low
   */
  void off() {
    getGpioType(gpioPort)->BSRR = gpioPin;
  }

private:
  /**
   * @brief Enables the GPIO clock
   * @param port Port to enable
   */
  void enableGpioClock(GpioPortName port);
  /**
   * @brief Get ST GPIO type
   * @param port Port name
   * @return The ST GPIO type
   */
  GPIO_TypeDef* getGpioType(GpioPortName port);

  GpioPortName gpioPort; ///< GPIO port name
  unsigned int gpioPin; ///< GPIO pin number
  GpioMode gpioMode; ///< Gpio mode
};

}

#endif /* INC_GPIO_H_ */
