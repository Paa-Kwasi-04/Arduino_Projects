# Conveyor Belt Control System

An Arduino-based conveyor belt control system using stepper motor, IR sensor for object detection, and LCD display for status feedback.

## 📝 Project Description

This project implements an automated conveyor belt system that detects objects using an infrared (IR) sensor and controls a stepper motor to move the belt accordingly. The system displays real-time status on a 20x4 I2C LCD screen.

## ⚙️ Features

- Object detection using IR sensor
- Stepper motor control for precise belt movement
- Real-time status display on LCD
- Enable/disable motor control
- Visual feedback with IR output indicator

## 🔧 Hardware Requirements

- Arduino board (Mega recommended based on pin usage)
- Stepper motor
- Stepper motor driver (e.g., A4988 or DRV8825)
- IR sensor module
- 20x4 I2C LCD display (I2C address: 0x27)
- Power supply for stepper motor
- Jumper wires and breadboard

## 📌 Pin Configuration

```
Stepper Motor:
- DIR (Direction): Pin 2
- STEP (Step): Pin 3
- EN (Enable): Pin 4

IR Sensor:
- Input: Pin 13
- Output Indicator: Pin 49
```

## 📚 Required Libraries

- `Wire.h` (Built-in)
- `LiquidCrystal_I2C.h` (Install via Arduino Library Manager)

## 🚀 Installation

1. Install the LiquidCrystal_I2C library:
   - Open Arduino IDE
   - Go to Sketch → Include Library → Manage Libraries
   - Search for "LiquidCrystal I2C"
   - Install the library by Frank de Brabander

2. Connect the hardware according to the pin configuration

3. Upload the code to your Arduino board

## 💡 How It Works

1. The system continuously monitors the IR sensor for object detection
2. When an object is detected (IR sensor reads HIGH):
   - Stepper motor is activated
   - Motor steps with 800 microsecond delay between pulses
   - LCD displays "DETECTED"
3. When no object is detected:
   - Motor stops
   - LCD shows idle status

## 🎯 Usage

1. Power on the Arduino and ensure LCD displays correctly
2. Place an object in front of the IR sensor
3. The conveyor belt (stepper motor) will start moving
4. Remove the object to stop the belt

## 🔄 Customization

You can modify the following parameters in the code:

- **Motor Speed**: Adjust the `delaymicrosecond(800)` value
  - Lower values = faster speed
  - Higher values = slower speed
- **LCD Messages**: Change the text displayed on detection
- **Motor Steps**: Modify step logic for different movement patterns

## ⚠️ Troubleshooting

**LCD not displaying:**
- Check I2C address (use I2C scanner sketch if needed)
- Verify I2C connections (SDA, SCL)
- Adjust LCD backlight potentiometer

**Motor not moving:**
- Verify stepper driver is powered
- Check enable pin is set correctly (LOW = enabled)
- Ensure motor power supply is adequate

**IR sensor not detecting:**
- Adjust IR sensor sensitivity potentiometer
- Check sensor orientation and distance
- Verify sensor power and ground connections

## 📊 Applications

- Automated sorting systems
- Package detection on production lines
- Material handling systems
- Quality control inspection stations
- Educational robotics projects

## 🔮 Future Enhancements

- Add speed control with potentiometer
- Implement object counting
- Add multiple IR sensors for position tracking
- Include emergency stop button
- Add reverse direction capability
- Implement variable speed based on object size

## 📝 Notes

- Ensure adequate power supply for stepper motor (typically 12V)
- Use appropriate stepper driver current settings
- The enable pin is active LOW (LOW = motor enabled)
- Stepper timing can be adjusted based on your specific motor

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*
