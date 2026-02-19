# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/-c0Uupz5NaY?feature=share)
This project implements a **Finite State Machine (FSM)** using a **Linked List** approach in C to control various LED animations on an STM32 microcontroller. The states are cycled through using a user button.

## 📌 Project Overview
Instead of using standard `if-else` or `switch-case` structures, this project utilizes an advanced C programming technique where each state is defined as a `struct` containing a function pointer for its action and a standard pointer to the next state. 

This approach keeps the `main` loop clean and makes it incredibly easy to add or modify states without rewriting core logic.

## 🛠️ Hardware Requirements
* **Microcontroller:** STM32 Development Board (e.g., STM32F407G-DISC1)
* **Button:** User Button (PA0)
* **LEDs:** * Green LED (PD12)
  * Orange LED (PD13)
  * Red LED (PD14)
  * Blue LED (PD15)

## ⚙️ States (Animation Modes)
The system starts in the `closed` state. Each valid button press transitions the system to the next state. After the final state, it loops back to the beginning.

1. **Closed State:** All LEDs are turned off. (Standby mode)
2. **In Line State:** LEDs turn on and off sequentially (Green -> Orange -> Red -> Blue).
3. **Flashing Light State:** LEDs blink in diagonal pairs.
4. **Flasher State:** All LEDs flash simultaneously.

## 💻 Software Architecture
The state transitions are managed using the following `StateNode` structure. Each node points to the function to execute (`Action execute`) and the next state in the loop (`struct StateNode *next`).

### State Structure

typedef void(*Action)(void);
typedef struct StateNode{
    Action execute;
    struct StateNode *next;
} StateNode;
Main Loop Logic
The program continuously executes the current state's function (current_action->execute()). When a button press is detected (with debounce and release wait logic applied), the pointer simply moves to the next node:
if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET){
    HAL_Delay(50); // Debounce delay
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET){
        current_action = current_action->next; // Move to the next state
        // Wait until the user releases the button
        while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET); 
    }
}
### LED State Machine (FSM)

```mermaid
stateDiagram-v2
    [*] --> Closed : Start

    Closed --> In_Line : Button Pressed (PA0 == 1)
    In_Line --> Flashing_Light : Button Pressed (PA0 == 1)
    Flashing_Light --> Flasher : Button Pressed (PA0 == 1)
    Flasher --> Closed : Button Pressed (PA0 == 1)

    note right of Closed
        All LEDs OFF
    end note

    note right of In_Line
        Sequential LEDs
        (Green -> Orange -> Red -> Blue)
    end note

    note right of Flashing_Light
        Alternating LEDs
        (Green+Red -> Orange+Blue)
    end note

    note left of Flasher
        Flasher Animation
        (All LEDs ON -> All LEDs OFF)
    end note