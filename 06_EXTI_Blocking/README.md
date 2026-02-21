# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/5KHQ8_AL5Nk)
System Blocking with Interrupts

This project aims to demonstrate how external interrupts (EXTI) work on an STM32F407 Discovery board and how they can completely halt the main system if misused.

## 📌 Project Purpose
To trigger an interrupt using an external button (PA1) and intentionally trap the processor inside a heavy loop within the interrupt callback function. This allows us to observe how the Main Loop gets blocked.

## 🛠 Hardware Requirements
* STM32F407G Discovery Kit
* 1x Red LED (External)
* 1x 10k Ohm Resistor
* 1x Tactile Button
* Breadboard and Jumper Wires

## 🏗 Wiring & Connections
* **Green LED:** Connected to PA2 (Heartbeat indicator in the main loop).
* **Button (PA1):** Connected with a 10k pull-down resistor (Provides 3.3V to PA1 when pressed).
* **Red LED (PA3):** Alarm LED indicating that the interrupt has been triggered.

## 💻 The Critical Code Block
The infamous mistake that traps the processor inside the interrupt service routine (ISR):

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if(GPIO_Pin == GPIO_PIN_1) {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); // Turn on Red LED
        
        // THE BLOCKING LOOP: Trapping the processor
        for(volatile uint32_t i = 0; i < 10000000; i++);    
        
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); // Turn off Red LED
    }
}

⚠️ Observation and Conclusion
When the button is pressed, the Red LED turns on. During this time, the Green LED completely stops blinking (freezes).

Why? The processor enters a high-priority interrupt state and gets stuck in the heavy for loop. Since it hasn't finished its task in the ISR, it cannot return to the while(1) main loop to toggle the Green LED.
The Golden Rule: Interrupt Service Routines (ISR) must always be kept as short and fast as possible!