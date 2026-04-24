# TailSitter HIL (Hardware-in-the-Loop) Simulation

# 🎥 [Watch the Project Demo on YouTube](https://youtu.be/i36wjRwoYaM)
This project is a Hardware-in-the-Loop (HIL) simulation for a TailSitter Drone (a vertical takeoff and landing UAV), developed using an STM32F407VGTX microcontroller and MATLAB/Simulink.

## Overview
The goal of this project is to simulate the flight dynamics of a TailSitter drone in real-time on real embedded hardware. 
Instead of running the physics simulation solely on a PC, the dynamics model designed in Simulink (`TailSitter_Sim.slx`) is translated to C code and runs directly on the STM32 board. The STM32 continuously calculates the drone's physical states (like altitude) based on inputs and streams the simulated telemetry data to MATLAB for real-time visualization.

## Architecture

### 1. Embedded Software (STM32CubeIDE)
- The core physics logic was generated via Simulink Coder and integrated into the STM32 project (`TailSitter_Sim.c`, `TailSitter_Sim_data.c`).
- The microcontroller executes the `TailSitter_Sim_step()` function in an infinite loop within `main.c`. 
- For testing purposes, a static PWM value of `0.6` (60% throttle) is currently applied to all four motors.
- Every 10 milliseconds (at an update rate of 100 Hz), the STM32 formats 4 simulated sensor variables outputs to a string and transmits them over `USART2` (configured for 115200 baud rate) to the host computer.

### 2. PC Telemetry and Visualization (MATLAB)
Two key MATLAB scripts are included to define physics and interface with the hardware:
- **`Init.m`**: This configuration script initializes the physical parameters of the simulated drone into the MATLAB workspace. Parameters include its mass (`0.5 kg`), motor properties (KV `1400`, voltages), propeller coefficients for thrust (`c_T`) and torque (`c_M`), moments of inertia (`Ixx`, `Iyy`, `Izz`), and the motor mixer matrix (`M_alloc`).
- **`grafik_drone.m`**: A live visualization script. It opens a serial connection on `COM5` to read the incoming stream of data from the STM32. It parses the 4 comma-separated values and dynamically plots the virtual drone's Z-axis position (altitude) in real-time using an animated chart.

## How to Run

1. Open the project in STM32CubeIDE.
2. Compile the project and flash the resulting firmware to the STM32F407VGTX development board.
3. Keep the board connected to the PC via USB.
4. Open MATLAB. 
5. Run the `Init.m` script to load the necessary constant variables into your workspace.
6. Open `grafik_drone.m` and verify that the `portAdi` variable matches the COM port assigned to your STM32 by Windows (Default is set to `COM5`).
7. Run the `grafik_drone.m` script. You will see a live updating graph visualizing the drone's simulated height (Z-Axis) as it responds to the static 60% throttle input.
