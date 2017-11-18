# STM32-based controller for DC/DC converter

## About
The purpose of this project was to develop DC motor microcontroller-based driver using
STM32F429I-DISCO evaluation board. Driver can be used as a closed-loop PI current controller,
closed-loop speed PID controller and as open-loop controller. Controllers parameters were
obtained in simulation process. Communication with driver is possible by using on-board touch
screen. Second part of work was windows application development. Application is used to control
DC motor operation.

## Directories
This repository consists of two parts:
- firmware - source files for STM32F429I-DISCO driver, written in C under TrueStudio environment
- software - source files for Windows application used as control panel with nice GUI for uC driver, written in C# under Visual Studio environment

## Tools & Libs
- Atollic True Studio 6.0.0
- Visual Studio 2013
- CubeMX - HAL
- STemWIN
