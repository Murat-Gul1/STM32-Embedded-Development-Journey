# STM32 ADC Potentiometer Reader (Polling Mode)

This project demonstrates how to read an analog voltage from a potentiometer using the ADC (Analog-to-Digital Converter) on an **STM32F407VGT6** microcontroller. The implementation uses **Polling Mode** with **Continuous Conversion** for real-time data updates.

## 🛠 Hardware Configuration
- **Board:** STM32F4 Discovery (or similar F407 system)
- **Peripheral:** ADC1, Channel 1
- **Input Pin:** PA1
- **Potentiometer:** 10kΩ (Recommended) or 500kΩ (Requires custom sampling time)

## ⚙️ CubeMX Settings
To achieve reliable readings, the following ADC parameters are configured:
- **Clock Prescaler:** PCLK2 divided by 4 (to keep ADCCLK within stable limits).
- **Resolution:** 12-bit (0 to 4095 range).
- **Continuous Conversion Mode:** **ENABLED** (Crucial for real-time value updates).
- **Sampling Time:** 84 Cycles (Balanced for stability and speed).

## ⚠️ The Impedance Challenge: 10kΩ vs. 500kΩ
One of the most common mistakes in embedded design is choosing a potentiometer with too high resistance without adjusting the sampling time.

### 10kΩ Potentiometer (Ideal)
When using a **10kΩ** pot, the internal ADC sampling capacitor ($C_{ADC}$) charges very quickly. The default sampling time (e.g., 84 cycles) is more than enough for the capacitor to reach the actual input voltage, resulting in **accurate and stable** readings.

### 500kΩ Potentiometer (High Impedance)
Using a **500kΩ** pot significantly increases the charging time constant ($\tau = R_{total} \times C_{ADC}$). 
- **The Problem:** With a short sampling time, the ADC switch opens before the internal capacitor is fully charged. 
- **The Result:** You will read a lower voltage than actual, and the values will be highly unstable or "laggy."
- **The Fix:** If you must use a 500kΩ pot, you **must** set the `Sampling Time` to the maximum (480 Cycles) and consider adding a **0.1µF capacitor** between the PA1 pin and GND to provide a charge reservoir.

## 💻 Code Snippet
The core logic resides in the main loop:

```c
/* Start ADC once outside the loop (Continuous Mode must be Enabled) */
HAL_ADC_Start(&hadc1);

while (1) {
    /* Wait for conversion to finish */
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        /* Retrieve 12-bit value (0-4095) */
        uint16_t pot_value = HAL_ADC_GetValue(&hadc1);
        
        /* Process data... */
    }
}
```