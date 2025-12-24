# RC Circuit PI Controller

A digital PI (Proportional-Integral) controller implementation for RC circuit voltage regulation using Tustin discretization method.

## 📝 Project Description

This project implements a discrete-time PI controller for regulating the voltage across a capacitor in an RC circuit. The controller uses the Tustin (bilinear) discretization method to convert continuous-time control to digital implementation with 1ms sampling period.

## 🎯 Control Objective

Regulate capacitor voltage to match a user-defined setpoint voltage:
- **Input**: Desired voltage via potentiometer (0-5V)
- **Output**: PWM signal to charge/discharge capacitor
- **Feedback**: Measured capacitor voltage

## ⚙️ Features

- Incremental PI control algorithm
- Tustin discretization for digital implementation
- 1ms sampling rate (1kHz control loop)
- Real-time telemetry via Serial Monitor
- PWM output with anti-windup saturation
- Adjustable setpoint via potentiometer

## 🔧 Hardware Requirements

- Arduino board (Uno/Mega/Nano)
- RC circuit components:
  - Resistor (e.g., 1kΩ - 10kΩ)
  - Capacitor (e.g., 100µF - 1000µF)
- Potentiometer (10kΩ) for setpoint adjustment
- Voltage divider or buffer circuit if needed
- Breadboard and jumper wires

## 📌 Pin Configuration

```
Analog Inputs:
- A0: Capacitor voltage measurement (0-5V)
- A1: Potentiometer for setpoint (0-5V)

PWM Output:
- Pin 11: Control signal to charge circuit
```

## 🔬 Control Algorithm

### Incremental PI Form

The controller uses the incremental (velocity) form of PI:

```
u[k] = u[k-1] + a*(e[k] - b*e[k-1])
```

Where:
- `u[k]` = Control output at time k
- `e[k]` = Error signal (setpoint - measured)
- `a = 0.96464` = Controller gain coefficient
- `b = 0.982` = Derivative coefficient

### Tustin Discretization

Continuous PI controller:
```
C(s) = Kp + Ki/s
```

Discretized using bilinear (Tustin) transformation:
```
s = (2/Ts) * (z-1)/(z+1)
```

Where `Ts = 1ms` is the sampling time.

## 📊 Telemetry Output

Serial output at 115200 baud provides:
```
Setpoint: X.XXXX , Error_Signal: X.XXXX , Capacitor Volt: X.XXXX , PID Signal: X.XXXX , PWM Signal: XXX
```

Displays:
- **Setpoint**: Target voltage from potentiometer
- **Error_Signal**: Difference between setpoint and measurement
- **Capacitor Volt**: Current capacitor voltage
- **PID Signal**: Control signal in volts (0-5V)
- **PWM Signal**: PWM duty cycle (0-255)

## 🚀 Usage Instructions

1. **Hardware Setup:**
   - Build RC circuit with known R and C values
   - Connect capacitor voltage to A0 (ensure voltage ≤ 5V)
   - Connect setpoint potentiometer to A1
   - Connect PWM output (pin 11) to charging circuit

2. **Upload and Test:**
   - Upload code to Arduino
   - Open Serial Monitor (115200 baud)
   - Adjust potentiometer to change setpoint
   - Observe capacitor voltage tracking setpoint

3. **Data Logging:**
   - Use Serial Plotter for real-time visualization
   - Log data for performance analysis
   - Evaluate settling time and overshoot

## 📈 Performance Tuning

### To modify controller response:

**Change coefficients:**
```cpp
const float a = 0.96464;  // Increase for faster response
const float b = 0.982;    // Adjust for stability
```

**Adjust sampling time:**
```cpp
const unsigned long Ts_ms = 1;  // Sample period in ms
```

### Design New Controller:

1. Identify RC circuit parameters (R, C)
2. Design continuous-time PI controller:
   ```
   Kp = proportional gain
   Ki = integral gain
   C(s) = Kp + Ki/s
   ```
3. Apply Tustin discretization:
   ```
   a = Kp + (Ki*Ts)/2
   b = 1 - (Ki*Ts)/(2*Kp + Ki*Ts)
   ```

## 🎓 Control Theory Background

### Why Incremental Form?
- Reduces numerical error accumulation
- Easier anti-windup implementation
- Better for real-time systems
- Smoother output changes

### Why Tustin?
- No frequency warping at low frequencies
- Stable mapping from s-plane to z-plane
- Preserves steady-state accuracy
- Industry standard for control systems

## 📐 Circuit Considerations

**Voltage Scaling:**
- If capacitor voltage > 5V, use voltage divider
- Ensure ADC sees 0-5V range
- Adjust code for scaling factor

**PWM to Voltage:**
- May need op-amp buffer
- Consider MOSFET driver for higher power
- Add flyback diode for inductive loads

## ⚠️ Important Notes

- **Sampling Rate**: 1ms is aggressive - ensure loop completes in time
- **Saturation**: Controller includes 0-5V limits
- **Anti-windup**: Incremental form naturally limits integral buildup
- **Noise**: Consider adding filtering on analog inputs
- **Resolution**: 10-bit ADC gives ~5mV resolution

## 🔮 Extensions

- Add derivative term for PID control
- Implement adaptive gain scheduling
- Add reference feedforward
- Include disturbance rejection
- Log data to SD card
- Add LCD for parameter display
- Implement auto-tuning algorithm

## 📊 Performance Metrics

Typical metrics to evaluate:
- **Rise Time**: Time to reach 90% of setpoint
- **Settling Time**: Time to stay within ±2% of setpoint
- **Overshoot**: Maximum deviation above setpoint
- **Steady-State Error**: Final error after settling
- **Disturbance Rejection**: Response to load changes

## 🛠️ Troubleshooting

**Voltage not tracking:**
- Verify RC circuit connections
- Check voltage scaling
- Test PWM output with LED
- Verify ADC readings in Serial Monitor

**Oscillations:**
- Reduce proportional gain (decrease `a`)
- Increase sampling time
- Add output filtering
- Check for noise on analog inputs

**Slow response:**
- Increase controller gains
- Reduce RC time constant
- Check PWM frequency
- Verify power supply capacity

## 📚 References

- Tustin's method (bilinear transformation)
- Digital Control Systems - Phillips & Nagle
- Discrete-time PI controller design
- Anti-windup techniques

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*
