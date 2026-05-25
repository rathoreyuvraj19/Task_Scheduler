/*
 * main.h
 *
 *  Created on: May 24, 2026
 *      Author: ratho
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include <stdio.h>
#include "SysTick.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#define SIZE_TASK_STACK 1024U
#define SIZE_SCHEDULER_STACK 1024U
#define MAX_TASKS 4

#define SRAM_START 0x20000000U
#define SRAM_SIZE ((1024)*(128)) //Bytes
#define SRAM_END  ((SRAM_START) + (SRAM_SIZE))

#define ICSR (*((volatile uint32_t*)0xE000ED04))


void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);


//volatile uint32_t timestamp;
//volatile uint32_t delta_cycles;
__attribute__((naked)) void init_scheduler_stack(uint32_t sch_top_of_stack_addr);

uint32_t* init_task_stack(uint32_t* sp, void (*task_fn)(void));
void init_tasks(void);
void enable_processor_faults(void);
__attribute__((naked)) void switch_sp_to_psp(void);
__attribute__((naked)) void start_first_task(void);

#endif /* MAIN_H_ */
