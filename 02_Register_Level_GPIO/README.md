# STM32F407 Bare-Metal LED Control (Register Level)

This project demonstrates how to control an onboard LED (PD12) on an **STM32F407G-DISC1** board by interacting directly with the processor's registers. Instead of using high-level libraries (HAL/LL), this implementation uses memory address calculations and bit manipulation based on the **RM0090 Reference Manual**.



## 🎯 Project Overview
The goal is to move away from the "black box" of HAL functions and understand the underlying hardware architecture:
- **Direct Memory Access:** Using C pointers to modify hardware states.
- **Clock Management:** Enabling peripheral clocks via the **RCC** unit.
- **GPIO Configuration:** Setting pin modes (MODER) and toggling output data (ODR).

## 🛠️ Technical Implementation

### 1. Address Calculation
According to the **RM0090 Reference Manual**, we identified the base addresses and offsets:
- **RCC_AHB1ENR:** `0x40023800` (Base) + `0x30` (Offset) = `0x40023830`
- **GPIOD_MODER:** `0x40020C00` (Base) + `0x00` (Offset) = `0x40020C00`
- **GPIOD_ODR:** `0x40020C00` (Base) + `0x14` (Offset) = `0x40020C14`



### 2. Logic Flow
1. **Clock Activation:** Set Bit 3 of `RCC_AHB1ENR` to enable the GPIOD peripheral.
2. **Mode Selection:** Set Bit 24 of `GPIOD_MODER` to `1` to configure PD12 as an **Output**.
3. **Data Toggling:** Modify Bit 12 of `GPIOD_ODR` to switch between High (3.3V) and Low (0V).

## 💻 The Implementation (Blink Logic)

The following code implements a manual delay to make the blinking visible to the human eye.

```c
// Define Register Pointers
volatile uint32_t *RCC_AHB1ENR = (volatile uint32_t *)(0x40023800 + 0x30);
volatile uint32_t *GPIOD_MODER = (volatile uint32_t *)(0x40020C00 + 0x00);
volatile uint32_t *GPIOD_ODR   = (volatile uint32_t *)(0x40020C00 + 0x14);

int main(void) {
    // 1. Enable Clock for GPIOD (Bit 3)
    *RCC_AHB1ENR |= (1 << 3);

    // 2. Set PD12 as Output (Bit 24)
    *GPIOD_MODER |= (1 << 24);

    while (1) {
        // 3. Toggle LED (Bit 12)
        *GPIOD_ODR |= (1 << 12);  // LED ON
        
        for(int i = 0; i < 1000000; i++); // Simple Delay
        
        *GPIOD_ODR &= ~(1 << 12); // LED OFF (Bitwise AND with Inverse)
        
        for(int i = 0; i < 1000000; i++); // Simple Delay
    }
}