# STM32 DMA Memory-to-Memory (M2M) Transfer

## Overview
This project is developed to demonstrate Memory-to-Memory (M2M) data transfer using Direct Memory Access (DMA) on an STM32 microcontroller. The transfer is handled entirely in Interrupt (IT) mode.

## Features
* **DMA Mode:** Memory-to-Memory (M2M) transfer is configured.
* **Interrupts:** Transfer completion is detected by DMA interrupts.
* **Library:** STM32 Hardware Abstraction Layer (HAL) is utilized.
* **CPU Efficiency:** The CPU is not blocked during the data transfer process.

## How It Works
1. A source data string (`source_data`) is created in the memory.
2. A destination array (`destination_data`) is initialized with zeros.
3. The DMA transfer is started by the `HAL_DMA_Start_IT()` function.
4. When the data is successfully copied, the `DMA_TransferComplete_Callback` function is automatically triggered.
5. A volatile flag (`transfer_completed`) is set to 1 inside the callback to notify the main loop.

## Hardware & Software Requirements
* **Microcontroller:** STM32 Series (Configured via STM32CubeMX)
* **IDE:** STM32CubeIDE 
* **Framework:** STM32 HAL Library
