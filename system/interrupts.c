/*
 * interrupts.c
 *
 *  Created on: 16.09.2016
 *      Author: mik
 */

#include <stm32f4xx.h>


/**
  * @brief   This function handles NMI exception.
  */
void NMI_Handler(void) {

}

/**
  * @brief  This function handles Hard Fault exception.
  */
void HardFault_Handler(void) {
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1) {

  }
}

/**
  * @brief  This function handles Memory Manage exception.
  */
void MemManage_Handler(void) {
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1) {

  }
}

/**
  * @brief  This function handles Bus Fault exception.
  */
void BusFault_Handler(void) {
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1) {

  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void) {
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1) {

  }
}

/**
  * @brief  This function handles SVCall exception.
  */
void SVC_Handler(void) {

}

/**
  * @brief  This function handles Debug Monitor exception.
  */
void DebugMon_Handler(void) {

}

/**
  * @brief  This function handles PendSVC exception.
  */
void PendSV_Handler(void) {

}

