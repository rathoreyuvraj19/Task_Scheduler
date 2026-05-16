# Bare-Metal Task Scheduler for ARM Cortex-M4

A lightweight **preemptive/cooperative task scheduler** built from scratch for ARM Cortex-M microcontrollers using pure Embedded C and low-level context switching mechanisms like **SysTick** and **PendSV**.

This project was created to deeply understand how an RTOS actually works internally instead of just using FreeRTOS as a black box.

Based on concepts like:

- Context switching
- PSP/MSP stack separation
- PendSV exception handling
- SysTick driven scheduling
- Task Control Blocks (TCB)
- Round-robin scheduling
- Blocking and task delays

Inspired by real RTOS kernel architecture used in systems like FreeRTOS.

---

# Features

- Cooperative scheduling
- Preemptive scheduling
- Round-robin task execution
- Independent stack per task
- Task blocking using `task_delay()`
- Context switching using PendSV
- SysTick based periodic scheduler tick
- TCB (Task Control Block) implementation
- Cortex-M4 PSP/MSP stack management
- Pure bare-metal implementation
- No HAL
- No RTOS libraries

---

# Target Platform

- ARM Cortex-M4
- STM32 / Cortex-M based MCUs
- Written in Embedded C + ARM Assembly

---

# Why This Project?

Most developers use an RTOS without understanding what happens internally.

This project was built to understand:

- How task switching actually works
- How registers are saved/restored
- Why PendSV exists
- Why Cortex-M has MSP and PSP
- How an RTOS creates the illusion of multitasking
- How schedulers manage READY/BLOCKED/RUNNING tasks

The goal is educational clarity rather than production-grade optimization.

---

# Scheduler Architecture

## Cooperative Scheduling

Tasks voluntarily yield CPU control.

```c
while(1)
{
    process_data();
    task_yield();
}
```

Simple but unsafe if a task never yields.

---

## Preemptive Scheduling

A hardware timer interrupt forces task switching periodically.

Flow:

```text
SysTick Interrupt
        ↓
PendSV Triggered
        ↓
Current Task Context Saved
        ↓
Next Task Selected
        ↓
Next Task Context Restored
```

This is the same architecture used in real RTOS kernels.

---

# Context Switching

The Cortex-M hardware automatically saves:

- R0–R3
- R12
- LR
- PC
- xPSR

The scheduler manually saves:

- R4–R11

Total task context:

```text
16 Registers × 4 Bytes = 64 Bytes
```

---

# MSP vs PSP

Cortex-M processors provide two stack pointers:

## MSP (Main Stack Pointer)

Used by:

- Kernel
- ISRs
- Exception handlers

## PSP (Process Stack Pointer)

Used by:

- User tasks

Each task gets its own private PSP stack.

This prevents user tasks from corrupting kernel stack memory.

---

# Task Control Block (TCB)

```c
typedef struct{
    uint32_t *stackPointer;
    uint32_t *stackBase;
    uint32_t stackSize;
    TaskState_t state;
    uint8_t priority;
    int32_t delayTicks;
    const char *name;
} TCB_t;
```

The TCB stores all information related to a task.

---

# Task States

Each task can be:

| State | Description |
|---|---|
| READY | Waiting to run |
| RUNNING | Currently executing |
| BLOCKED | Waiting for delay/resource |

---

# Scheduling Algorithm

Currently implemented:

- Round Robin Scheduling

Planned:

- Priority-based preemptive scheduling
- Priority + Round Robin hybrid
- Dynamic priority scheduling

---

# Blocking and Delays

Instead of wasting CPU cycles using busy-wait loops:

```c
for(volatile int i=0;i<100000;i++);
```

Tasks can sleep efficiently:

```c
task_delay(500);
```

The scheduler skips blocked tasks entirely.

---

# Project Structure

```text
.
├── Core/
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── task.c
│   ├── task.h
│   ├── context_switch.s
│   └── main.c
│
├── Drivers/
│
├── Startup/
│
└── README.md
```

---

# Concepts Covered

This project demonstrates:

- ARM exception model
- PendSV internals
- SysTick timer
- Stack frame initialization
- Fake stack frame creation
- EXC_RETURN behavior
- CPU register preservation
- Task lifecycle management
- Bare-metal multitasking

---

# Future Improvements

- Mutex implementation
- Semaphore support
- Priority inversion handling
- Software timers
- Event flags
- Message queues
- Dynamic memory allocation
- Tickless idle mode
- SMP scheduling concepts
- EDF scheduling

---

# Learning Outcomes

After building this project, you will understand:

- How FreeRTOS works internally
- How operating systems perform multitasking
- Cortex-M exception handling
- Low-level ARM debugging
- Embedded kernel architecture
- Real-time scheduling concepts

---

# References

- ARM Cortex-M4 Technical Reference Manual
- ARMv7-M Architecture Reference Manual
- FreeRTOS Kernel Source Code
- STM32 Reference Manuals

---

# Author

Yuvraj Singh Rathore  
Embedded Systems Engineer | DRDO | FPGA + Embedded Systems Enthusiast

GitHub: add-your-link-here

---

# License

This project is open-source under the MIT License.
