# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/J_THG6B-4Tc?feature=share)
# STM32 + Nextion HMI Calculator

This professional embedded systems project, developed as part of a broader software development engagement, utilizes an STM32F407 Discovery board and a Nextion HMI to create a robust, interrupt-driven calculator capable of processing complex mathematical expressions. By leveraging UART communication at 115200 baud, the system ensures real-time responsiveness through a character-echo mechanism that provides immediate visual feedback on the display. The backend logic employs the Shunting-yard algorithm to convert infix notation into Reverse Polish Notation (RPN), effectively managing operator precedence (BODMAS/PEMDAS) for addition, subtraction, multiplication, division, and modulo operations, while providing a seamless transition between input and result pages.

### 📡 Hardware Connections & Specifications

| Feature / Pin | STM32F407 (Master) | Nextion HMI (Slave) | Description |
| :--- | :--- | :--- | :--- |
| **UART TX** | **PA2** | **RX** | Data transmission to display |
| **UART RX** | **PA3** | **TX** | Data reception from touch events |
| **Ground** | **GND** | **GND** | Shared reference point |
| **Baud Rate** | **115200** | **115200** | High-speed communication |
| **Logic** | **Interrupt-Driven** | **Event-Driven** | Non-blocking architecture |

### 🛠 Configuration Requirement
To enable float support for `sprintf` in STM32CubeIDE, add the following flag to your Linker settings:
`-u _printf_float`