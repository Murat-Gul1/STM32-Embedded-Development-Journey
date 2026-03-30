# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/A9rKPAxiy3U)
# STM32 DMA Memory-to-Memory (M2M) Optimization with FIFO & Burst Mode

This project demonstrates how to achieve maximum performance for Memory-to-Memory (M2M) data transfers (from Flash to SRAM) using the **DMA (Direct Memory Access)** peripheral on STM32 microcontrollers (specifically the STM32F4 series). The project explores the working principles of **FIFO** and **Burst (INCR4)** modes, hardware constraints, and their impact on performance by measuring clock cycles using the DWT (Data Watchpoint and Trace) unit.

## 🚀 Project Goal and Experiment Scenario

The main objective of this project is to practically investigate the logic behind the DMA Burst mode and its mathematical relationship with the FIFO hardware.

In the code, a constant array located in Flash memory (`flash_array`) is copied to an array in SRAM (`sram_array`) using the DMA M2M mode. The data width is set to **32-bit (Word)**, and the Burst packet size is configured as **INCR4 (4 beats)**.

### ⚠️ The Crucial Experiment: "The Remaining Data Trap"
The total data size to be transferred is intentionally defined as `#define SIZE 1289` in this project.
* In INCR4 mode, data is sent in packets of 4.
* 1289 is not perfectly divisible by 4 (1288 is divisible, leaving a remainder of 1).
* This configuration practically proves that the first 1288 data items are transferred at maximum speed using Burst mode, while the **remaining 1 data item is automatically downgraded to "Single" mode by the hardware**, resulting in a slower transfer for that specific portion.

## 📐 DMA FIFO and Burst Architecture: 3 Golden Rules

To achieve maximum speed in M2M transfers, the following hardware rules must be strictly followed, as implemented in this project:

1. **Physical Limit (16 Bytes):** In the STM32F4 series, the FIFO memory of each DMA stream is strictly 16 Bytes. The configured *(Burst Size x Data Width)* can never exceed this limit. (e.g., 4 Words x 4 Bytes = 16 Bytes ✔️)
2. **Threshold Compliance:** The selected FIFO threshold level (1/4, 1/2, 3/4, FULL) must be a perfect multiple of the created Burst packet size (in bytes). Since a 16-Byte packet is created in this project, the threshold must be set to **FULL**. Otherwise, the hardware will trigger a `FEIF` (FIFO Error).
3. **M2M and FIFO Relationship:** When Memory-to-Memory (M2M) transfers are used in the STM32 architecture, the FIFO hardware is automatically enabled by default (Direct Mode cannot be used). Therefore, configuring the FIFO settings correctly is mandatory, not optional.

## 🛠️ Hardware & Software Requirements
* **Microcontroller:** STM32F4 Series (Development board used in the project)
* **IDE:** STM32CubeIDE
* **Driver Architecture:** HAL (Hardware Abstraction Layer)

## ⏱️ Performance Measurement (DWT)
To measure the transfer time at the microcontroller's core speed with microsecond precision, the **DWT (Data Watchpoint and Trace)** unit—a hardware counter of the ARM Cortex-M architecture—was used instead of `SysTick`.

```c
CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
DWT->CYCCNT = 0; // Reset the counter

uint32_t start_cycle = DWT->CYCCNT; // Start cycle value
HAL_DMA_Start(&hdma_memtomem_dma2_stream0, (uint32_t)flash_array, (uint32_t)sram_array, SIZE);
HAL_DMA_PollForTransfer(&hdma_memtomem_dma2_stream0, HAL_DMA_FULL_TRANSFER, HAL_MAX_DELAY);
uint32_t stop_cycle = DWT->CYCCNT; // End cycle value

uint32_t total_cycles = stop_cycle - start_cycle;
// Calculation of microseconds and seconds based on the total cycle value...
```
The measurement results are printed to the serial terminal via UART (printf).

⚙️ DMA Configuration Summary (STM32CubeMX / HAL)
Mode: Memory To Memory

Data Width (Src & Dest): Word (32-bits)

FIFO Mode: Enable

FIFO Threshold: Full

Burst Size (Src & Dest): 4 Beats (INCR4)