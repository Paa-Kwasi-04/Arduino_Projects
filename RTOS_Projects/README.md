# RTOS Projects - FreeRTOS on Arduino

Real-Time Operating System (RTOS) projects demonstrating multitasking, task scheduling, and concurrent operations on Arduino using FreeRTOS.

## 📝 Project Description

This collection showcases the implementation of FreeRTOS (Free Real-Time Operating System) on Arduino platforms. FreeRTOS enables true multitasking on microcontrollers, allowing multiple tasks to run concurrently with deterministic timing.

## 🎯 Purpose

Learn and implement:
- **Multitasking**: Run multiple tasks simultaneously
- **Task Scheduling**: Priority-based task execution
- **Real-Time Performance**: Deterministic timing guarantees
- **Resource Management**: Efficient CPU utilization
- **Concurrent Programming**: Parallel task execution

## 📂 Projects

### Dual_Task_Blink_Scheduler

A fundamental RTOS example demonstrating:
- Two independent LED blinking tasks running concurrently
- Different task priorities and timing
- FreeRTOS task creation and management
- Task delays using FreeRTOS timing functions

**Features:**
- Red LED blinks at 500ms interval (1Hz)
- Green LED blinks at 200ms interval (2.5Hz)
- Tasks run independently with different priorities
- Non-blocking concurrent execution

## ⚙️ Key Concepts

### FreeRTOS Basics

**Task Creation:**
```cpp
xTaskCreate(
    TaskFunction,    // Function implementing the task
    "TaskName",      // Task name for debugging
    StackDepth,      // Stack size in words
    Parameters,      // Parameters to pass to task
    Priority,        // Task priority (0 = lowest)
    TaskHandle       // Handle to created task
);
```

**Task Scheduling:**
- Preemptive scheduling based on priority
- Higher priority tasks run first
- Equal priority tasks use round-robin
- Scheduler started with `vTaskStartScheduler()`

**Task Delays:**
```cpp
vTaskDelay(pdMS_TO_TICKS(milliseconds));
```
- Non-blocking delay
- Yields CPU to other tasks
- Precise timing using system ticks

## 🔧 Hardware Requirements

- Arduino board with FreeRTOS support:
  - Arduino Uno
  - Arduino Mega
  - Arduino Nano
  - ESP32 (native FreeRTOS support)
- LEDs (for demonstration projects)
- Resistors (220Ω for LEDs)
- Breadboard and jumper wires

## 📚 Required Library

**Arduino_FreeRTOS Library**

Installation:
1. Open Arduino IDE
2. Go to Sketch → Include Library → Manage Libraries
3. Search for "FreeRTOS"
4. Install "FreeRTOS" by Richard Barry

**Note**: ESP32 boards have native FreeRTOS support built-in.

## 🚀 Getting Started

### Basic FreeRTOS Structure:

```cpp
#include <Arduino_FreeRTOS.h>

// Task function prototypes
void Task1(void *parameters);
void Task2(void *parameters);

void setup() {
    // Initialize hardware
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    
    // Create tasks
    xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 128, NULL, 2, NULL);
    
    // Start scheduler (never returns)
    vTaskStartScheduler();
}

void loop() {
    // Empty - not used with FreeRTOS
}

void Task1(void *parameters) {
    while(1) {
        // Task code here
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```

## 📊 FreeRTOS Features

### Task Management
- Create and delete tasks dynamically
- Suspend and resume tasks
- Change task priorities
- Query task states

### Timing & Delays
- Precise tick-based timing
- Non-blocking delays
- Absolute time delays
- Periodic task execution

### Synchronization
- Semaphores (binary, counting)
- Mutexes for resource protection
- Event groups
- Task notifications

### Communication
- Queues for inter-task messaging
- Stream buffers
- Message buffers

## 🎓 RTOS Advantages

**Why use an RTOS?**

1. **True Multitasking**: Multiple tasks run independently
2. **Deterministic Timing**: Guaranteed response times
3. **Priority Management**: Critical tasks get CPU first
4. **Modularity**: Separate concerns into isolated tasks
5. **Resource Efficiency**: Better CPU utilization
6. **Scalability**: Easy to add new tasks

**vs. Traditional Arduino Programming:**
- No more `delay()` blocking entire program
- No complex `millis()` timing logic
- No state machines for pseudo-multitasking
- Better code organization

## 📈 Performance Considerations

### Stack Size
```cpp
xTaskCreate(..., StackSize, ...);
```
- Specified in words (not bytes)
- Too small = stack overflow
- Too large = wasted RAM
- Use 128-256 words for simple tasks
- Monitor with `uxTaskGetStackHighWaterMark()`

### Priority Levels
```cpp
Priority:
0 = Idle task (lowest)
1 = Low priority
2 = Medium priority
3+ = High priority
```
- Use priorities wisely
- Avoid priority inversion
- Critical tasks get higher priority

### Tick Rate
- Default: 1000 Hz (1ms tick)
- Configurable in FreeRTOSConfig.h
- Affects timing precision and overhead

## 🔄 Common RTOS Patterns

### Periodic Tasks
```cpp
void PeriodicTask(void *parameters) {
    TickType_t lastWakeTime = xTaskGetTickCount();
    const TickType_t period = pdMS_TO_TICKS(100);
    
    while(1) {
        // Task work
        vTaskDelayUntil(&lastWakeTime, period);
    }
}
```

### Event-Driven Tasks
```cpp
void EventTask(void *parameters) {
    while(1) {
        if(eventOccurred) {
            // Handle event
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
```

## ⚠️ Important Notes

**Memory Limitations:**
- Arduino Uno: Limited RAM (2KB)
- Each task needs stack space
- Monitor heap and stack usage
- Start with few, simple tasks

**Watchdog Timer:**
- May need to disable or feed in tasks
- RTOS idle task can handle this
- Configure based on timing requirements

**Interrupts:**
- ISRs must be short
- Use FreeRTOS "FromISR" functions in ISRs (e.g., xQueueSendFromISR, xSemaphoreGiveFromISR)
- Post to queues rather than processing in ISR

**Debugging:**
- Use Serial output carefully (not thread-safe)
- Consider using semaphores for Serial
- Monitor task states
- Watch for stack overflow

## 🔮 Project Extensions

Future RTOS projects could include:

- **Mutex Example**: Protecting shared resources
- **Queue Communication**: Inter-task messaging
- **Semaphore Synchronization**: Task coordination
- **Software Timers**: Callback-based timing
- **Priority Inversion**: Demonstration and solution
- **Multi-Sensor System**: RTOS-based data acquisition
- **Motor Control**: Concurrent motor management
- **Communication System**: RTOS-based serial/wireless

## 🛠️ Troubleshooting

**Task not running:**
- Check priority settings
- Verify stack size is adequate
- Ensure scheduler is started
- Check for blocking calls

**System crashes:**
- Stack overflow most common
- Increase stack size
- Check for infinite loops without delays
- Monitor memory usage

**Timing issues:**
- Use `vTaskDelayUntil` for periodic tasks
- Don't use `delay()` - use `vTaskDelay()`
- Check tick rate configuration
- Avoid long-running task sections

**Serial output garbled:**
- Protect Serial with mutex
- Use task notifications
- Keep Serial in one task
- Check baud rate settings

## 📚 Learning Resources

- FreeRTOS Official Documentation
- FreeRTOS Tutorial Books
- Arduino FreeRTOS Library Examples
- Real-Time Systems Theory
- Mastering the FreeRTOS Real Time Kernel (free book)

## 🎯 Learning Path

1. **Start**: Dual_Task_Blink_Scheduler (current project)
2. **Next**: Task communication with queues
3. **Then**: Resource protection with mutexes
4. **Advanced**: Complex multi-task systems
5. **Expert**: Real-time control systems

## 📐 Best Practices

- Keep tasks simple and focused
- Use appropriate delays (yield CPU)
- Protect shared resources
- Monitor stack usage
- Use meaningful task names
- Document task priorities
- Test thoroughly under load
- Plan task interactions carefully

---

*Part of Arduino_Projects repository by Paa-Kwasi-04*

**Ready to learn real-time systems? Start with Dual_Task_Blink_Scheduler!**
