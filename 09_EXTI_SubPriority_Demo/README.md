# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/egXte7tgt-w)
# Cortex-M4 NVIC: Preemption vs. Sub-Priority Demonstration

## Overview
This project demonstrates the hardware-level interrupt management capabilities of the ARM Cortex-M4 architecture, specifically focusing on the Nested Vectored Interrupt Controller (NVIC). It provides a practical, hands-on example to illustrate the crucial differences between **Preemption Priority** and **Sub-Priority**.



In Cortex-M microcontrollers, interrupt priorities are split into two groups:
1. **Preemption Priority:** Determines if an interrupt can preempt (interrupt) another currently running interrupt.
2. **Sub-Priority:** Acts as a queueing mechanism. If multiple interrupts with the *same* preemption priority are pending, the one with the highest sub-priority executes first. It **cannot** preempt a running interrupt.

## Hardware Setup
The project uses 3 push buttons to trigger External Interrupts (EXTI) and 3 LEDs to visualize the interrupt service routines (ISR).

### Pin Configuration
* **Red LED System (Highest Priority):**
  * Button (EXTI0): `PA0`
  * LED (Output): `PE7`
* **Green LED System:**
  * Button (EXTI1): `PA1`
  * LED (Output): `PE8`
* **Yellow LED System:**
  * Button (EXTI2): `PA2`
  * LED (Output): `PE9`

## NVIC Configuration
The core of this demonstration lies in the NVIC settings configured via STM32CubeMX:

| Interrupt Source | Preemption Priority | Sub-Priority | Behavior |
| :--- | :---: | :---: | :--- |
| **SysTick Timer** | `0` | `0` | Highest priority to prevent `HAL_Delay()` deadlocks inside ISRs. |
| **EXTI Line 0 (Red)** | `1` | `0` | Can preempt Green and Yellow. |
| **EXTI Line 1 (Green)**| `2` | `1` | Cannot preempt Red. Cannot preempt Yellow. Executes before Yellow if both are pending. |
| **EXTI Line 2 (Yellow)**| `2` | `2` | Cannot preempt Red. Cannot preempt Green. Executes last if both are pending. |

*(Note: In Cortex-M architecture, a lower numerical value represents a higher logical priority).*

## How to Test and Observe
1. **Press the Red Button:** The Red LED turns on for 6 seconds. The processor is currently executing the EXTI0 ISR.
2. **Trigger Pending Interrupts:** While the Red LED is still on, press the Green Button, and then the Yellow Button (or vice versa). 
   * *Observation:* Neither the Green nor the Yellow LED turns on immediately. Because their preemption priority (2) is lower than Red's (1), they cannot interrupt the Red ISR. They are placed in a **Pending** state.
3. **Observe the Sub-Priority Resolution:** Once the Red LED turns off (EXTI0 ISR completes), the processor evaluates the pending interrupts.
   * *Observation:* Even if you pressed the Yellow button first, the **Green LED will always turn on next**. This is because Green and Yellow share the same preemption priority, but Green has a higher sub-priority (1 vs 2).
4. **No Mutual Preemption:** While the Green LED is on, pressing the Yellow button will not interrupt it (and vice versa). They will wait for each other to finish because they share the same preemption priority level.

## Key Takeaways
* **Preemption Priority is absolute power:** It is the only way an interrupt can pause another running interrupt.
* **Sub-Priority is a queue manager:** It only decides the execution order of pending interrupts when the processor becomes free.
* **SysTick Priority matters:** If you use `HAL_Delay()` inside an ISR, the SysTick timer's preemption priority must be strictly higher (numerically lower) than the ISR's priority, otherwise, the system will face a deadlock.

## Future Enhancements
This project serves as a foundational step in mastering Cortex-M4 interrupt handling. Future iterations will explore software-triggered interrupts (Pending IRQ) and critical section management using `BASEPRI` and `PRIMASK` registers.