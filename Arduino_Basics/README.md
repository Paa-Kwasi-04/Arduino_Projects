# Arduino Basics Projects

A comprehensive collection of fundamental Arduino projects designed for learning and experimentation. These projects cover essential concepts in electronics, sensors, actuators, and displays.

## 📂 Projects List

### 🔴 LED Projects
- **blinking_lights** - Basic LED blinking (Hello World of Arduino)
- **Led_button** - Control LED with push button
- **Led_potentiometer** - Analog control of LED brightness with potentiometer
- **Led_bar_potentiometer** - LED bar graph controlled by potentiometer
- **Led_breathing** - PWM breathing effect on LED
- **Led_relay** - Control relay module with LED indicator
- **Led_stream** - Sequential LED animation effects
- **RGB_led** - RGB LED color mixing
- **RGB_IRremote** - Control RGB LED with IR remote

### 📟 Display Projects
- **7_segment_display_1_digit** - Single digit 7-segment display
- **4_digit_segment_display** - Four digit 7-segment display
- **8_dot_matrix** - 8x8 LED matrix display
- **LCD_basics** - 16x2 LCD display fundamentals

### 🌡️ Sensor Projects
- **dht11_temp_humidity_sensor** - Temperature and humidity sensing
- **Digital_thermometer** - Digital temperature measurement and display
- **Ultrasonic_sensor** - Distance measurement using HC-SR04
- **PIR_sensor** - Motion detection with PIR sensor
- **Photoresistor** - Light level detection
- **MPU6050** - 6-axis accelerometer and gyroscope
- **tilt_switch** - Tilt detection sensor
- **Voltmeter** - Voltage measurement using analog input

### 🎮 Input Devices
- **Keypad_4x4** - 4x4 matrix keypad interface
- **PS2_joystick** - PlayStation-style joystick control
- **buzzer** - Piezo buzzer tone generation

### 🔧 Motor Control
- **DC_motor_1293d_control** - DC motor control with L293D driver
- **Servo_basics** - Servo motor positioning
- **Stepper_motor** - Stepper motor control and positioning

## 🎯 Learning Objectives

By working through these projects, you will learn:

- Digital I/O operations (digitalWrite, digitalRead)
- Analog I/O operations (analogWrite, analogRead)
- PWM (Pulse Width Modulation) control
- Serial communication for debugging
- Sensor interfacing and data acquisition
- Display technologies and protocols
- Motor control fundamentals
- Interrupt handling
- I2C and SPI communication protocols
- Libraries usage and integration

## 🛠️ Common Components Required

### Essential Components
- Arduino board (Uno/Mega/Nano)
- Breadboard and jumper wires
- LEDs (various colors)
- Resistors (220Ω, 1kΩ, 10kΩ)
- Push buttons
- Potentiometers

### Sensors
- DHT11 temperature & humidity sensor
- HC-SR04 ultrasonic sensor
- PIR motion sensor
- Photoresistor (LDR)
- MPU6050 IMU module
- Tilt switch

### Displays
- 16x2 LCD display (with I2C backpack recommended)
- 7-segment displays (single and 4-digit)
- 8x8 LED matrix

### Actuators & Control
- DC motors with L293D driver
- Servo motors
- Stepper motors
- Relay modules
- Piezo buzzer

### Input Devices
- 4x4 matrix keypad
- PS2 joystick module
- IR remote and receiver

## 📚 Getting Started

1. **Choose a project** based on your skill level and available components
2. **Gather components** listed in the project folder
3. **Open the .ino file** in Arduino IDE
4. **Install required libraries** (if any)
   - Go to Tools → Manage Libraries in Arduino IDE
   - Search and install needed libraries
5. **Connect components** according to the circuit diagram (if available)
6. **Upload the code** to your Arduino board
7. **Test and experiment** with the code!

## 💡 Tips for Beginners

- Start with **blinking_lights** if you're completely new
- Progress to **Led_button** to learn digital input
- Try **Led_potentiometer** for analog input understanding
- Work through display projects to learn different interfaces
- Experiment with sensors before moving to motors
- Always check component polarity (LEDs, sensors, motors)
- Use the Serial Monitor for debugging (Tools → Serial Monitor)

## 📖 Recommended Learning Path

**Level 1 - Basics:**
1. blinking_lights
2. Led_button
3. buzzer
4. Led_potentiometer

**Level 2 - Displays:**
1. 7_segment_display_1_digit
2. LCD_basics
3. 4_digit_segment_display

**Level 3 - Sensors:**
1. Photoresistor
2. Ultrasonic_sensor
3. dht11_temp_humidity_sensor
4. PIR_sensor

**Level 4 - Advanced:**
1. DC_motor_1293d_control
2. Servo_basics
3. MPU6050
4. RGB_IRremote

## 🔗 Useful Resources

- [Arduino Official Documentation](https://www.arduino.cc/reference/)
- [Arduino Language Reference](https://www.arduino.cc/reference/en/)
- [Arduino Forum](https://forum.arduino.cc/)

## 📝 Notes

- Pin numbers in the code may need adjustment based on your wiring
- Some projects require external libraries available through Arduino Library Manager
- Always double-check connections before powering up
- Use appropriate resistors to protect LEDs and components

---

*Happy Learning! 🚀*
