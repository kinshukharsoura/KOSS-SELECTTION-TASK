# KOSS-SELECTTION-TASK
CHIP-8 EMULATOR
# Custom CHIP-8 Emulator Core (C++)

## Overview
This is a custom-built CHIP-8 virtual machine emulator written entirely in C++ for the KOSS selection task. It handles memory mapping, instruction fetching, and complex opcode execution. 

Instead of relying on heavy external graphics libraries like SDL2, I designed a **custom Terminal-based ASCII rendering engine** that maps the 64x32 display array directly to console output using block characters (`█`), allowing the emulator to run natively in a Windows terminal.

## Features Implemented
* **Core CPU Cycle:** Accurate Fetch-Decode-Execute loop.
* **Memory Management:** 4KB RAM with protected system space.
* **Stack/Subroutines:** Implemented `CALL` and `RET` for nested logic.
* **Input Handling:** Mapped standard `WASD` keys to the CHIP-8 hex-pad using synchronous `<conio.h>` thread blocking.
* **Bitwise Graphics:** Accurate implementation of the `DXYN` XOR drawing logic.

## Included Custom Game: "Dot Hunter"
I wrote a custom game in raw CHIP-8 Assembly (included in the source code).
* **Gameplay:** Use WASD to move your player block and catch the randomly teleporting coin.
* **Technical Highlights:** * Uses the `CXNN` (Random Number) opcode hooked into C++ `rand()` for dynamic teleportation.
  * Utilizes hardware-level collision detection: Instead of checking X/Y coordinate math, the assembly checks the `VF` flag, which is natively triggered by the CPU when the XOR drawing instruction erases a pixel.

## How to Run
1. Compile using g++: `g++ task.cpp -o task`
2. Run the executable: `./task`
