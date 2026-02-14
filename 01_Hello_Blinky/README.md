# 01 - Hello Blinky: The Embedded "Hello World" 💡

This is my first project in the world of embedded systems. While every programmer starts with printing "Hello World" on a screen, in the embedded world, we say hello by making an LED blink. 

For this project, I took it a step further and created a **"Police Flasher"** animation instead of a simple blink.

## 🚀 Project Overview
The goal of this project is to understand the basics of GPIO (General Purpose Input/Output) pins, clock configurations, and delay functions using the STM32 HAL (Hardware Abstraction Layer) library.

### Key Features:
- **Police Flasher Mode:** A custom animation that toggles multiple LEDs in a specific sequence.
- **Optimized Logic:** Used `uint8_t` for memory efficiency and Bitwise operations for pin management.
- **Hardware Control:** Directly interfacing with the ARM Cortex-M4 core.

## 🛠 Hardware & Tools
- **Board:** STM32F407G-DISC1 (Discovery Board)
- **Microcontroller:** STM32F407VGT6 (ARM Cortex-M4)
- **IDE:** STM32CubeIDE
- **Library:** STM32Cube HAL

## 📺 Project Demo
*(Optional: You can add your LinkedIn video link or a GIF here)*
[Watch the Animation in Action]([https://www.youtube.com/shorts/YwHq0zjWtAU])

## 💻 Technical Snippet
In this project, I used the `HAL_GPIO_TogglePin` and `HAL_Delay` functions to create the timing for the flasher effect:

```c
// Example of the police flasher logic
HAL_GPIO_TogglePin(GPIOD, LED_RED_Pin | LED_BLUE_Pin);
HAL_Delay(100);
