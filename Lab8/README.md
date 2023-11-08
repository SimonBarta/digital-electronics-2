4. Go through the `main.c` file and make sure you understand each line. Use **AVR® Instruction Set Manual** from Microchip [Online Technical Documentation](https://onlinedocs.microchip.com/), find the description of instructions used in `mac.S`, and complete the table.

   | **Instruction** | **Operation** | **Description** | **Cycles** |
   | :-- | :-: | :-- | :-: |
   | `add Rd, Rr` | Rd ← Rd + Rr | Adds two registers without the C Flag and places the result in the destination register Rd. | 1 |
   | `mul Rd, Rr` | R1:R0 ← Rd × Rr (unsigned ← unsigned × unsigned)  | This instruction performs 8-bit × 8-bit → 16-bit unsigned multiplication. | 1 |
   | `ret` | (i) PC(15:0) ← STACK Devices with 16-bit PC, 128KB Program memory maximum.
(ii) PC(21:0) ← STACK Devices with 22-bit PC, 8MB Program memory maximum | Returns from subroutine. The return address is loaded from the STACK. The Stack Pointer uses a pre-
increment scheme during RET. | 4 devices with 16-bit PC
5 devices with 22-bit PC |

5. Use manual's 16-bit Opcodes and convert used instructions to hexadecimal.

   | **Instruction** | **Binary opcode** | **Hex opcode** | **Compiler Hex opcode** |
   | :-- | :-: | :-: | :-: |
   | `add r24, r0` | `0000 1110  1000 0000` | `0E 80` | 08 E0 |
   | `mul r22, r20` | `1001 1111  0110 0100` | `9F 64` | 46 F9 |
   | `ret` | `1001_0101_0000_1000` | `95 08` | 80 59 |

1. Consider a 4-bit shift register whose input (LSB bit) is formed by an XNOR gate with taps [4, 3] and the initial value is 0000 [[5]](https://www.edn.com/tutorial-linear-feedback-shift-registers-lfsrs-part-1/). Explore LFSR algorithm within `lfsr4_fibonacci_asm` assembly function, complete Timer1 overflow handler and generate 4-bit pseudo-random sequences for different Tap positions. How many states are generated for every settings?

   ![LFSR generation algo](images/flowchart_lfsr-value_algo.png)

   | **Tap position** | **Generated values** | **Length** |
   | :-: | :-- | :-: |
   | 4, 3 | 01371514128␁␑␅␃ 0 |  |
   | 4, 2 | 013714128 |  |
   | 4, 1 | 013612936 |  |