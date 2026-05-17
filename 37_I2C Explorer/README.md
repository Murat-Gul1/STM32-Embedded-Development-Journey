# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/0v8YC_uD3tk)
# STM32F407 Real-Time Sensor Monitoring and Advanced I2C Bus Management

This project is an embedded software application running on the STM32F407 microcontroller that reads sensor data (IMU and Environment) and displays an interactive menu on an OLED screen.

The main focus of the project is to demonstrate **how multiple hardware components (MPU9250, SHT3x, and SSD1306) with different frequencies and data sizes can be managed over a single I2C bus in a non-blocking manner and without straining the CPU.**

## 🚀 Hardware Challenges and Architectural Solutions

The most common problem encountered in embedded systems when displays and sensors share the same I2C bus is **"I2C Bus Starvation".**

Sending a 1024-byte OLED display frame via I2C over DMA takes approximately **25 milliseconds**. If the CPU attempts to read data from sensors (IMU or Temperature) during this time, it receives a `HAL_BUSY` response, and the sensors are skipped without being read.

**Solution: Time-Slicing and Bus Arbitration**
In this project, an intelligent traffic control mechanism has been established to prevent the sensors from becoming unresponsive:
1. The processor waits for the display's DMA transfer to finish (`HAL_I2C_STATE_READY`).
2. In that microsecond gap when the line is free (just before a new display frame is drawn), the MPU9250 and SHT3x sensors are quickly read.
3. The received updated data is transferred to the state machine (FSM), and the display DMA is re-triggered.

This ensures that the screen updates smoothly while the sensors continue to read in real-time without missing a single frame.

## ⚙️ Technical Specifications and Technologies Used

* **Single I2C Line Multiple Devices:** SSD1306 (OLED), MPU9250 (IMU), and SHT3x (Temperature/Humidity) devices are seamlessly operated on the same I2C (`hi2c1`) line.
* **Non-locking Display Drawing (DMA_TX):** OLED screen updates are performed asynchronously via the `DMA1 Stream 6` channel (with Memory Increment enabled) to avoid CPU lockup.
* **CPU Independent ADC Reading (Circular DMA):** Analog joystick data used for menu navigation is continuously read in the background in circular mode via the `DMA2 Stream 0` channel.
* **MVC-Based State Machine:** Display drawing and hardware inputs are completely isolated from each other. The joystick only changes a cursor variable (`menu_cursor`), while the State Machine draws the interface based on this variable.

## 📂 File Structure and Dependencies

* `Core/Src/main.c`: Main loop containing the State Machine and I2C traffic control algorithm.
* `ssd1306...`: Double-buffered OLED driver that allows the screen to be updated via DMA.
* `inv_mpu...` / `MPU9250-DMP...`: InvenSense eMPL-based advanced IMU library.

## 🛠️ Setup

The project was developed with STM32CubeIDE. After cloning the source code, ensure that the **"Use float with printf from newlib-nano (-u _printf_float)"** option is enabled in the compiler settings so that `float` data types can be printed to the screen using `sprintf`.