# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/eubzdtQcSho)
# STM32 Timer Synchronization and Hardware Triggering (Master/Slave Mode)

This project demonstrates the hardware-level synchronization of two timers (**TIM1** and **TIM3**) on an **STM32F407VGT6** microcontroller. The system uses an external signal to trigger the master timer, which in turn drives the slave timer through internal hardware bridges, allowing for zero-latency interaction without CPU overhead.

## 🎯 Objective
To toggle an onboard LED (PD12) at a precise frequency (2 Hz) using a cascaded timer architecture. The process starts only when a physical 3.3V signal is detected on a specific GPIO pin.

## 🏗️ System Architecture

### 1. Master Timer: TIM1 (Advanced Control Timer)
* **Clock Source:** Internal Clock (connected to the high-speed **APB2** bus).
* **Slave Mode:** `Trigger Mode`. The timer stays idle until a trigger is received.
* **Trigger Source:** `TI1FP1` (linked to physical pin **PA8**).
* **Trigger Polarity:** `Rising Edge` (Triggers when signal goes from 0V to 3.3V).
* **Safety:** Hardware `Trigger Filter (15)` and `Pull-down` resistor are enabled on PA8 to prevent accidental triggering from electrical noise.
* **Master/Slave Mode (MSM):** `Enabled` (Ensures perfect synchronization between timers).
* **Master Output Trigger (TRGO):** Set to `Update Event`. TIM1 sends a pulse to the internal bridge every time it resets.

### 2. Slave Timer: TIM3 (General Purpose Timer)
* **Slave Mode:** `External Clock Mode 1`. Instead of using the internal APB bus, TIM3 treats incoming pulses from the master as its "clock".
* **Trigger Source:** `ITR0`. On the STM32F4 architecture, ITR0 is the internal hardware bridge directly connecting TIM1 to TIM3.

---

## 🧮 Mathematical Calculations

Based on the **42 MHz** Timer Clock frequency on the APB2 bus:

### TIM1 Configuration (Generating 4 Hz)
The target is for TIM1 to produce 4 "Update Events" per second.
$$Frequency = \frac{f_{clk}}{(Prescaler + 1) \times (Period + 1)}$$
* **Prescaler (PSC):** 4199
* **Counter Period (ARR):** 2499
* **Calculation:** $42,000,000 / (4200 \times 2500) = 4 \text{ Hz}$

### TIM3 Configuration (Blinking at 2 Hz)
TIM3 counts the 4 Hz pulses coming from TIM1 via ITR0.
* **Prescaler:** 0 (No further division).
* **Counter Period (ARR):** 1 (Resets every 2 pulses).
* **Interrupt:** `TIM3 Global Interrupt` enabled to toggle the LED.
* **Result:** The LED toggles every 0.5s, resulting in a **2 Hz** blink rate (500ms ON / 500ms OFF).

---

## 🔌 Hardware Setup
1.  **Microcontroller:** STM32F407 Discovery Board.
2.  **Input Pin:** **PA8** (Configured as TIM1_CH1 with internal Pull-down).
3.  **Output Pin:** **PE7**.
4.  **Trigger:** Apply **3.3V** to PA8 to start the sequence.

---

## 💻 Code Implementation (Snippet)

Only the Slave timer needs to be started in code; the Master timer starts automatically via hardware trigger.

```c
/* USER CODE BEGIN 2 */
// Start TIM3 in Interrupt Mode. It waits for pulses from TIM1.
HAL_TIM_Base_Start_IT(&htim3);
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12); // Toggle Green LED
    }
}
/* USER CODE END 4 */
```