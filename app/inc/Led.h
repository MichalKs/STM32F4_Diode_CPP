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

/**
 * @brief LED class
 */
class Led {

public:
  /**
   * @brief State of the LED
   */
  enum LedState {
    LED_OFF,//!< LED_OFF
    LED_ON  //!< LED_ON
  };
  /**
   * @brief Sets LED to active high or low
   */
  enum LedActiveLevel {
    ACTIVE_LOW, //!< ACTIVE_LOW
    ACTIVE_HIGH,//!< ACTIVE_HIGH
  };
  /**
   * @brief This function initalizes the LED by initalizing the GPIO
   * @param gpioPort Port of the LED
   * @param gpioPin Pin number of the LED
   */
  Led(Gpio::GpioPortName gpioPort, int gpioPin, LedActiveLevel ledActiveLevel = ACTIVE_HIGH):
    gpio(gpioPort, gpioPin, Gpio::GPIO_MODE_OUTPUT) {
    this->ledActiveLevel = ledActiveLevel;
    off(); // turn the LED off initially
  }
  /**
   * @brief Turn LED on
   */
  void on() {
    if (ledActiveLevel == ACTIVE_HIGH) {
      gpio.on();
    } else {
      gpio.off();
    }
    ledState = LED_ON;
  }
  /**
   * @brief Turn LED off
   */
  void off() {
    if (ledActiveLevel == ACTIVE_HIGH) {
      gpio.off();
    } else {
      gpio.on();
    }
    ledState = LED_OFF;
  }
  /**
   * @brief Toggles LED state
   */
  void toggle() {
    if (ledState == LED_OFF) {
      on();
    } else {
      off();
    }
  }

private:
  Gpio gpio; ///< The GPIO of the LED
  LedState ledState; ///< The state of the LED
  LedActiveLevel ledActiveLevel; ///< Tells whether LED is active high or low

};

}

#endif /* APP_INC_LED_H_ */
