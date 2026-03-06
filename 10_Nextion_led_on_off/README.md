# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/xKkmz_lEnaw)

# STM32 & Nextion Display UART Communication 🚀

A robust MCU-to-MCU communication project demonstrating how to interface an STM32 microcontroller with a Nextion HMI touch display using UART/USART.

## 📌 Project Overview
This project goes beyond a simple "blink LED" application by establishing a clean and efficient communication layer between two independent microcontrollers. 

The Nextion display handles all the UI rendering (buttons, backgrounds, text updates) on its own built-in MCU. This completely offloads the graphical processing burden from the STM32. When a user interacts with the display, the Nextion screen transmits simple 1-byte hexadecimal payloads to the STM32. The STM32 captures this data using a **non-blocking Hardware Interrupt** to toggle an onboard LED instantly without stalling its main execution loop.

This architecture serves as the foundational communication layer for more complex upcoming projects, such as a microcontroller-based "Simon Says" memory game.

## 🛠️ Hardware & Software Requirements

### Hardware
* **MCU:** STM32F407G-DISC1 (or any STM32 development board)
* **Display:** Nextion NX3224K024_011 (2.4" Basic Series)
* **Adapter:** CP2102 USB-to-TTL Converter (for initial display programming)
* External LED and a 220Ω/330Ω resistor

### Software
* **STM32CubeIDE:** For MCU configuration (CubeMX) and C programming.
* **Nextion Editor:** For designing the HMI interface and compiling display logic.

## 🔌 Wiring & Connections

### 1. Nextion to STM32 (UART Cross-Connection)
| Nextion Pin | Wire Color | STM32 Pin | Function |
| :--- | :--- | :--- | :--- |
| **5V** | Red | **5V** | Power supply |
| **GND** | Black | **GND** | Common Ground |
| **TX** | Blue | **PA3 (USART2_RX)** | Transmit data to STM32 |
| **RX** | Yellow | **PA2 (USART2_TX)** | Receive data from STM32 |

### 2. LED Circuit
* **STM32 PC4 Pin** ➔ Resistor ➔ LED Anode (Long leg)
* **STM32 GND Pin** ➔ LED Cathode (Short leg)

## 💻 How It Works

### Nextion Side (HMI Logic)
A Dual-state button (`bt0`) is placed on the screen. The "Send Component ID" option is disabled to ensure only raw, clean data is transmitted.
In the **Touch Release Event**, the following code is executed:
```text
if(bt0.val==1)
{
  bt0.txt="OFF"
  printh 01
}
else if(bt0.val==0)
{
  bt0.txt="ON"
  printh 00
}
```
Pressing the button sends raw hex 0x01 over UART.

Pressing it again sends raw hex 0x00.

STM32 Side (Interrupt Logic)
USART2 is configured in Asynchronous Mode at a 9600 Baud Rate with Global Interrupts enabled.

Instead of a blocking HAL_UART_Receive() (Polling), the system relies on HAL_UART_Receive_IT() to listen for 1-byte payloads in the background. Once the byte is received, the hardware triggers the HAL_UART_RxCpltCallback function:
```text
uint8_t rx_data[1]; // Buffer for incoming data

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
    if (rx_data[0] == 0x01) // Button ON
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    }
    else if (rx_data[0] == 0x00) // Button OFF
    {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
    }
    
    // Re-arm the interrupt for the next incoming byte
    HAL_UART_Receive_IT(&huart2, rx_data, 1); 
  }
}
```