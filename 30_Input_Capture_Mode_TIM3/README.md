# STM32F407 Drone Project: RC Receiver Input Capture (DMA Based)

This module is designed to read PWM signals from an RC Receiver using the **STM32F407VGT6 (Discovery Board)**. It utilizes the **Timer Input Capture** peripheral combined with **DMA (Direct Memory Access)** to achieve high-precision measurements of pilot commands without interrupting the main CPU.

## Project Overview
In a drone flight controller, reading the receiver's signal is the "ears" of the system. This project captures the pulse width of incoming PWM signals (typically ranging from 1000µs to 2000µs) and maps them to target flight angles.

## Hardware Configuration
- **MCU:** STM32F407VGT6
- **Timer:** TIM3 (General Purpose Timer)
- **Channel:** Channel 1
- **Input Pin:** PC6 (Alternate Function: TIM3_CH1)
- **Clock Source:** 8 MHz External Crystal (HSE)

## STM32CubeMX Setup Details

### 1. Clock Configuration
- **HCLK (CPU Speed):** 168 MHz (Maximum performance for PID calculations).
- **APB1 Timer Clock:** 84 MHz (The specific bus speed for TIM3).

### 2. Timer 3 (TIM3) Parameters
- **Clock Source:** Internal Clock
- **Channel 1:** Input Capture direct mode
- **Prescaler (PSC):** `84 - 1` (Downscales 84MHz to 1MHz → 1 tick = 1 microsecond).
- **Counter Period (ARR):** `65535` (Maximum 16-bit value).
- **Polarity Selection:** `Both Edges` (Captures both rising and falling transitions).

### 3. DMA Settings
- **Stream:** DMA1 Stream 4 (Mapped to TIM3_CH1)
- **Direction:** Peripheral To Memory
- **Mode:** Circular (Continuously updates the buffer).
- **Data Width:** Half Word (16-bit).

## Software Implementation

The system uses a 2-element buffer to store the timestamps of the rising and falling edges. The pulse width is calculated inside the DMA Transfer Complete callback.

### Code Snippet: Logic and Mathematics

```c
/* Variables */
uint16_t ic_buffer[2];        // Buffer for timestamps
uint16_t pulse_width = 0;     // Measured signal in microseconds
float target_roll_angle = 0;  // Mapped angle for PID controller

/* Start the Capture */
HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t*)ic_buffer, 2);

/* Interrupt Callback */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        // Calculate the difference between Falling and Rising edges
        if (ic_buffer[1] >= ic_buffer[0]) {
            pulse_width = ic_buffer[1] - ic_buffer[0];
        } else {
            // Handle timer overflow (65535 wrap-around)
            pulse_width = (65535 - ic_buffer[0]) + ic_buffer[1] + 1;
        }

        // Mapping: 1000us -> -30°, 1500us -> 0°, 2000us -> +30°
        target_roll_angle = (pulse_width - 1500) * (30.0f / 500.0f);
    }
}
```