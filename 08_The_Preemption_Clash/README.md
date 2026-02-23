# 🎥 [Watch the Project Demo on YouTube](https://www.youtube.com/watch?v=q6xtBsvfkU0)

## 📌 Project Overview
"The Preemption Clash" is a bare-metal embedded C project designed for the STM32 (ARM Cortex-M4) microcontroller. Its primary goal is to visually demonstrate how the **Nested Vectored Interrupt Controller (NVIC)** handles concurrent hardware interrupts, task prioritization, and interrupt queuing.

By using simple GPIO inputs (buttons) and outputs (LEDs) with deliberate delay blocks (`HAL_Delay`), this project showcases two critical real-time operating concepts on a hardware level:
1. **Interrupt Preemption (Nesting):** A higher-priority task interrupting a running lower-priority task.
2. **Interrupt Pending:** The hardware queuing a lower-priority trigger while a higher-priority task is active, ensuring no signals are lost.

## 🛠️ Hardware Setup
The project utilizes two buttons and two LEDs to represent different tasks:

* 🔴 **High-Priority Task (Left Button & Red LED)**
  * **Trigger:** EXTI Line 0 (e.g., PB0)
  * **Action:** Turns on the Red LED for **3 seconds**.
  * **Priority Level:** 1 (Higher priority)

* 🟢 **Low-Priority Task (Right Button & Green LED)**
  * **Trigger:** EXTI Line 15_10 (e.g., PC13)
  * **Action:** Turns on the Green LED for **5 seconds**.
  * **Priority Level:** 2 (Lower priority)

## ⚙️ NVIC Configuration (The Core Logic)
To make this demonstration work without deadlocks, the Cortex-M4 priority grouping and levels are configured as follows:
* **Priority Grouping:** 4 bits for pre-emption priority, 0 bits for subpriority.
* **SysTick Timer:** Priority `0` *(Crucial: Must be the highest priority so `HAL_Delay()` functions correctly inside the Interrupt Service Routines).*
* **EXTI0 (Red Task):** Priority `1`
* **EXTI15_10 (Green Task):** Priority `2`



## 🚀 Demonstration Scenarios

### Scenario 1: The Preemption (Interrupting a Task)
1. Press the **Right Button**. The Green LED turns on, and the processor enters a 5-second delay.
2. While the Green LED is still on, press the **Left Button**.
3. **What happens:** The NVIC instantly recognizes the higher-priority EXTI0 signal. It suspends the 5-second Green task and immediately executes the Red LED task. The Red LED stays on for 3 seconds, turns off, and then the processor flawlessly returns to finish the remaining time of the Green LED task. 

### Scenario 2: The Pending State (Queuing a Task)
1. Press the **Left Button**. The Red LED turns on, and the processor enters a 3-second critical delay.
2. While the Red LED is still on, press the **Right Button**.
3. **What happens:** The NVIC knows the Red task has higher priority, so it does *not* interrupt it. However, the processor *does not ignore* the Right Button press. It registers the EXTI15_10 interrupt into a **"Pending"** state. 
4. The exact microsecond the Red LED finishes its 3-second task, the hardware automatically pulls the Green task from the pending queue and executes it (turning on the Green LED for 5 seconds) without needing another button press!

## 💡 Why This Matters
Understanding Preemption and Pending states is critical for developing robust, real-time embedded systems. It ensures that life-saving or time-critical hardware events (like an emergency motor stop or a fault detection) are executed instantly, while less critical background tasks are safely paused or queued without data loss.