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
```c
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

flowchart TD
    Start([Start]) --> Closed

    Closed -->|Button Pressed\n(PA0 == 1)| In_Line
    In_Line -->|Button Pressed\n(PA0 == 1)| Flashing_Light
    Flashing_Light -->|Button Pressed\n(PA0 == 1)| Flasher
    Flasher -->|Button Pressed\n(PA0 == 1)| Closed

    Closed:::state
    In_Line:::state
    Flashing_Light:::state
    Flasher:::state

    Closed_note["All LEDs OFF"]
    In_Line_note["Sequential LEDs<br/>(Green → Orange → Red → Blue)"]
    Flashing_note["Alternating LEDs<br/>(Green+Red → Orange+Blue)"]
    Flasher_note["Flasher Animation<br/>(All LEDs ON → All LEDs OFF)"]

    Closed --- Closed_note
    In_Line --- In_Line_note
    Flashing_Light --- Flashing_note
    Flasher --- Flasher_note

    classDef state fill:#f9f9f9,stroke:#333,stroke-width:1px;
