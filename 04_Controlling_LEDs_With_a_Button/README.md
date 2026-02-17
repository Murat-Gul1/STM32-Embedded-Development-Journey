# 🎥 [Watch the Project Demo on YouTube](YOUTUBE_LINKINI_BURAYA_YAPISTIR)

# STM32F4 Discovery - LED Counter & Flash Animation

This project implements a **Sequential LED Control System** using the **STM32 HAL Library**. It utilizes a state machine logic based on button presses to cycle through LEDs and triggers a special "Flash Animation" at the end of the sequence.

## 🎯 Project Overview

The system uses the **User Button (PA0)** to increment a counter. Based on the counter value, the onboard LEDs light up in a specific sequence.

**Logic Flow:**
1.  **1st Press:** Green LED turns ON.
2.  **2nd Press:** Orange LED turns ON (Green turns OFF).
3.  **3rd Press:** Red LED turns ON (Orange turns OFF).
4.  **4th Press:** Blue LED turns ON (Red turns OFF).
5.  **Final Stage:** All 4 LEDs flash simultaneously **3 times** (1-second interval), and the system resets to the beginning.

> **Note:** Since the code uses a 150ms delay, holding the button down will cause the LEDs to cycle through the sequence automatically.

## 🛠 Hardware Required

* **Board:** STM32F407G-DISC1 (STM32F4 Discovery)
* **MCU:** STM32F407VGT6
* **Peripherals:** Onboard LEDs & User Button

## ⚙️ Pin Configuration
| Component | Pin Name | GPIO Port | GPIO Pin | Function |
| :--- | :--- | :--- | :--- | :--- |
| **User Button** | `PA0` | GPIOA | PIN 0 | Input |
| **Green LED** | `PD12` | GPIOD | PIN 12 | Output |
| **Orange LED** | `PD13` | GPIOD | PIN 13 | Output |
| **Red LED** | `PD14` | GPIOD | PIN 14 | Output |
| **Blue LED** | `PD15` | GPIOD | PIN 15 | Output |

## 💻 Software & Tools

* **IDE:** STM32CubeIDE
* **Firmware:** STM32Cube FW_F4
* **Library:** HAL (Hardware Abstraction Layer)

## 📝 Code Logic

The core logic is implemented in the `main.c` file using a `counter` variable and `HAL_Delay`.

```c
/* Basic Logic Structure */
if((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) == 1 && counter == 0){
    HAL_Delay(150);
    counter++;
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // Green ON
}
// ... (Steps 1, 2, 3 continue here) ...

/* Animation Sequence */
if(counter == 4){
    // Reset last LED
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
    
    // Flash all LEDs 3 times
    for(uint8_t i = 0; i < 3 ; i++){
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
        HAL_Delay(1000);
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
        HAL_Delay(1000);
    }
    counter = 0; // Reset System
}