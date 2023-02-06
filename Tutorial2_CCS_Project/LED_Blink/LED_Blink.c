#include <stdint.h>
#include "msp.h"
#include "..\inc\SysTick.h"

void LED1_Init()
{
    // Initialize P1.0 and make it output (P1.0 built-in red LED)
    P1->SEL0 &= ~0x01;
    // Configure built-in red LED as GPIO
    P1->SEL1 &= ~0x01;
    // Make the built-in red LED out
    P1->DIR |= 0x01;
}

int LED1_Output(uint8_t led_status)
{
    P1->OUT = led_status;

    if (led_status != 0)
        return 1;
    else
        return 0;
}

void LED2_Init()
{
    // Configure P2.2-P2.0 as GPIO
    P2->SEL0 = 0x00;
    P2->SEL1 = 0x00;
    // Make P2.2-P2.0 High Drive Strength
    P2->DS = 0x07;
    // Set P2.2-P2.0 as output
    P2->DIR = 0x07;
    // Set LED off
    P2->OUT = 0x00;
}

int LED2_Output(uint8_t led_color)
{
    P2->OUT = led_color;

    if (led_color != 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int main(void) {
    // Initialize SysTick timer
    SysTick_Init();

    // Initialize LED 1 and LED 2
    LED1_Init();
    LED2_Init();

    while(1) {
        int LED1_Status = LED1_Output(0x00);
        int LED2_Status = LED2_Output(0x00);
        SysTick_Wait(2400000);
        LED1_Status = LED1_Output(0x01);
        LED2_Status = LED2_Output(0x04);
        SysTick_Wait(2400000);
    }
}
