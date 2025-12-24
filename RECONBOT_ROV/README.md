# RECONBOT ROV (Remotely Operated Vehicle)

A comprehensive ROV (Remotely Operated Vehicle) project featuring multiple sensor drivers, power monitoring systems, thruster control, and UART communication for underwater robotics applications.

## 📝 Project Description

RECONBOT is a remotely operated underwater vehicle project that includes various drivers and monitoring systems for sensors, power management, and thruster control. The system is designed for underwater exploration, monitoring, and remote operation.

## 🎯 Project Components

### 📂 RECONBOT_ROV_DRIVERS

Collection of driver modules for ROV sensors and actuators:

#### Power Monitoring
- **INA260_High_Current_Sensor** - High-side current/voltage/power monitoring using INA260 with I2C multiplexer support
- **INA3221_Low_Current_Sensor** - Triple-channel low-current monitoring
- **Combined_INA3221_INA260** - Integrated power monitoring solution
- **PowerSensor** - General power sensing and monitoring
- **DC_Resetable_Fuse** - Resettable fuse protection and monitoring

#### Thruster Control & Monitoring
- **ThrusterTemperature** - Temperature monitoring for thrusters with MicroROS integration examples
- **Thruster_normalisation** - Thruster calibration and normalization routines

#### System Monitoring
- **Canister_Monitoring** - Electronics canister environmental monitoring

### 📂 UARTPublisher

UART communication module for:
- Data publishing from ROV to surface station
- Sensor data serialization
- Communication protocol implementation

## ⚙️ Key Features

- Multi-channel current and voltage sensing
- I2C multiplexer support (PCA9548)
- Temperature monitoring for critical components
- Thruster control and calibration
- Modular driver architecture
- UART-based telemetry system
- MicroROS integration ready
- Canister environmental monitoring

## 🔧 Hardware Components

### Electronics
- Arduino Mega (recommended for multiple sensors)
- INA260 current/voltage sensors
- INA3221 triple-channel current sensors
- PCA9548 I2C multiplexer
- Temperature sensors for thrusters
- Resettable fuses for protection
- UART communication hardware

### ROV Components
- Thrusters (for propulsion)
- Electronics canister (waterproof)
- Power distribution system
- Sensors and monitoring systems
- Communication tether or wireless link

## 📌 Common Configurations

### I2C Addresses
```
PCA9548 Multiplexer: 0x72 (configurable via A0-A2 pins, default may be 0x70)
INA260 Sensors: 0x40, 0x44, 0x45 (configurable)
Note: Actual addresses depend on hardware configuration
(Check individual driver READMEs for specific addresses)
```

### Communication
- UART baud rates vary by module (typically 9600-115200)
- I2C standard mode (100kHz) or fast mode (400kHz)

## 🚀 Getting Started

### Basic Setup Steps:

1. **Install Required Libraries:**
   ```
   - INA260 library
   - INA3221 library
   - Wire library (built-in)
   - MicroROS (optional, for ROS integration)
   ```

2. **Hardware Assembly:**
   - Connect sensors via I2C bus
   - Set up I2C multiplexer if using multiple devices with same address
   - Connect thrusters to appropriate controllers
   - Wire power monitoring sensors
   - Set up UART communication

3. **Individual Module Setup:**
   - Navigate to specific driver folder
   - Follow module-specific instructions
   - Test each module independently before integration

4. **System Integration:**
   - Combine tested modules
   - Configure communication protocols
   - Test complete system operation

## 📊 Typical Applications

- **Underwater Inspection**: Pool, tank, or marine inspection
- **Research**: Marine biology and oceanography
- **Education**: Robotics and marine engineering education
- **Competition**: Underwater robotics competitions (MATE ROV, etc.)
- **Monitoring**: Infrastructure inspection and environmental monitoring

## 🔄 Driver Module Structure

Each driver typically includes:
- Initialization and setup routines
- Sensor reading functions
- Data processing and filtering
- Communication/publishing functions
- Example code and usage demonstrations

## 📈 System Architecture

```
┌─────────────────────────────────────┐
│         Arduino Mega                 │
│  (Main Controller)                   │
├─────────────────────────────────────┤
│                                      │
│  ┌──────────────┐  ┌─────────────┐ │
│  │ Power        │  │  Thruster   │ │
│  │ Monitoring   │  │  Control    │ │
│  │ (INA260/321) │  │             │ │
│  └──────────────┘  └─────────────┘ │
│                                      │
│  ┌──────────────┐  ┌─────────────┐ │
│  │ Temperature  │  │  Canister   │ │
│  │ Monitoring   │  │  Monitor    │ │
│  └──────────────┘  └─────────────┘ │
│                                      │
└────────┬─────────────────────┬──────┘
         │                     │
    ┌────▼─────┐         ┌────▼────┐
    │  UART    │         │   I2C   │
    │  Comm    │         │   Bus   │
    └──────────┘         └─────────┘
```

## ⚠️ Important Safety Notes

**Underwater Operations:**
- Ensure proper waterproofing of electronics canister
- Test in shallow water before deep deployment
- Have emergency retrieval plan
- Monitor battery levels continuously

**Electrical Safety:**
- Use appropriate fuses and protection circuits
- Monitor current draw to prevent overcurrent
- Implement emergency shutdown systems
- Follow proper grounding procedures

**Testing:**
- Always test in controlled environment first
- Verify all sensors before submersion
- Check communication reliability
- Test emergency procedures

## 🔮 Future Enhancements

- [ ] Add camera integration
- [ ] Implement depth sensor monitoring
- [ ] Add IMU for orientation tracking
- [ ] Integrate sonar sensors
- [ ] Implement autonomous navigation
- [ ] Add mission recording/replay
- [ ] Develop GUI control interface
- [ ] Add wireless communication option
- [ ] Implement battery management system
- [ ] Add LED lighting control

## 🛠️ Troubleshooting

**I2C Communication Issues:**
- Check wiring and connections
- Verify I2C addresses
- Test multiplexer channels
- Add pull-up resistors if needed
- Check for address conflicts

**Sensor Reading Errors:**
- Verify power supply
- Check sensor initialization
- Monitor serial output for errors
- Test individual sensors separately

**UART Communication Problems:**
- Verify baud rate settings
- Check TX/RX connections
- Test with loopback
- Monitor for data corruption

## 📚 Resources

- INA260 Datasheet: High-precision current/voltage/power monitor
- INA3221 Datasheet: Triple-channel current monitor
- PCA9548 Datasheet: 8-channel I2C multiplexer
- MicroROS Documentation: ROS 2 for microcontrollers
- ROV Design Guides: MATE ROV competition resources

## 🎓 Learning Outcomes

Working with this project teaches:
- Underwater robotics principles
- Multi-sensor integration
- I2C communication and multiplexing
- Power management and monitoring
- Thruster control systems
- UART communication protocols
- System integration techniques
- Safety-critical systems design

## 🤝 Contributing

Contributions are welcome! Areas for contribution:
- New sensor drivers
- Improved control algorithms
- Better documentation
- Testing and bug reports
- Performance optimizations

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*

**Note**: Refer to individual driver folders for specific implementation details, wiring diagrams, and usage examples.
