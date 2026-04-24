# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/xde5tDRIafE)
# STM32F407 Discovery - TIM6 Basic Timer Interrupt Project

This project demonstrates how to configure and use the **TIM6 (Basic Timer)** in **Interrupt Mode** on an **STM32F407G-DISC1** board. Instead of using software delays, this project implements a precise 0.5-second timebase using hardware timers and the NVIC (Nested Vectored Interrupt Controller).

## 🚀 Overview

The primary goal is to toggle the onboard Green LED (PD12) every **0.5 seconds (2 Hz)**. This is achieved by calculating the exact Prescaler and Period values based on the STM32F407's Clock Tree architecture.

## ⚙️ Hardware Specifications

- **MCU:** STM32F407VGT6 (Cortex-M4)
- **Board:** STM32F407G-DISC1 (Discovery)
- **Clock Source:** 8 MHz External Crystal (HSE)
- **System Clock (SYSCLK):** 168 MHz

## 🧠 The Mathematics & Theory

The timing is calculated using the following hardware formula:

$$UpdateEvent (Hz) = \frac{TimerClock}{(Prescaler + 1) \times (Period + 1)}$$

### 1. Clock Tree Configuration
- **HCLK (CPU Speed):** 168 MHz.
- **APB1 Bus:** Limited to **42 MHz** (168 MHz / 4).
- **Timer Multiplier Rule:** Since the APB1 prescaler is > 1, the hardware automatically multiplies the timer clock by **x2**.
- **Resulting TimerClock (TIM6):** 42 MHz * 2 = **84,000,000 Hz (84 MHz)**.

### 2. Handling the 16-Bit Limit
TIM6 is a 16-bit timer (Max value: 65,535). To avoid register overflow while creating a 0.5s delay, we scale the speed:
- **Prescaler (PSC):** Set to **8399** ($84,000,000 / 8400 = 10,000$ Hz).
- **Period (ARR):** To achieve 0.5s (2 Hz) from a 10 kHz clock, we need **5000** ticks.
- **Register Value:** Set to **4999** (Since counting starts from 0).

**Verification:**
$$84,000,000 / (8400 \times 5000) = 2 Hz \rightarrow 0.5 seconds.$$

## 🛠️ Project Configuration (STM32CubeMX)

1. **RCC:** Set High Speed Clock (HSE) to *Crystal/Ceramic Resonator*.
2. **Clock Configuration:**
   - Input Frequency: 8 MHz.
   - Set PLL Parameters to reach **168 MHz** HCLK.
   - Ensure **APB1 Timer Clocks** is **84 MHz**.
3. **TIM6:**
   - **Activated:** Checked.
   - **Prescaler:** 8399.
   - **Counter Period:** 4999.
4. **NVIC:** Enable *TIM6 global interrupt*.
5. **GPIO:** Set **PD12** as *GPIO_Output*.

## 💻 Key Code Snippets

### Start Timer in Interrupt Mode
```c
/* USER CODE BEGIN 2 */
HAL_TIM_Base_Start_IT(&htim6);
/* USER CODE END 2 */
```
Interrupt Callback Function
```c
/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    }
}
/* USER CODE END 4 */
```