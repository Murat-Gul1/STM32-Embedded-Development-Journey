# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/kpQqhvYOG2A)
# STM32 Non-Blocking Ultrasonic Distance Sensor Project

## Overview
This project implements a highly optimized, non-blocking distance measurement system using an STM32 microcontroller, an HC-SR04 ultrasonic sensor, and an SSD1306 OLED display. 

Instead of using standard "delay-based" (blocking) code, this architecture leverages the full power of the STM32's hardware peripherals (Timers and DMA) to minimize CPU load to nearly 0% for the sensor measurement process[.

## Key Features
**Hardware-Driven Triggering:** Uses a Timer in PWM mode to generate the 10µs trigger pulse every 60ms, ensuring precise timing without CPU intervention.
**Hardware-Capture Measurement:** Utilizes Timer Input Capture in "Reset Mode" to automatically capture the echo duration without requiring manual interrupt-based calculations.
**Non-Blocking Display Updates:** Uses I2C with DMA (Direct Memory Access) to update the OLED screen, preventing the I2C bus from stalling the main application loop.
**Zero-Wait Main Loop:** The CPU remains free to execute other tasks, only waking up to process the data when a new measurement is ready (Flag-based architecture).

## Architecture Breakdown

### 1. Triggering (TIM3 - PWM Mode)
The HC-SR04 requires a 10µs pulse to start a measurement. We configured TIM3 to output a PWM signal with a 60ms period and a 10µs pulse width. This automates the sensor excitation.

### 2. Echo Measurement (TIM2 - Input Capture & Reset Mode)
To measure the echo duration, we use TIM2.By configuring it in "Reset Mode" with "TI1FP1" trigger source, the hardware automatically resets the counter when the echo signal rises and captures the timestamp when it falls. This eliminates the need for complex manual timestamp calculations inside interrupts.

### 3. Display (I2C + DMA)
Display data is transmitted using I2C with DMA. This allows the CPU to offload the transfer of the 1024-byte framebuffer to the DMA controller, significantly improving system responsiveness and avoiding "Busy" errors on the I2C bus.

## Pinout Configuration (Example)
*HC-SR04 VCC:** 3V
*HC-SR04 GND:** GND
*HC-SR04 TRIG:** Connected to PC6 (TIM3_CH1) 
*HC-SR04 ECHO:** Connected to PA15 (TIM2_CH1) 

## Configuration Summary
**TIM3 (Trigger):** PWM Generation CH1, Prescaler 83, ARR 59999, Pulse 10.
**TIM2 (Echo):** Slave Mode (Reset), Trigger Source (TI1FP1), Input Capture (Direct for Ch1, Indirect for Ch2).
**I2C1:** Enabled with DMA TX (Transmit) channel for display updates.

## How It Works
1. **Triggering:** TIM3 automatically pulses the TRIG pin every 60ms.
2. **Measurement:** TIM2 captures the duration of the ECHO pulse in microseconds.
3. **Processing:** Once a measurement is complete, an interrupt flag is set.
4. **Display:** The main loop checks the flag, performs the math ($Distance = Time / 58$), and updates the screen via I2C DMA.

