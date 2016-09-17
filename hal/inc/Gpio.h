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
  enum GpioMode {
    GPIO_MODE_IN,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOGUE,
  };

  enum GpioOutputType {
    GPIO_PUSH_PULL,
    GPIO_OPEN_DRAIN,
  };

  enum GpioSpeed {
    GPIO_LOW_SPEED,
    GPIO_MEDIUM_SPEED,
    GPIO_FAST_SPEED,
    GPIO_HIGH_SPEED,
  };

  enum GpioPull {
    GPIO_NO_PULL,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN,
  };

  enum GpioPin {
    GPIO_PIN_NO_0,
    GPIO_PIN_NO_1,
    GPIO_PIN_NO_2,
    GPIO_PIN_NO_3,
    GPIO_PIN_NO_4,
    GPIO_PIN_NO_5,
    GPIO_PIN_NO_6,
    GPIO_PIN_NO_7,
    GPIO_PIN_NO_8,
    GPIO_PIN_NO_9,
    GPIO_PIN_NO_10,
    GPIO_PIN_NO_11,
    GPIO_PIN_NO_12,
    GPIO_PIN_NO_13,
    GPIO_PIN_NO_14,
    GPIO_PIN_NO_15,
  };

  enum GpioAlternateFunction {
    GPIO_AF_0,
    GPIO_AF_1,
    GPIO_AF_2,
    GPIO_AF_3,
    GPIO_AF_4,
    GPIO_AF_5,
    GPIO_AF_6,
    GPIO_AF_7,
    GPIO_AF_8,
    GPIO_AF_9,
    GPIO_AF_10,
    GPIO_AF_11,
    GPIO_AF_12,
    GPIO_AF_13,
    GPIO_AF_14,
    GPIO_AF_15,
  };

  /**
   * @brief GPIO constructor
   * @param gpioPort Port name
   * @param gpioPin Pin number
   * @param gpioMode Pin mode
   * @param gpioSpeed Output pin speed
   * @param gpioOutputType Output Pin type
   * @param gpioPull Pullup or pulldown
   * @param gpioAlternateFunction Alternate function number
   */
  Gpio(GpioPortName gpioPort, GpioPin gpioPin, GpioMode gpioMode,
      GpioSpeed gpioSpeed = GPIO_LOW_SPEED,
      GpioOutputType gpioOutputType = GPIO_PUSH_PULL,
      GpioPull gpioPull = GPIO_NO_PULL,
      GpioAlternateFunction gpioAlternateFunction = GPIO_AF_0);

  /**
   * @brief Set GPIO high
   */
  void on() {
    getGpioType(gpioPort)->BSRR = gpioPin;
  }
  /**
   * @brief Set GPIO low
   */
  void off() {
    const int RESET_BITS_OFFSET = 16;
    getGpioType(gpioPort)->BSRR = (gpioPin << RESET_BITS_OFFSET);
  }
  /**
   * @brief Read data on pin
   * @retval true Pin is set
   * @retval false Pin is reset
   */
  bool read() {
    unsigned int portValues = getGpioType(gpioPort)->IDR;
    if (portValues & gpioPin) {
      return true;
    } else {
      return false;
    }
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

  GpioPortName gpioPort;  ///< GPIO port name
  unsigned int gpioPin;   ///< GPIO pin number
  GpioMode gpioMode;      ///< Gpio mode
};

}

#endif /* INC_GPIO_H_ */
