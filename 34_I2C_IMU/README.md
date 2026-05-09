# STM32 MPU-9255 IMU Data Processing System

This repository contains a high-performance embedded solution for real-time orientation tracking using the **STM32** microcontroller and the **MPU-9255** 9-axis Inertial Measurement Unit (IMU). The system focuses on stable I2C communication, hardware-level data filtering, and efficient data streaming via DMA.

## 🚀 Overview
The project implements an interrupt-driven data acquisition system to convert raw accelerometer and gyroscope data into stable Euler angles (Pitch, Roll, and Yaw). A key highlight is the successful integration and optimization of 3rd-party hardware drivers from an external GitHub repository, adapted for the STM32 HAL environment.

## 🛠 Hardware Configuration

### Pin Mapping
The system is configured using the following pinout:

| Peripheral | Pin | Function |
| :--- | :--- | :--- |
| **I2C1_SCL** | PB8 | Serial Clock |
| **I2C1_SDA** | PB9 | Serial Data |
| **GPIO_EXTI5**| PB5 | Sensor Data Ready Interrupt |
| **USART2_TX** | PA2 | Data Streaming (Bluetooth/Serial) |
| **USART2_RX** | PA3 | Command Input |

### Sensor Strapping (MPU-9255)
To ensure correct I2C addressing and communication protocol selection:
* **AD0 → GND:** Configures the I2C address to `0x68`.
* **NCS (CS) → 3.3V:** Forces the sensor into I2C mode (disables SPI).
* **VCC → 5V:** Powered via the 5V rail for stable Bluetooth/Sensor operation.

## 💻 Technical Implementation

### 1. 3rd-Party Library Integration
* **Adaptation:** Analyzed and integrated complex hardware drivers from an open-source GitHub repository, successfully bridging them with the STM32 Hardware Abstraction Layer (HAL).
* **Optimization:** Leveraged specific hardware registers to offload processing from the main MCU core, ensuring efficient data handling.

### 2. Data Acquisition Flow
* **Interrupt-Driven (EXTI):** The sensor signals the STM32 via `PB5` whenever a new data sample is available, preventing polling-related CPU waste.
* **DMA-Assisted UART:** Processed orientation data is streamed using **Direct Memory Access (DMA)** to maintain high-speed communication without blocking the main execution loop.
* **HSE Clock:** Configured with an external high-speed crystal for maximum timing precision.

### 3. Serial Communication
Data is streamed at **115200 Baud** in a structured format:
`P:[Pitch],R:[Roll],Y:[Yaw]`
*(e.g., P:10.25,R:-1.50,Y:180.45)*

## 🔧 Build & Installation
1.  Open the project in **STM32CubeIDE**.
2.  Verify **I2C1** and **USART2** settings in the `.ioc` file.
3.  Build the project to generate the `.elf` or `.bin` file.
4.  Flash the firmware using an **ST-Link** debugger.

---
*Technical exploration focused on embedded sensor fusion and hardware driver implementation.*