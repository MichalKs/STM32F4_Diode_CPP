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
    GPIO_MODE_IN,            //!< GPIO_MODE_IN
    GPIO_MODE_OUT_OPEN_DRAIN,//!< GPIO_MODE_OUT_OPEN_DRAIN
    GPIO_MODE_OUT_PUSH_PULL, //!< GPIO_MODE_OUT_PUSH_PULL
  };
  /**
   * @brief
   * @param gpioPort Port name
   * @param gpioPin Pin number
   * @param gpioMode Mode of GPIO
   */
  Gpio(GpioPortName gpioPort, unsigned int gpioPin, GpioMode gpioMode) {
    this->gpioPort = gpioPort;
    this->gpioPin = (1 << gpioPin);
    this->gpioMode = gpioMode;

    enableGpioClock(gpioPort);

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = this->gpioPin;

    HAL_GPIO_Init(getGpioType(gpioPort), &GPIO_InitStruct);

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
