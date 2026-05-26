/*
 * SysTick.h
 *
 *  Created on: May 17, 2026
 *      Author: ratho
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdint.h>
#include <stdio.h>

// SysTick registers

#define SYSTICK_TIM_CLK  16000000U

#define STRVR (*((volatile uint32_t*)0xE000E014))
#define STCSR (*((volatile uint32_t*)0xE000E010))
#define STCVR   (*((volatile uint32_t*)0xE000E018))  // current value

// DWT registers
#define DEMCR           (*(volatile uint32_t*)0xE000EDFC)
#define DWT_CTRL        (*(volatile uint32_t*)0xE0001000)
#define DWT_CYCCNT      (*(volatile uint32_t*)0xE0001004)

void timestamp_init(void);
void sysTick_init(uint32_t tick_hz);
#endif /* SYSTICK_H_ */
