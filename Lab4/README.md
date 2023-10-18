## Pre-Lab preparation

1. Use schematic of the [LCD keypad shield](https://oshwlab.com/tomas.fryza/arduino-shields) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

   | **LCD signal(s)** | **AVR pin(s)** | **Description** |
   | :-: | :-: | :-- |
   | RS | PB0 | Register selection signal. Selection between Instruction register (RS=0) and Data register (RS=1) |
   | R/W | GND | that selects reading mode or writing mode |
   | E | PB1 | that enables writing to the registers |
   | D[3:0] | None | The states of these pins (high or low) are the bits that you're writing to a register when you write, or the values you're reading when you read. |
   | D[7:4] | PB7 | The states of these pins (high or low) are the bits that you're writing to a register when you write, or the values you're reading when you read. |
   | K | PB2 | that you can use to power the LCD, control the display contrast, and turn on and off the LED backlight, respectively. |

2. What is the ASCII table? What are the codes/values for uppercase letters `A` to `E`, lowercase letters `a` to `e`, and numbers `0` to `4` in this table?

   | **Char** | **Decimal** | **Hexadecimal** |
   | :-: | :-: | :-: |
   | `A` | 65 | 0x41 |
   | `B` | 66 | 0x42 |
   | `C` | 67 | 0x43 |
   | `D` | 68 | 0x44 |
   | `E` | 69 | 0x45 |
   | `a` | 97 | 0x61 |
   | `b` | 98 | 0x62 |
   | `c` | 99 | 0x63 |
   | `d` | 100 | 0x64 |
   | `e` | 101 | 0x65 |
   | `0` | 48 | 0x30 |
   | `1` | 49 | 0x31 |
   | `2` | 50 | 0x32 |
   | `3` | 51 | 0x33 |
   | `4` | 52 | 0x34 |
