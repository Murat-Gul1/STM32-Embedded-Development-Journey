# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/wPw1vZI-aLg)
# STM32F407 External Clock Mode 2 Implementation

This project demonstrates the implementation of **External Clock Mode 2** on an STM32F407VGT6 microcontroller. The project showcases how to drive a timer using a hardware-based external signal instead of the internal APB bus clock. In this setup, an internal clock signal is exported via **MCO1** and routed back into the timer through the **ETR** pin.

## 🚀 Project Overview
Typically, STM32 timers are clocked by internal peripherals. In this application:
1. Internal timer clocking is disabled.
2. The timer is configured to count physical electrical pulses arriving at the **ETR (External Trigger)** pin.
3. This methodology is fundamental for real-world applications such as:
   - Motor RPM counting (Tachometer)
   - Industrial part counting on production lines
   - Flowmeter pulse integration

## 🛠 Hardware Requirements
- **Microcontroller:** STM32F407VGT6 (Discovery Kit or custom board)
- **Connectivity:** 1x Female-to-Female (or Male-to-Male) jumper wire
- **Feedback:** 1x LED and a 220Ω/330Ω resistor

## 📍 Pin Configuration
| Function | Pin | Mode | Description |
| :--- | :--- | :--- | :--- |
| **Clock Source (MCO1)** | PA8 | AF0 | Outputs the 16 MHz HSI internal signal. |
| **Timer Input (ETR)** | PD2 | AF2 (TIM3_ETR) | Hardware-counts incoming external pulses. |
| **LED Output** | PE7 | GPIO_Output | Toggles state upon timer interrupt. |

> **Critical Connection:** Use a jumper wire to physically connect **PA8** to **PD2**.

## 📐 Mathematical Calculation
The STM32F407 utilizes an internal **HSI** signal running at **16 MHz**. To achieve a toggle rate of 2 times per second (2 Hz / 0.5s interval), the following scaling is applied:

- **Input Frequency:** 16,000,000 Hz
- **Prescaler (PSC):** 999 (+1) = 1,000
- **Counter Period (ARR):** 7,999 (+1) = 8,000

**Formula:**
$$f_{UEV} = \frac{16,000,000}{1,000 \times 8,000} = 2 \text{ Hz}$$

## ⚙️ CubeMX Configuration
1. **RCC:** Enable `Master Clock Output 1`, select `HSI` as the source.
2. **TIM3:** - `Slave Mode`: External Clock Mode 2
   - `Trigger Source`: ETR2
   - `Prescaler`: 999
   - `Period`: 7999
3. **NVIC:** Check `TIM3 global interrupt` Enabled.
4. **GPIO:** Set PA8 output speed to `Very High`.

## 💻 Code Implementation

### Start Timer in Interrupt Mode (main.c)
```c
/* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim3); // Start TIM3 with interrupts enabled
/* USER CODE END 2 */
```
```c
/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM3) {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin); // Toggle the PE7 LED
    }
}
/* USER CODE END 4 */
```
📝 Result
Once the system is powered, the 16 MHz signal generated at PA8 triggers the TIM3 peripheral via the PD2 pin. The timer hardware-counts these pulses and generates an update event (interrupt) every 8,000 cycles. This results in the LED on PE7 blinking rhythmically at exactly 2 Hz (0.5-second intervals).