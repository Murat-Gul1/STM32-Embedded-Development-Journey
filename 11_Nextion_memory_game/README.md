# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/P3RMER-qdm8)

# STM32 & Nextion HMI Memory Game ("Simon Says") 🎮

## 📖 About the Project / Proje Hakkında
**[EN]** This project is a hardware-based memory game inspired by "Simon Says". It demonstrates bidirectional, UART-based serial communication between an STM32 microcontroller and a Nextion HMI touch display. The system utilizes hardware interrupts for real-time response and dynamic UI updates.

**[TR]** Bu proje, "Simon Says" oyunundan ilham alan donanım tabanlı bir hafıza oyunudur. Bir STM32 mikrodenetleyicisi ile Nextion HMI dokunmatik ekranı arasında UART tabanlı çift yönlü seri haberleşmeyi gösterir. Sistem, gerçek zamanlı tepki ve dinamik arayüz güncellemeleri için donanımsal kesmeleri (Interrupt) kullanır.

## ✨ Features / Özellikler
* **Bidirectional UART Communication:** STM32 receives touch inputs and sends UI commands.
* **Hardware Interrupts (IT):** Non-blocking input handling using `HAL_UART_Receive_IT`.
* **Real-time Verification:** Player inputs are checked instantly against the sequence without waiting for the full input cycle.
* **Dynamic UI:** The current level is dynamically updated on the Nextion display.
* **Audio-Visual Feedback:** Dedicated LEDs for the sequence, a red LED for errors, and a buzzer for sound effects.

## 🛠️ Hardware Requirements / Donanım İhtiyaçları
* STM32 Microcontroller (e.g., STM32F407xx)
* Nextion HMI Touch Display (Connected via USB-TTL for initial programming)
* 3x Game LEDs (Different colors recommended)
* 1x Red Error LED
* 1x Active Buzzer
* Resistors (220Ω - 330Ω) & Jumper Wires

## 🔌 Wiring & Connections / Bağlantı Şeması



| STM32 Pin | Component / Bileşen | Mode | Description |
| :--- | :--- | :--- | :--- |
| **PA2 (TX)** | Nextion **RX** | UART2 (TX) | Sends Level data to Display |
| **PA3 (RX)** | Nextion **TX** | UART2 (RX) | Receives Button data from Display |
| **PE7** | LED A | GPIO Output | Game Sequence LED 1 |
| **PE8** | LED B | GPIO Output | Game Sequence LED 2 |
| **PE9** | LED C | GPIO Output | Game Sequence LED 3 |
| **PE10** | LED Red | GPIO Output | Game Over / Error Indicator |
| **PE11** | Buzzer | GPIO Output | Sound Feedback |
| **GND** | Nextion & LEDs GND | Ground | Common Ground is CRITICAL! |

## ⚙️ System Architecture / Sistem Mimarisi

### 1. Nextion ➔ STM32 (Input / Giriş)
When a user presses a button on the Nextion screen, the display sends a specific hexadecimal byte to the STM32 via the `Touch Release Event`:
* Button 1 (LED A) sends: `0x41` (Hex for 'A')
* Button 2 (LED B) sends: `0x42` (Hex for 'B')
* Button 3 (LED C) sends: `0x43` (Hex for 'C')

*Note: "Send Component ID" must be unchecked in the Nextion Editor.*

### 2. STM32 ➔ Nextion (Output / Çıkış)
When the player completes a level, the STM32 sends a command to update the text component (`t0`) on the Nextion display. The command format is:
`t0.txt="level X"` followed by three termination bytes `0xFF 0xFF 0xFF`.

```c
// Example snippet for updating the Nextion Display
void Update_Nextion_Level(uint8_t current_level){
    char cmd[20];
    int len = sprintf(cmd,"t0.txt=\"level %d\"", current_level);
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, len, 100);
    
    uint8_t terminator[] = {0xFF, 0xFF, 0xFF};
    HAL_UART_Transmit(&huart2, terminator, 3, 100);
}
```
