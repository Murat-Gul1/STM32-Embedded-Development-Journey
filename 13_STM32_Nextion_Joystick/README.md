# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/gAYoJqZSlaQ)
# STM32 & Nextion HMI: Smooth Joystick Control

This project demonstrates how to achieve smooth, jitter-free graphical control on a Nextion HMI display using an analog joystick and an STM32F407 microcontroller. It features a custom dynamic hysteresis filter to eliminate analog noise and provides a seamless user experience.

## 🚀 Features

* **Analog-to-Digital Conversion (ADC):** Reads raw analog data from a 2-axis joystick using the STM32's 12-bit ADC.
* **Dynamic Hysteresis Filter (Thresholding):** Implements a custom software filter to eliminate hardware jitter and electrical noise, ensuring the graphical indicator on the screen remains perfectly stable when the joystick is held still.
* **Resolution Mapping:** Mathematically scales the 12-bit ADC resolution (0-4095) to the Nextion display's X-axis resolution (0-320 pixels).
* **Efficient UART Rendering:** Instead of redrawing the entire screen, the algorithm efficiently erases only the previous line and draws the new one, preventing UART buffer overflow and screen flickering.

## 🛠️ Hardware Requirements

* **Microcontroller:** STM32F407G-DISC1 (Discovery Board)
* **Display:** Nextion HMI Display (Model: NX3224K024_011, Resolution: 320x240)
* **Input:** Standard Analog Joystick Module
* **Connectivity:** Jumper wires (USB to TTL not required for final run, STM32 communicates directly with Nextion via UART).

## 📌 Pin Configuration

| Component | Pin / Channel | STM32 Pin | Function |
| :--- | :--- | :--- | :--- |
| **Joystick** | VRx (X-Axis) | `PA1` | ADC1_IN1 (Analog Read) |
| **Nextion** | RX | `PA2` | USART2_TX (Transmit commands to display) |
| **Nextion** | TX | `PA3` | USART2_RX (Receive from display - optional here) |

## 💻 Software & Tools

* **STM32CubeMX:** For configuring peripherals (ADC, USART, Clock) and generating initialization code.
* **STM32CubeIDE:** For writing the core logic in C and live-debugging variables.
* **Nextion Editor:** For setting the initial display parameters (e.g., `bauds=115200`).

## 🧠 Core Algorithm: The Hysteresis Filter

Analog sensors are inherently noisy. To prevent the on-screen crosshair from "jittering", a delta threshold algorithm is applied before any UART commands are sent. 

The system stores the previous raw ADC value. A new UART render command is only triggered if the absolute difference between the new ADC reading and the old ADC reading exceeds a defined threshold (e.g., `20` units).

```c
// Dynamic Noise Filter (Delta Threshold = 20)
if (joy_x_axis > old_joy_x + 20 || joy_x_axis < old_joy_x - 20) 
{
    old_joy_x = joy_x_axis; // Update valid state
    
    // Map 0-4095 to 0-320 pixels
    new_x = (joy_x_axis * 320) / 4095; 

    if (new_x != old_x) 
    {
        // 1. Erase old line (Draw White)
        sprintf(uart_buffer, "line %d,90,%d,150,65535", old_x, old_x);
        Nextion_Command_send(uart_buffer);

        // 2. Draw new line (Draw Black)
        sprintf(uart_buffer, "line %d,90,%d,150,0", new_x, new_x);
        Nextion_Command_send(uart_buffer);

        old_x = new_x;
    }
}