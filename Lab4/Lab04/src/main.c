/***********************************************************************
 * 
 * Stopwatch by Timer/Counter2 on the Liquid Crystal Display (LCD).
 *
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 * Components list:
 *   16x2 character LCD with parallel interface
 *     VSS  - GND (Power supply ground)
 *     VDD  - +5V (Positive power supply)
 *     Vo   - (Contrast)
 *     RS   - PB0 (Register Select: High for Data transfer, Low for Instruction transfer)
 *     RW   - GND (Read/Write signal: High for Read mode, Low for Write mode)
 *     E    - PB1 (Read/Write Enable: High for Read, falling edge writes data to LCD)
 *     D3:0 - NC (Data bits 3..0, Not Connected)
 *     D4   - PD4 (Data bit 4)
 *     D5   - PD5 (Data bit 5)
 *     D6   - PD6 (Data bit 6)
 *     D7   - PD7 (Data bit 7)
 *     A+K  - Back-light enabled/disabled by PB2
 * 
 **********************************************************************/


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Update stopwatch value on LCD screen when 8-bit 
 *           Timer/Counter2 overflows.
 * Returns:  none
 **********************************************************************/
#define N_CHARS 1

int main(void)
{
   // Custom character definition using https://omerk.github.io/lcdchargen/
   
    uint8_t mycustomChar[N_CHARS*8] = {
	      0b00000,
	      0b00000,
	      0b01010,
	      0b10101,
	      0b10101,
	      0b00100,
	      0b01010,
	      0b00100
    };
    // Initialize display
    lcd_init(LCD_DISP_ON);

    lcd_command(1<<LCD_CGRAM);       // Set addressing to CGRAM (Character Generator RAM)
                                     // ie to individual lines of character patterns
    for (uint8_t i = 0; i < N_CHARS*8; i++)  // Copy new character patterns line by line to CGRAM
        lcd_data(mycustomChar[i]);
    lcd_command(1<<LCD_DDRAM);   

    // Put string(s) on LCD screen
    //lcd_gotoxy(6, 1);
    //lcd_puts("LCD Test");
    //lcd_putc('!');

     // Configuration of 16-bit Timer/Counter1 for LED blinking
    TIM2_OVF_16MS
    TIM2_OVF_ENABLE
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose:  Update the stopwatch on LCD screen every sixth overflow,
 *           ie approximately every 100 ms (6 x 16 ms = 100 ms).
 **********************************************************************/
ISR(TIMER2_OVF_vect)
{
    static uint8_t no_of_overflows = 0;
    static uint8_t tenths = 0;  // Tenths of a second
    static uint8_t seconds = 0;  // Seconds
    static uint8_t minutes = 0;  // Minutes
    char string[2];             // String for converted numbers by itoa()


    no_of_overflows++;
    if (no_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        no_of_overflows = 0;
        
        // Count tenth of seconds 0, 1, ..., 9, 0, 1, ...
        tenths++;
        if (tenths>9)
        {
          tenths=0;
          seconds++;
        }  
        // Count of seconds 0, 1, ..., 9, 0, 1, ...
        if (seconds>59)
        {
          seconds=0;
          minutes++;
        }  
        // Count of minutes 0, 1, ..., 9, 0, 1, ...
        if (minutes>59)
        {
          minutes=0;
        }  
        lcd_gotoxy(0, 0);
        itoa(minutes, string, 10);  // Convert decimal value to string
        if(minutes<10)
        {
          lcd_putc('0');
        }  
        lcd_puts(string);
        lcd_gotoxy(2, 0);
        lcd_putc(':');


        itoa(seconds, string, 10);  // Convert decimal value to string
        // Display "00:00.seconds"
        lcd_gotoxy(3, 0);
        if(seconds<10)
        {
          lcd_putc('0');
        } 
        lcd_puts(string);
        lcd_gotoxy(5, 0);
        lcd_putc('.');

        itoa(tenths, string, 10);  // Convert decimal value to string
        // Display "00:00.tenths"
        lcd_gotoxy(6, 0);
        lcd_puts(string); 


        
        
  
        // Display "00:00.minutes"

        lcd_gotoxy(0, 1);
        lcd_putc(0x00);

    }
    // Else do nothing and exit the ISR
}