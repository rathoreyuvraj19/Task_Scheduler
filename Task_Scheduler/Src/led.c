/* led.c */
#include "led.h"

/* ── led_init ────────────────────────────────────────────────────────────────
 * Enable GPIOD clock and configure PD12-PD15 as general purpose output pins.
 * MODER register: 2 bits per pin
 *   00 = input, 01 = output, 10 = alternate function, 11 = analog
 * We write 01 into bits [25:24], [27:26], [29:28], [31:30]                   */
void led_init(void)
{
    /* 1. Enable GPIOD peripheral clock via RCC AHB1ENR                       */
    RCC_AHB1ENR |= RCC_GPIODEN;

    /* 2. Small delay to let clock stabilize (read back)                      */
    volatile uint32_t dummy = RCC_AHB1ENR;
    (void)dummy;

    /* 3. Clear MODER bits for PD12-PD15 (2 bits each = 8 bits total)        */
    GPIOD_MODER &= ~(0xFFU << 24);

    /* 4. Set PD12-PD15 as outputs (01 per pin)                               */
    GPIOD_MODER |=  (0x55U << 24);
    /*   0x55 = 0101 0101 in binary
     *   bits [25:24] = 01 → PD12 output
     *   bits [27:26] = 01 → PD13 output
     *   bits [29:28] = 01 → PD14 output
     *   bits [31:30] = 01 → PD15 output                                      */

    /* 5. Make sure all LEDs start off                                         */
    led_all_off();
}

/* ── led_on ──────────────────────────────────────────────────────────────────
 * Turn on a single LED.
 * BSRR bits [15:0]  = set bits  (write 1 to set the pin HIGH)
 * BSRR bits [31:16] = reset bits(write 1 to set the pin LOW)
 * Using BSRR is atomic — no read-modify-write needed.                        */
void led_on(LED_Id led)
{
    GPIOD_BSRR = (1U << (uint32_t)led);   /* set bit → pin HIGH → LED ON      */
}

/* ── led_off ─────────────────────────────────────────────────────────────────
 * Turn off a single LED.
 * Write to upper 16 bits of BSRR (reset side) to drive pin LOW.             */
void led_off(LED_Id led)
{
    GPIOD_BSRR = (1U << ((uint32_t)led + 16U)); /* reset bit → pin LOW → OFF  */
}

/* ── led_toggle ──────────────────────────────────────────────────────────────
 * Toggle a single LED.
 * Read current ODR state and flip the relevant bit.                          */
void led_toggle(LED_Id led)
{
    GPIOD_ODR ^= (1U << (uint32_t)led);
}

/* ── led_all_on ──────────────────────────────────────────────────────────────
 * Turn on all 4 LEDs at once atomically using BSRR.                         */
void led_all_on(void)
{
    GPIOD_BSRR = LED_ALL_PINS;             /* set PD12-PD15 HIGH               */
}

/* ── led_all_off ─────────────────────────────────────────────────────────────
 * Turn off all 4 LEDs at once atomically using BSRR reset side.            */
void led_all_off(void)
{
    GPIOD_BSRR = (LED_ALL_PINS << 16U);   /* reset PD12-PD15 LOW              */
}

/* ── led_all_toggle ──────────────────────────────────────────────────────────
 * Toggle all 4 LEDs at once.                                                */
void led_all_toggle(void)
{
    GPIOD_ODR ^= LED_ALL_PINS;
}
