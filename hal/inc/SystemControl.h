/*
 * SystemTimer.h
 *
 *  Created on: 16.09.2016
 *      Author: mik
 */

#ifndef INC_SYSTEMCONTROL_H_
#define INC_SYSTEMCONTROL_H_

#include <stm32f4xx.h>

namespace mkstm32 {

class SystemControl {

public:

  static void init() {

    systemClockConfig();
    // enable instruction cache
    FLASH->ACR |= FLASH_ACR_ICEN;
    // enable data cache
    FLASH->ACR |= FLASH_ACR_DCEN;
    // enable prefetch
    FLASH->ACR |= FLASH_ACR_PRFTEN;

    /* Set Interrupt Group Priority */
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    SysTick_Config(SystemCoreClock/1000U);

    // Configure the SysTick IRQ priority
    unsigned int priorityGroup = NVIC_GetPriorityGrouping();
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(priorityGroup, 15, 0));
  }

  static void delayMillis(int millis) {
    unsigned int start = systemTimer;
    while((systemTimer - start) < millis);
  }

  static unsigned int getSystemTimer() {
    return systemTimer;
  }

  static void increaseSystemTimer() {
    systemTimer++;
  }

private:
  /**
    * @brief  System Clock Configuration
    *         The system Clock is configured as follows :
    *            AHB Prescaler                  = 1
    *            APB1 Prescaler                 = 4
    *            APB2 Prescaler                 = 2
    *            VDD(V)                         = 3.3
    *            Main regulator output voltage  = Scale1 mode
    *            Flash Latency(WS)              = 5
    */
  static void systemClockConfig() {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // enable HSE
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));

    // turn off PLL
    RCC->CR &= ~RCC_CR_PLLON;
    while (RCC->CR & RCC_CR_PLLRDY);

    unsigned int rccPllcfgrRegister = RCC->PLLCFGR;

    rccPllcfgrRegister |= RCC_PLLCFGR_PLLSRC_HSE;

    // PLL input clock is 1 MHz (HSE = 8 MHz)
    rccPllcfgrRegister &= ~RCC_PLLCFGR_PLLM;
    rccPllcfgrRegister |= (8<<0);

    // VCO output is 336 MHz
    rccPllcfgrRegister &= ~RCC_PLLCFGR_PLLN;
    rccPllcfgrRegister |= (336<<6);

    // Clock for USB, etc. is 48 MHz
    rccPllcfgrRegister &= ~RCC_PLLCFGR_PLLQ;
    rccPllcfgrRegister |= (7<<24);

    // set division by two of PLL clock to obtain system clock
    // => system clock is 168 MHz (SYSCLK, HCLK)
    rccPllcfgrRegister &= ~RCC_PLLCFGR_PLLP;

    RCC->PLLCFGR = rccPllcfgrRegister;

    // turn on PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
       clocks dividers */
    RCC_ClkInitStruct.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider   = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider  = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider  = RCC_HCLK_DIV2;
    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    }

  }

  static unsigned int systemTimer;

};

}


#endif /* INC_SYSTEMCONTROL_H_ */
