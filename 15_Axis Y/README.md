# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/Rks5X7KEzPA)
# Advanced ADC Signal Filtering (STM32 + Nextion) 🚀

This repository demonstrates a custom-built signal filtering algorithm for embedded systems, taking basic ADC readings from an STM32 microcontroller and visualizing the transformation in real-time on a Nextion display. 

The core philosophy of this project is **solving hardware imperfections through software**.

## 📌 Project Overview

Analog sensors (like joysticks or potentiometers) often suffer from electrical noise, jitter, and mechanical drift. Instead of relying on raw 12-bit ADC data, this project implements a multi-stage software pipeline to clean, map, and shape the signal into a perfectly smooth and highly responsive output.

You can observe the entire filtering pipeline live on the Nextion display in three distinct stages:

* **📍 Top of Screen (Raw Data):** The raw, noisy 12-bit (0-4095) reading straight from the sensor.
* **📍 Middle of Screen (Linear Map):** The data mathematically mapped between `-100` and `+100`. While scaled correctly, it remains jittery and lacks true analog precision.
* **📍 Bottom of Screen (Filtered):** The final output, mapped between `-100` and `+100`, processed through our custom algorithm for ultimate smoothness.

## ⚙️ Under the Hood: The Algorithm

The final filtered value isn't just a simple moving average. It utilizes three distinct techniques running in the background to guarantee perfect control:

1.  **Threshold Filter:** A dual-layer tolerance threshold that acts as a gatekeeper, completely blocking out micro-fluctuations and hardware noise.
2.  **Deadzone (Safety Barrier):** Compensates for mechanical wear and tear. It nullifies mechanical drift at the center resting position, creating a crisp, absolute `0` point.
3.  **Cubic ($x^3$) Acceleration:** Replaces standard linear mapping with a polynomial speed curve. This provides pinpoint, millimeter-level accuracy near the center, while smoothly ramping up exponentially toward the extreme edges.

## 🛠️ Hardware Requirements

* STM32 Microcontroller (Any series with a 12-bit ADC)
* Nextion HMI Display
* Analog Input Device (Joystick, Potentiometer, etc.)
* UART connection between STM32 and Nextion

## 🚀 Getting Started

*(You can add instructions here on how to compile your code, which IDE you used (e.g., STM32CubeIDE), and how to flash it to the board.)*

1. Clone this repository.
2. Open the project in your preferred STM32 IDE.
3. Compile and flash the firmware to your MCU.
4. Upload the provided `.HMI` file to your Nextion display.

