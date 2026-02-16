# [🎥 Watch the Project Demo on YouTube](https://youtube.com/shorts/U6Ynq9WG1xk?feature=share)

# STM32F4 Discovery - Button Controlled LED (Polling)

This project demonstrates a basic **GPIO Input/Output** operation using the **STM32 HAL Library**. It implements a simple "polling" mechanism where the microcontroller continuously checks the state of the user button to control an onboard LED.

## 🎯 Overview

The main goal of this project is to understand how to:
1.  Configure GPIO pins as **Input** (for the button) and **Output** (for the LED).
2.  Read the state of a digital pin using `HAL_GPIO_ReadPin`.
3.  Write a state to a digital pin using `HAL_GPIO_WritePin`.
4.  Implement a basic polling loop.

**Logic:**
* **Pressed:** The Green LED (LD4) turns **ON**.
* **Released:** The Green LED (LD4) turns **OFF**.

## 🛠 Hardware Required

* **Board:** STM32F407G-DISC1 (STM32F4 Discovery Board)
* **MCU:** STM32F407VGT6
* **Cable:** Mini-USB cable for programming/debugging.

## ⚙️ Pin Configuration

The code uses the onboard peripherals of the Discovery board. No external wiring is required.

| Component              | Pin Name   | GPIO Port   | GPIO Pin  | Mode |                           
| **User Button** (Blue) | `PA0`      | GPIOA       | PIN 0     | Input |                          
| **Green LED** (LD4)    | `PD12`     | GPIOD       | PIN 12    | Output |                         

## 💻 Software & Tools

* **IDE:** STM32CubeIDE
* **Firmware Package:** STM32Cube FW_F4
* **Library:** HAL (Hardware Abstraction Layer)

## 📝 Code Explanation

The core logic resides in the `while(1)` loop in `main.c`. It uses a **Polling** method, meaning the CPU is constantly asking "Is the button pressed?".

```c
while (1)
{
  /* Check if the Button (PA0) is pressed (Logic High) */
  if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) == 1) 
  {
      /* Turn ON the LED (PD12) */
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
  }
  else
  {
      /* Turn OFF the LED (PD12) */
      HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
  }
}