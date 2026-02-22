# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/XNo8l3TsSDg?feature=share)
# STM32 Non-Blocking Multi-Tasking with EXTI & SysTick 🚀

## 📌 Project Overview
This project demonstrates how to achieve pseudo-multitasking and real-time responsiveness on an STM32 microcontroller. By completely eliminating blocking functions like `HAL_Delay()`, the system can simultaneously manage a continuous background task (a heartbeat LED) while asynchronously handling external hardware interrupts (button presses) without any CPU stalling.

## ✨ Key Features
* **Zero-Blocking Architecture:** The main loop runs continuously at maximum speed, relying on the hardware SysTick timer (`HAL_GetTick()`) for timekeeping.
* **Optimized Interrupt Service Routine (ISR):** The EXTI callback function uses a minimalist "Flag" logic, ensuring the CPU spends only microseconds inside the ISR.
* **Rollover-Safe Time Calculation:** Time-tracking logic is implemented using modular subtraction `(CurrentTime - StartTime >= Interval)`. This guarantees the system will not crash or freeze even when the 32-bit `uint32_t` SysTick timer overflows after ~49.7 days of continuous operation.

## 🛠️ Hardware Configuration

| Component | STM32 Pin | Configuration | Description |
| :--- | :--- | :--- | :--- |
| **Tactile Button** | `PA1` | `EXTI` (Rising Edge) | External interrupt trigger (with external pull-down resistor). |
| **Green LED** | `PA2` | `GPIO_Output` | System heartbeat. Toggles every 500ms continuously. |
| **Red LED** | `PA3` | `GPIO_Output` | Event indicator. Turns on via ISR flag, turns off automatically after 2000ms. |

## ⚙️ How It Works



1. **The Heartbeat (`PA2`):** The Green LED checks the `HAL_GetTick()` counter in the main loop. If 500ms have passed since its last toggle, it changes state. It operates completely independently of other tasks.
2. **The Interrupt (`PA1`):** When the button is pressed, the hardware triggers the EXTI line. The processor briefly pauses the main loop, sets a volatile `flag = 1`, and immediately returns.
3. **The Event Handler (`PA3`):** The main loop detects the raised flag, turns on the Red LED, records the exact timestamp, and lowers the flag. It then continues its normal operation. After 2000ms, the main loop detects the time elapsed and turns off the Red LED. 

## 💻 Code Architecture Highlight

```c
// Example of the rollover-safe, non-blocking delay structure used in the main loop:
if ((HAL_GetTick() - green_led_on_time) >= 500) {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
    green_led_on_time = HAL_GetTick(); // Reset the timer
}

```
