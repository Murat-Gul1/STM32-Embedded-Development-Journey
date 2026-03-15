# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/w0XGTNhIN_c?feature=share)
# Dynamic Score Display (STM32 & Nextion HMI)


## Key Features
* **UART Communication:** Configured hardware UART on the STM32 to transmit formatted commands to the Nextion display.
* **Dynamic Text Updating:** Converts integer values (such as an active game score or timer) into strings and sends them to specific text objects (e.g., `t0`, `t1`) on the user interface.

* **Command Termination:** Implements the `0xFF 0xFF 0xFF` byte sequence strictly required by the Nextion instruction set to successfully execute commands.


## Hardware Requirements
* STM32 Development Board
* Nextion HMI Display
* USB-to-TTL Converter (for flashing the Nextion UI via Nextion Editor)
* Jumper Wires

## Software & Tools
* **STM32CubeIDE:** For microcontroller configuration and C programming.
* **Nextion Editor:** For designing the graphical user interface and generating custom `.zi` fonts.
