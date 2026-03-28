# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/ZaEh5WzBkek)
# STM32 Memory-to-Memory (M2M) DMA Transfer (Polling Mode) 🚀

## Overview
This project demonstrates how to perform a high-speed data transfer from memory to memory (Flash to SRAM) using the Direct Memory Access (DMA) controller on an STM32 microcontroller. 

The data transfer process is completely offloaded to the DMA hardware, eliminating the need for CPU-intensive `for` or `while` loops. This specific implementation utilizes **Polling Mode** to manage the transfer state.

## Hardware & Software
* **Microcontroller:** STM32 (Developed and tested on STM32F407G-DISC1)
* **IDE:** STM32CubeIDE
* **Firmware Package:** STM32 HAL Library

## How It Works: Polling Mode
Polling mode (also known as blocking or synchronous mode) is the simplest form of DMA communication. In this mode, the main program (CPU) waits until the data transfer is complete. The processor constantly checks the relevant hardware flags to ask, "Has the DMA operation finished?", and locks on the current line of code during this time.

### Core Implementation
The operation is handled by two main HAL functions:

```c
// 1. Start DMA Operation: Command is given to the DMA to copy from source to destination.
HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t)source, (uint32_t)target, strlen(source));

// 2. Wait for Transfer (Polling): The processor is trapped at this line until the full transfer is completed.
HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
```
Pros and Cons
•	Advantage: This mode is the simplest data transfer method to implement. It can be easily used if the system does not have another urgent task for the processor to execute.
•	Disadvantage: It is highly disadvantageous in terms of performance. Because it keeps the processor waiting doing nothing (wasting CPU cycles), it does not fully comply with the core philosophy of "freeing the processor," which is the main purpose of using DMA.
Debugging & Observation
To observe the DMA in action:
1.	Enter Debug Mode in STM32CubeIDE.
2.	Add the target and source array variables to the Live Expressions window.
3.	Place a Breakpoint at the HAL_DMA_Start line.
4.	Use Step Over (F6) to execute the DMA start command and instantly watch the target memory block fill with the source data without any processor loops!

