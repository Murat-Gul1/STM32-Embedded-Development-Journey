# STM32 Timer-Triggered DMA to GPIO (Zero CPU Overhead)

This project demonstrates how to toggle a GPIO pin (LED) using an Advanced Timer (TIM1) and DMA2 without any CPU intervention after initialization. It leverages the STM32 Bus Matrix architecture to achieve deterministic timing and efficiency.

## 📌 Project Overview

Traditional LED blinking usually involves `HAL_Delay()` or Timer Interrupts, both of which consume CPU cycles. This implementation uses:
- **TIM1 (Update Event):** To trigger a DMA request at a fixed frequency.
- **DMA2 (Stream 5 / Channel 6):** To transfer data directly from memory to the GPIO register.
- **GPIO BSRR (Bit Set/Reset Register):** To safely toggle a specific pin without affecting other pins on the same port.

## 🛠 Hardware & System Configuration

- **MCU:** STM32F4 Series (F429/F407)
- **Core Clock:** 84 MHz (HCLK)
- **Timer:** TIM1 (Internal Clock)
- **DMA Controller:** DMA2 (Required for AHB1/GPIO Bus Matrix access)

### Timer Settings (for 1Hz Blinking)
- **Prescaler (PSC):** 8399
- **Counter Period (ARR):** 4999
- **Calculation:** Freq = 84,000,000 / ((8399+1) * (4999+1)) = 2 Hz (toggles every 0.5s)

### DMA Settings
- **Request:** TIM1_UP
- **Direction:** Memory to Peripheral
- **Mode:** Circular
- **Data Width:** Word (32-bit)
- **Memory Increment:** Enabled
- **Peripheral Address:** `&GPIOD->BSRR`

## 💻 Implementation Details

The core logic uses a two-element buffer to set and reset the pin:

```c
/* Memory buffer containing BSRR values for PD12 */
uint32_t led_data[] = {
    0x00001000,  // Set PD12 (Bit 12)
    0x10000000   // Reset PD12 (Bit 28)
};
```
Initialization Sequence
Start DMA: Configure source (buffer), destination (BSRR), and length (2).

Enable Timer DMA Request: Tell the timer to trigger DMA on every update event.

Start Timer: Begin the counting process.
```c
HAL_DMA_Start(&hdma_tim1_up, (uint32_t)led_data, (uint32_t)&GPIOD->BSRR, 2);
__HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_UPDATE);
HAL_TIM_Base_Start(&htim1);
```