# DC Motor System Identification

A system identification project for characterizing DC motor dynamics using quadrature encoder feedback and step response testing.

## 📝 Project Description

This project performs automated system identification on a DC motor by applying step inputs and measuring the motor's RPM response using a quadrature encoder. The collected data can be used to derive transfer functions and create mathematical models for control system design.

## 🎯 Purpose

System identification is crucial for:
- Determining motor transfer functions
- Estimating time constants and gains
- Designing model-based controllers (PID, state-feedback, etc.)
- Understanding motor dynamics and behavior
- Validating theoretical models

## ⚙️ Features

- Step response testing with configurable PWM levels
- Quadrature encoder decoding with interrupt-based counting
- Real-time RPM calculation
- CSV data logging for analysis
- Configurable test phases (baseline, step, decay)
- 20ms sampling rate for accurate data capture

## 🔧 Hardware Requirements

- Arduino board (Uno/Mega/Nano)
- DC motor with gearbox
- Quadrature encoder (CPR = 315 used in code)
- L298N or similar H-bridge motor driver
- Power supply for motor (6-12V depending on motor)
- Jumper wires

## 📌 Pin Configuration

```
Motor Control:
- PWM: Pin 9
- IN1 (Direction): Pin 6
- IN2 (Direction): Pin 7

Encoder:
- Channel A: Pin 2 (interrupt)
- Channel B: Pin 3 (interrupt)
```

## 🔬 Test Sequence

The code executes a three-phase step test:

1. **Baseline Phase** (2 seconds)
   - Motor off (PWM = 0)
   - Establishes zero reference
   
2. **Step Phase** (6 seconds)
   - Motor at full speed (PWM = 255)
   - Captures rise response
   
3. **Decay Phase** (2 seconds)
   - Motor off
   - Captures decay response

## 📊 Data Output

The system outputs CSV data via Serial (115200 baud):
```
time_ms, pwm, rpm
0, 0, 0.00
20, 255, 45.23
40, 255, 89.76
...
```

## 🚀 Usage Instructions

1. **Hardware Setup:**
   - Connect motor to H-bridge driver
   - Connect encoder to interrupt pins
   - Connect H-bridge to Arduino
   - Power up motor driver

2. **Upload and Run:**
   - Upload code to Arduino
   - Open Serial Monitor (115200 baud)
   - Reset Arduino to start test
   - Copy CSV data from Serial Monitor

3. **Data Analysis:**
   - Save CSV data to file
   - Import into MATLAB, Python, or Excel
   - Plot RPM vs Time
   - Fit transfer function models
   - Extract system parameters

## 📈 Analysis Methods

### In MATLAB:
```matlab
% Load data
data = readtable('motor_data.csv');

% Plot response
plot(data.time_ms, data.rpm);
xlabel('Time (ms)');
ylabel('RPM');
title('Motor Step Response');

% System Identification Toolbox
sys = tfest(iddata(data.rpm, data.pwm, 0.02));
```

### In Python:
```python
import pandas as pd
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# Load and plot
data = pd.read_csv('motor_data.csv')
plt.plot(data['time_ms'], data['rpm'])
plt.xlabel('Time (ms)')
plt.ylabel('RPM')
plt.title('Motor Step Response')
plt.show()

# Fit first-order model: K/(τs + 1)
```

## 🔄 Customization

Modify these parameters for your motor:

```cpp
const int CPR = 315;              // Encoder counts per revolution
const int PWM_STEP = 255;         // Step amplitude (0-255)
const unsigned long T_BASELINE = 2000;  // Baseline duration (ms)
const unsigned long T_STEP = 6000;      // Step duration (ms)
const unsigned long SAMPLE_INTERVAL = 20; // Sample time (ms)
```

## 📐 Encoder Configuration

The code uses quadrature decoding with a lookup table for accurate position tracking:
- 4x counting mode (maximum resolution)
- Interrupt-driven for precise timing
- Direction detection included

**To change encoder CPR:**
1. Measure your encoder's actual CPR
2. Update: `const int CPR = YOUR_CPR;`

## ⚠️ Important Notes

- **Encoder CPR**: Must be accurate for correct RPM calculation
- **Sampling Rate**: 20ms gives 50Hz data rate
- **Test Duration**: Total test is 10 seconds
- **Serial Buffer**: Large CSV output - ensure no data loss
- **Motor Load**: Test with actual load conditions if needed

## 🎓 Control System Applications

Use the identified model for:

1. **PID Tuning**: Design optimal PID gains
2. **State-Space Control**: Implement state-feedback controllers
3. **Model Predictive Control**: Use model for predictions
4. **Observer Design**: Create state estimators
5. **Feedforward Compensation**: Improve tracking performance

## 🔮 Extensions

- Add multiple step levels for better model fitting
- Implement frequency sweep (chirp) for frequency response
- Add load torque measurement
- Include temperature compensation
- Log data to SD card for longer tests
- Add automatic model fitting on Arduino

## 📚 Theory Reference

First-order motor model:
```
G(s) = K / (τs + 1)
```
Where:
- K = DC gain (RPM/PWM)
- τ = Time constant (seconds)

## 🛠️ Troubleshooting

**No RPM reading:**
- Check encoder connections
- Verify power to encoder
- Test encoder channels with Serial.println()

**Erratic RPM values:**
- Check for electrical noise
- Add capacitors to encoder lines
- Verify encoder CPR setting

**Motor doesn't run:**
- Check H-bridge connections
- Verify motor power supply
- Test motor driver enable pins

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*
