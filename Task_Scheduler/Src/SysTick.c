/*
 * SysTick.c
 *
 *  Created on: May 17, 2026
 *      Author: ratho
 */


#include "SysTick.h"

void timestamp_init(void)
{
    /* Enable trace */
    DEMCR |= (1 << 24);

    /* Reset counter */
    DWT_CYCCNT = 0;

    /* Enable cycle counter */
    DWT_CTRL |= (1 << 0);
}

void sysTick_init(uint32_t tick_hz){

    // set PendSV to lowest priority
    *(volatile uint32_t*)0xE000ED22 = 0xFF;   // SHPR3 PendSV priority byte

	STRVR = SYSTICK_TIM_CLK/tick_hz-1;
    // clear current value
    STCVR = 0;
	STCSR |= 0x7;
}


