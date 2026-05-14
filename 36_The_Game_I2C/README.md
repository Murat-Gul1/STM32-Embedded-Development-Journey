# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/rd8ueYZEPJw?feature=share)
# STM32F4 Space Shooter Game 🚀

A real-time space shooter game developed for the **STM32F407 Discovery** board using an **SSD1306 OLED** display and an **Analog Joystick**. This project demonstrates advanced embedded programming techniques such as DMA-driven peripheral management, double buffering, and real-time signal filtering.

## 🕹️ Game Mechanics
- **Movement:** Control the ship's vertical (Y-axis) position using the analog joystick.
- **Combat:** Fire lasers using the joystick's push-button (Micro Switch).
- **Enemies:** Enemies spawn at random altitudes (using the internal hardware RNG) and move from right to left.
- **Scoring:** Destroy enemies to increase your score.
- **Game Over:** If an enemy reaches the left edge of the screen, the game ends.

## 🛠️ Technical Features

### 1. High-Performance Display Rendering
- **DMA + Double Buffering:** To prevent screen tearing and flicker, the display is rendered using an 8-bit double buffer system.
- **I2C DMA:** The full 1024-byte screen buffer is sent to the SSD1306 via I2C DMA at 400kHz.
- **Address Management:** Uses `0x21` (Column Address) and `0x22` (Page Address) commands to reset the display cursor for seamless DMA transfers.

### 2. Precise Controls
- **ADC DMA (Continuous Mode):** Joystick axes are read continuously in the background without CPU intervention.
- **Signal Filtering:** Implements a digital low-pass filter `(filtered * 3 + raw) / 4` to smooth out joystick noise and provide fluid movement.
- **Sampling Time Optimization:** Configured with **480 Cycles** sampling time to prevent Bus Matrix starvation and ensure system stability.

### 3. Hardware Randomness
- **STM32 RNG Peripheral:** Uses the built-in True Random Number Generator (RNG) to determine enemy spawn heights, ensuring unpredictable gameplay.

## 🔌 Connection Map (Pinout)

| Component | Pin (STM32) | Function |
| :--- | :--- | :--- |
| **SSD1306 OLED** | PB6 | I2C1 SCL |
| | PB9 | I2C1 SDA |
| **Joystick** | PA1 | ADC1_IN1 (X-Axis) |
| | PA2 | ADC1_IN2 (Y-Axis) |
| | PA0 | EXTI0 (Fire Button - Pull-up) |
| **Power** | 3.3V | VCC |
| | GND | GND |

## 🚀 Setup & Build
1. Open the project in **STM32CubeIDE**.
2. Ensure **I2C1 Event/Error Interrupts** are enabled in the NVIC settings.
3. Ensure **ADC1 DMA** is set to **Circular Mode** with a data width of **Half Word**.
4. Build the project (`Ctrl + B`).
5. Flash the binary to the STM32F407 Discovery board.

## 📝 Known Solutions during Development
- **Black Screen:** Solved by shifting the I2C address (`0x3C << 1`) and adding a hardware reset delay.
- **System Freeze:** Solved by increasing ADC sampling time from 3 to 480 cycles to reduce Bus Matrix congestion.
- **Drawing Artifacts:** Solved by correctly configuring the SSD1306 memory addressing mode for DMA packets.

## 🎥 Screenshots
*(Add your game screenshots here)*

---
Developed as a deep-dive into STM32 HAL, DMA, and real-time game logic.