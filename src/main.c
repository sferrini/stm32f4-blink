/*
 * This is a blink example using the stm32f4-template (https://github.com/sferrini/stm32f4-template)
 */

#include "stm32f4_discovery.h"

#define LEDS_GPIO_PORT (GPIOD)

#define GREEN  LED4_PIN
#define ORANGE LED3_PIN
#define RED    LED5_PIN
#define BLUE   LED6_PIN
#define ALL_LEDS (GREEN | ORANGE | RED | BLUE) // all leds

static uint16_t leds[LEDn] = {GREEN, ORANGE, RED, BLUE};

#define PAUSE_LONG  4000000L
#define PAUSE_SHORT 1000000L


static void delay(__IO uint32_t nCount)
{
    while(nCount--)
        __asm("nop"); // do nothing
}

static void leds_setup(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = ALL_LEDS;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStructure);
}

static void leds_round(void)
{
    int i;

    for (i = 0; i < LEDn; i++)
    {
        GPIO_SetBits(LEDS_GPIO_PORT, leds[i]);
        delay(PAUSE_LONG);
        GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
    }
}

static void leds_flash_all(void)
{
    int i;

    for (i = 0; i < LEDn; i++)
    {
        GPIO_SetBits(LEDS_GPIO_PORT, ALL_LEDS);
        delay(PAUSE_SHORT);
        GPIO_ResetBits(LEDS_GPIO_PORT, ALL_LEDS);
        delay(PAUSE_SHORT);
    }
}

int main(void)
{
    leds_setup();

    while (1)
    {
        leds_round();
        leds_flash_all();
    }

    return 0; // never returns actually
}
