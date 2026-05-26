/* led.h */
#ifndef LED_H
#define LED_H

#include <stdint.h>

/* STM32F407 Discovery LED pins (all on GPIOD)
 * LD3 = PD13 = Orange
 * LD4 = PD12 = Green
 * LD5 = PD14 = Red
 * LD6 = PD15 = Blue                                                          */

/* RCC and GPIOD register base addresses                                       */
#define RCC_BASE        0x40023800U
#define GPIOD_BASE      0x40020C00U

/* RCC AHB1 peripheral clock enable register                                   */
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30U))
#define RCC_GPIODEN     (1U << 3)   /* bit3 = GPIOD clock enable               */

/* GPIOD registers                                                             */
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00U)) /* mode    */
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14U)) /* output  */
#define GPIOD_BSRR      (*(volatile uint32_t*)(GPIOD_BASE + 0x18U)) /* set/rst */

/* Pin numbers                                                                 */
#define LED_GREEN       12U   /* PD12 - LD4                                    */
#define LED_ORANGE      13U   /* PD13 - LD3                                    */
#define LED_RED         14U   /* PD14 - LD5                                    */
#define LED_BLUE        15U   /* PD15 - LD6                                    */

/* LED bitmasks for convenience                                                */
#define LED_GREEN_PIN   (1U << LED_GREEN)
#define LED_ORANGE_PIN  (1U << LED_ORANGE)
#define LED_RED_PIN     (1U << LED_RED)
#define LED_BLUE_PIN    (1U << LED_BLUE)
#define LED_ALL_PINS    (LED_GREEN_PIN | LED_ORANGE_PIN | LED_RED_PIN | LED_BLUE_PIN)

/* LED identifiers for use with API functions                                  */
typedef enum {
    LED_ID_GREEN  = LED_GREEN,
    LED_ID_ORANGE = LED_ORANGE,
    LED_ID_RED    = LED_RED,
    LED_ID_BLUE   = LED_BLUE
} LED_Id;

/* API declarations                                                            */
void led_init(void);
void led_on(LED_Id led);
void led_off(LED_Id led);
void led_toggle(LED_Id led);
void led_all_on(void);
void led_all_off(void);
void led_all_toggle(void);

#endif /* LED_H */
