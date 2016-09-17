/*
 * SystemControl.cpp
 *
 *  Created on: 17.09.2016
 *      Author: mik
 */

#include "SystemControl.h"

namespace mkstm32 {

unsigned int SystemControl::systemTimer;

}


extern "C" {
/**
 * @brief Interrupt handler for SysTick.
 */
void SysTick_Handler(void) {
  mkstm32::SystemControl::increaseSystemTimer();
}
}
