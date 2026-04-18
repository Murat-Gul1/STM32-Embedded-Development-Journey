# STM32 M2P DMA to Nextion Display 🚀

## Overview
This repository contains a high-efficiency hardware-level communication implementation for the STM32 microcontroller. It demonstrates how to transmit string arrays from SRAM to a Nextion HMI display over a UART bus using Direct Memory Access (DMA) in Memory-to-Peripheral (M2P) mode.

The primary goal of this architecture is to achieve **zero CPU load** during data transmission. By offloading the UART TX process entirely to the DMA controller, the CPU is freed up to handle high-frequency real-time tasks, such as reading 9-axis IMU sensors and executing PID algorithms for custom flight controllers.

## Key Technical Architecture
The real power of this project lies in its AHB bus matrix optimization rather than just the C code. 

### 1. FIFO & Memory Burst Optimization
* **FIFO Threshold (1/2):** The DMA FIFO (16 Bytes) is configured to trigger at half-full (8 Bytes).
* **Memory Burst (INCR8):** Instead of fetching data byte-by-byte and constantly locking the AHB bus, the DMA is configured to fetch 8 bytes (64 bits) simultaneously from SRAM in a single burst.
* **Peripheral Burst (Single):** The DMA unloads the FIFO byte-by-byte into the UART Data Register (DR), perfectly matching the physical 8-bit limit of the UART hardware without causing overrun errors. This creates a highly efficient pipeline.

### 2. Interrupt Safety
While the DMA handles the heavy lifting, the **UART Global Interrupt** is enabled alongside the DMA interrupt. This is crucial for data integrity. The DMA considers its job done when data reaches the UART register, but the physical transmission takes time. Enabling the UART interrupt ensures the CPU is safely notified via the `HAL_UART_TxCpltCallback` only when the final bit has physically exited the TX pin.

### 3. Nextion Protocol Compliance
Nextion displays require a mandatory 24-bit termination sequence to parse commands. The payload includes this natively:
`uint8_t nextion[] ="t0.txt=\"Hello DMA!\"\xFF\xFF\xFF";`
The DMA seamlessly handles this non-standard byte length (22 Bytes total) by utilizing INCR8 for the bulk of the data and automatically switching to single-mode for the remainder, preventing any bus faults.

## Hardware Requirements
* STM32 Development Board (e.g., STM32F407G-DISC1)
* Nextion HMI Display (e.g., 2.4" TFT)
* Jumper Wires

## Wiring & Pinout
> **⚠️ Critical:** A common Ground (GND) between the STM32 and the Nextion display is required for stable UART communication.

| STM32 Pin | Nextion Pin | Function |
| :--- | :--- | :--- |
| `PA2` (USART2_TX) | `RX` (Yellow) | Transmit data to display |
| `GND` | `GND` (Black) | Common Ground |
| `5V` / `VBUS` | `+5V` (Red) | Power supply |

## Quick Start / Code Snippet
Initialize the DMA transfer just before your main loop. Note the `- 1` in the sizeof function, which prevents sending the hidden C null-terminator (`\0`) to the screen.

```c
/* 1. Define the payload with Nextion termination */
uint8_t nextion_data[] ="t0.txt=\"Hello DMA!\"\xFF\xFF\xFF";
volatile uint8_t transfer_completed = 0;

int main(void) {
    /* HAL & Peripheral Inits (GPIO, DMA, UART) */
    // ...

    /* 2. Start M2P DMA Transfer */
    HAL_UART_Transmit_DMA(&huart2, nextion_data, sizeof(nextion_data) - 1);

    while (1) {
        /* CPU is 100% free here to run main application logic! */
        
        if(transfer_completed == 1){
            transfer_completed = 0;
            // Handle post-transfer logic if necessary
        }
    }
}

/* 3. Safe Completion Callback */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
    if(huart->Instance == USART2) {
        transfer_completed = 1;
    }
}