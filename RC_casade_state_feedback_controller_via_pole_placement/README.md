# RC Cascade State-Feedback Controller via Pole Placement

An advanced cascade control system for RC circuits implementing state-feedback control with integral action using pole placement design methodology.

## 📝 Project Description

This project implements a sophisticated cascade state-feedback controller for a two-stage RC circuit. The controller uses pole placement to achieve desired closed-loop dynamics and includes integral action for zero steady-state error to step references.

## 🎯 Control Architecture

### Cascade Configuration:
- **Inner Loop**: State-feedback control of RC circuit states
- **Outer Loop**: Integral action for reference tracking
- **Pole Placement**: Systematic controller design for desired dynamics

### Control Law:
```
u = -K*x + Ko*∫e dt
```

Where:
- `K = [k1, k2]` = State feedback gains
- `Ko` = Integral gain
- `x = [x1, x2]'` = State vector (capacitor voltages)
- `e = r - x2` = Tracking error

## ⚙️ Features

- Cascade state-feedback control
- Pole placement-based controller design
- Integral action for zero steady-state error
- Real-time state estimation from sensors
- 1ms sampling rate digital implementation
- Adjustable reference via potentiometer
- Full state feedback (both capacitor voltages)

## 🔧 Hardware Requirements

- Arduino board (Uno/Mega/Nano)
- Two-stage RC circuit:
  - First stage: R1-C1
  - Second stage: R2-C2
- Potentiometer (10kΩ) for reference input
- Voltage measurement circuits (if voltage dividers needed)
- PWM-capable output stage
- Power supply
- Breadboard and jumper wires

## 📌 Pin Configuration

```
Analog Inputs:
- A0 (Vc1): First capacitor voltage (state x1)
- A1 (Vc2): Second capacitor voltage (state x2)
- A2 (VPot): Reference voltage input (r)

PWM Output:
- Pin 11: Control signal output
```

## 🎓 Control Theory

### State-Space Model

The two-stage RC circuit can be represented as:
```
ẋ = Ax + Bu
y = Cx
```

Where:
- `x = [Vc1, Vc2]'` = State vector (capacitor voltages)
- `u` = Control input (PWM voltage)
- `y = Vc2` = Output (second capacitor voltage)

### Controller Design

**Step 1: State Feedback**
```
u = -Kx
```
Design K using pole placement for desired closed-loop poles.

**Step 2: Add Integral Action**
```
u = -Kx + Ko∫(r - y)dt
```
Design Ko for steady-state performance.

### Given Controller Gains

```cpp
float k1 = -1.8985;  // Feedback gain for x1
float k2 = 1.1107;   // Feedback gain for x2
float ko = 0.2122;   // Integral gain
```

These gains were designed using pole placement for:
- Desired closed-loop poles
- Stability margins
- Transient response specifications

## 📊 Control Variables

The code implements:
```cpp
x1 = Vc1;              // First state
x2 = Vc2;              // Second state (output)
r = potentiometer;     // Reference input
e = r - x2;            // Tracking error
I = ∫e dt;             // Integral of error
kx = k1*x1 + k2*x2;    // State feedback term
u = -kx + ko*I;        // Total control signal
```

## 🚀 Usage Instructions

1. **System Identification:**
   - Build two-stage RC circuit
   - Measure R1, C1, R2, C2 values
   - Derive state-space matrices A, B, C

2. **Controller Design:**
   - Choose desired closed-loop poles
   - Calculate state feedback gains using pole placement
   - Design integral gain for reference tracking
   - Update gains in code

3. **Implementation:**
   - Connect circuit to Arduino
   - Verify voltage measurements on A0, A1, A2
   - Upload code
   - Test with different reference inputs

4. **Tuning:**
   - Adjust gains if needed
   - Monitor transient response
   - Verify steady-state tracking

## 📈 Performance Metrics

Monitor these characteristics:
- **Rise Time**: Speed of response to reference changes
- **Overshoot**: Maximum deviation above reference
- **Settling Time**: Time to reach steady-state
- **Steady-State Error**: Should be zero (integral action)
- **Disturbance Rejection**: Response to load changes

## 🔄 Design Process

### To design your own controller:

1. **System Identification**
   ```matlab
   % Measure RC values
   R1 = 1000; C1 = 100e-6;
   R2 = 1000; C2 = 100e-6;
   
   % Derive state-space model
   A = [-1/(R1*C1), 0; 
        1/(R2*C1), -1/(R2*C2)];
   B = [1/(R1*C1); 0];
   C = [0, 1];
   ```

2. **Pole Placement**
   ```matlab
   % Choose desired poles
   poles = [-100, -200];  % Rad/s
   
   % Calculate gains
   K = place(A, B, poles);
   k1 = K(1);
   k2 = K(2);
   ```

3. **Integral Design**
   ```matlab
   % Augment system for integral action
   % Design Ko for zero steady-state error
   Ko = -1 / (C * inv(A - B*K) * B);
   ```

4. **Discretization**
   - Sample time Ts = 1ms
   - Use Tustin or ZOH for discrete implementation

## 🎯 Advantages of This Approach

**State Feedback:**
- Full control over closed-loop dynamics
- Place poles anywhere in complex plane
- Multi-variable control capability
- Optimal transient response

**Integral Action:**
- Eliminates steady-state error
- Robust to constant disturbances
- Type 1 servo system
- Maintains zero error to step inputs

**Pole Placement:**
- Systematic design procedure
- Predictable closed-loop behavior
- No trial-and-error tuning
- Based on system model

## ⚠️ Important Considerations

**State Measurement:**
- Both capacitor voltages must be measured
- Use voltage dividers if > 5V
- Consider noise filtering
- Ensure accurate ADC readings

**Sampling Rate:**
- 1ms sampling (1kHz)
- Must be faster than system dynamics
- Ensure loop execution time < 1ms
- Consider computational load

**Saturation:**
- PWM limits: 0-255
- Physical voltage limits
- Implement anti-windup for integral term
- Monitor actuator limits

## 🔮 Extensions

- Add state observer for unmeasured states
- Implement LQR (Linear Quadratic Regulator)
- Add feedforward for reference tracking
- Include disturbance observer
- Implement gain scheduling
- Add adaptive control
- Multi-input multi-output (MIMO) extension

## 📚 Theory References

- **Pole Placement**: Ackermann's formula, direct design
- **State-Space Control**: Modern Control Engineering
- **Integral Augmentation**: Type 1 servo design
- **Digital Implementation**: Discrete-time systems

## 🛠️ Troubleshooting

**Unstable system:**
- Verify gain signs (k1, k2, ko)
- Check pole locations (left half-plane?)
- Reduce integral gain Ko
- Verify state measurements

**Poor tracking:**
- Increase integral gain Ko
- Check reference scaling
- Verify steady-state gain
- Monitor saturation

**Oscillations:**
- Poles too far left (too fast)
- Reduce state feedback gains
- Add damping (move poles to real axis)
- Check for measurement noise

**Steady-state error:**
- Integral action not working
- Check error calculation (e = r - x2)
- Verify integral implementation
- Check Ko sign and value

## 📐 Example Design

For a system with:
- Time constant τ1 = 10ms, τ2 = 20ms
- Desired settling time: 50ms
- No overshoot

Choose poles at:
- p1 = -80 rad/s (real)
- p2 = -150 rad/s (real)

This gives fast response without oscillation.

## 🎓 Learning Outcomes

By implementing this project, you'll understand:
- State-space representation
- Pole placement design
- State feedback control
- Integral action implementation
- Cascade control structures
- Digital control implementation
- Control system analysis

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*
