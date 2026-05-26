# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/I_smqlOg2r4)

# STM32 Target Radar & Laser Firing System

This project is an embedded system developed on the **STM32F407VGTX** microcontroller. It acts as a miniature radar and targeting system that can be manually controlled via a joystick to scan for objects. When a target is detected within a specific range, its position and distance are recorded and displayed on an OLED screen. The user can then select any of the recorded targets, automatically aim the system at it, and "fire" a laser.

## 🚀 Features

*   **Joystick Controlled Servo**: Manually sweep the area by controlling a servo motor using the X-axis of an analog joystick. A deadband algorithm is implemented to prevent jitter.
*   **Automatic Target Detection**: Uses an HC-SR04 ultrasonic sensor to detect objects. If an object is closer than 20 cm, its distance and angle are automatically saved to memory.
*   **Target Memory System**: Can store up to 3 different targets, preventing duplicate recordings by checking distance and angle thresholds.
*   **Interactive OLED Menu**: Displays the list of recorded targets on an SSD1306 OLED display. Users can navigate the menu using the Y-axis of the joystick.
*   **Auto-Aiming**: Selecting a target from the OLED menu automatically drives the servo motor to the exact angle where the target was detected.
*   **Laser Firing Mechanism**: Pressing the "Fire" button triggers a laser module, simulating a firing sequence at the selected target.
*   **System Reset**: A dedicated "Clear" button erases all stored targets, clears the screen, and resets the servo to its default center position (90 degrees).

## 🛠️ Hardware Components

*   **Microcontroller**: STM32F407VGTX (Discovery Board / Custom Board)
*   **Display**: SSD1306 OLED Display (I2C)
*   **Sensor**: HC-SR04 Ultrasonic Distance Sensor
*   **Actuator**: SG90 or MG995 Servo Motor
*   **Input**: 2-Axis Analog Joystick
*   **Output**: Laser Diode Module
*   **Buttons**: 2x Tactile Push Buttons (Clear and Fire)

## ⚙️ Software Architecture & Peripherals

The project leverages several STM32 hardware peripherals for efficient, non-blocking operations:

*   **ADC with DMA (Analog to Digital Converter)**: Continuously reads the X and Y axes of the joystick in the background using DMA, mapping the X-axis to servo angles (0-180°) and the Y-axis to OLED menu navigation.
*   **TIM2 PWM (Pulse Width Modulation)**: Generates the precise signals required to position the servo motor.
*   **TIM9 Input Capture**: Measures the pulse width of the HC-SR04 `ECHO` pin using hardware timers, providing highly accurate microsecond resolution for distance calculation.
*   **I2C with DMA**: Communicates with the SSD1306 OLED display. Framebuffer updates are sent via DMA to avoid blocking the main CPU loop.
*   **EXTI (External Interrupts)**: Handles the "Clear" and "Fire" buttons to ensure immediate response without relying on polling.

## 🎮 How to Use

1.  **Power On**: Once powered, the system initializes, and the servo moves to the starting position. The OLED will be clear.
2.  **Scan for Targets**: Move the joystick left and right (X-axis) to rotate the servo. The ultrasonic sensor will scan the area.
3.  **Target Acquisition**: If an object is found within **20 cm**, the system automatically registers it. You will see it appear on the OLED display in the format: `> Target:1 cm:15.5`.
4.  **Navigate Menu**: Move the joystick up and down (Y-axis) to move the cursor (`>`) on the OLED display to select between the saved targets.
5.  **Auto-Aim**: As you change your selection in the menu, the servo motor will automatically rotate to aim at the selected target.
6.  **Fire**: Press the **Fire** button to activate the laser module. The laser will blink rapidly, simulating a firing sequence.
7.  **Clear**: Press the **Clear** button to erase all targets, wipe the screen, and return to the center position to start a new scan.

## 👨‍💻 Code Highlights

- Jitter reduction via angle difference threshold calculation (`deadband`).
- Anti-spam and anti-duplicate targeting logic (requires at least 20 degrees of movement and 1 second between consecutive saves).
- Hardware-level Input Capture for non-blocking acoustic distance measurement.
