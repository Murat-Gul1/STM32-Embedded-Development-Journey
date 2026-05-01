# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/ioil8WCoEsM)
# STM32 PWM LED Dimming Project

This project demonstrates how to control the brightness of an external LED using **Pulse-Width Modulation (PWM)** on an STM32F407VGT6 microcontroller (Discovery Board). The fading effect is achieved by incrementally changing the duty cycle of the PWM signal.

## Hardware Specifications
- **MCU:** STM32F407VGT6 (Cortex-M4)
- **Board:** STM32F4 Discovery
- **Timer:** TIM3, Channel 3
- **Output Pin:** PB0 (Connected to an external LED via a resistor)

## Project Configuration (STM32CubeMX)

### Clock Configuration
- **HCLK:** 168 MHz
- **APB1 Timer Clock:** 84 MHz (Internal clock source for TIM3)

### TIM3 Peripheral Settings
- **Mode:** PWM Generation CH3
- **Prescaler (PSC):** 839
- **Counter Period (ARR):** 999
- **PWM Mode:** PWM Mode 1
- **CH Polarity:** High

#### Frequency Calculation:
$Frequency = \frac{Internal Clock}{(PSC + 1) \times (ARR + 1)}$
$Frequency = \frac{84,000,000}{840 \times 1000} = 100\text{ Hz}$

## Project Logic
The firmware uses a nested `while` loop to vary the `CCR3` (Capture Compare Register) value from 0 to 999 and back.
1. **Fade In:** Increases the `Pulse` value every 1ms until it reaches the `Period` (ARR).
2. **Fade Out:** Decreases the `Pulse` value every 1ms until it reaches 0.

## Code Snippet (main.c)

```c
/* Start PWM on TIM3 Channel 3 */
HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

uint16_t dutyCycle = 0;

while (1) {
    // Brighten
    while(dutyCycle < 999) {
        dutyCycle++;
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, dutyCycle);
        HAL_Delay(1);
    }
    // Dim
    while(dutyCycle > 0) {
        dutyCycle--;
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, dutyCycle);
        HAL_Delay(1);
    }
}
```