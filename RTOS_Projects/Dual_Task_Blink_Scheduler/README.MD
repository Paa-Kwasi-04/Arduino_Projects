Arduino Uno FreeRTOS Dual-Task LED Blinker
This project runs two independent FreeRTOS tasks on an Arduino Uno to blink two LEDs at different rates concurrently.

Hardware Requirements
Board: Arduino Uno
LEDs: 2 (e.g., Red and Green)
Resistors: 2 x 220 Ohm
Software Requirements
Arduino IDE
Library: Arduino_FreeRTOS (Install via Library Manager)

Wiring
Pin Connection
D5 Red LED (via resistor)
D6 Green LED (via resistor)
GND Resistors to ground

Code
The provided code defines two tasks:
LEDR_task: Blinks the LED on Pin 5 every 1000ms (500ms ON/OFF).
LEDG_task: Blinks the LED on Pin 6 every 400ms (200ms ON/OFF).
The tasks are created in setup() using xTaskCreate() and the scheduler is started with vTaskStartScheduler().

Usage
Install the Arduino_FreeRTOS library.
Upload the sketch to your Arduino Uno.
Observe the LEDs blinking simultaneously at different rates.
Notes
The Arduino Uno has limited RAM (2KB). If you encounter issues, try increasing the stack size in xTaskCreate() (e.g., from 128 to 256).
