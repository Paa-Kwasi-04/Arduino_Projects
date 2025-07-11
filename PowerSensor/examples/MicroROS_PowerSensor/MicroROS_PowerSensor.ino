/**
 * @file PowerSensorNode.ino
 * @brief Micro-ROS node for publishing thruster power data
 */

#include <micro_ros_arduino.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/float32_multi_array.h>
#include "PowerSensor.h"

// Configuration
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}
constexpr uint8_t NUM_THRUSTERS = 4;  // Can be expanded
constexpr unsigned long PUBLISH_INTERVAL_MS = 500;  // 2Hz update rate

// Sensor addresses (0x40, 0x41, 0x44, 0x45)
const uint8_t sensorAddresses[NUM_THRUSTERS] = {0x40, 0x41, 0x44, 0x45};

// ROS entities
rcl_publisher_t power_publisher;
rcl_publisher_t current_publisher;
rcl_publisher_t voltage_publisher;
std_msgs__msg__Float32MultiArray power_msg;
std_msgs__msg__Float32MultiArray current_msg;
std_msgs__msg__Float32MultiArray voltage_msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
rclc_executor_t executor;

// Sensor instance
PowerSensor powerSensor;

void error_loop() {
  while(1) {
    delay(100);
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
  (void) last_call_time;
  if (timer != NULL) {
    // Read all sensor data
    float power[NUM_THRUSTERS];
    float current[NUM_THRUSTERS];
    float voltage[NUM_THRUSTERS];
    
    powerSensor.readPower(power);
    powerSensor.readCurrent(current);
    powerSensor.readLoadVoltage(voltage);
    
    // Copy data to messages
    for (uint8_t i = 0; i < NUM_THRUSTERS; i++) {
      power_msg.data.data[i] = power[i];
      current_msg.data.data[i] = current[i];
      voltage_msg.data.data[i] = voltage[i];
    }
    
    // Publish all data
    RCSOFTCHECK(rcl_publish(&power_publisher, &power_msg, NULL));
    RCSOFTCHECK(rcl_publish(&current_publisher, &current_msg, NULL));
    RCSOFTCHECK(rcl_publish(&voltage_publisher, &voltage_msg, NULL));
    
    // Debug output
    Serial.println("Published power data:");
    for (uint8_t i = 0; i < NUM_THRUSTERS; i++) {
      Serial.print("Thruster ");
      Serial.print(i+1);
      Serial.print(" - P: ");
      Serial.print(power[i], 2);
      Serial.print(" W, I: ");
      Serial.print(current[i], 2);
      Serial.print(" A, V: ");
      Serial.print(voltage[i], 2);
      Serial.println(" V");
    }
    Serial.println("-------------------");
  }
}

void setup() {
  // Initialize serial
  Serial.begin(9600);
  while (!Serial);  // Wait for serial console

  // Initialize power sensors
  if (!powerSensor.begin(sensorAddresses, NUM_THRUSTERS)) {
    Serial.println("Failed to initialize power sensors!");
    while(1);
  }

  // Set up Micro-ROS transport
  set_microros_transports();
  delay(2000);  // Wait for agent

  // Initialize allocator
  allocator = rcl_get_default_allocator();

  // Create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // Create node
  RCCHECK(rclc_node_init_default(&node, "PowerSensorNode", "", &support));

  // Initialize message memory for all arrays
  power_msg.data.data = (float*)malloc(sizeof(float) * NUM_THRUSTERS);
  power_msg.data.size = NUM_THRUSTERS;
  power_msg.data.capacity = NUM_THRUSTERS;
  
  current_msg.data.data = (float*)malloc(sizeof(float) * NUM_THRUSTERS);
  current_msg.data.size = NUM_THRUSTERS;
  current_msg.data.capacity = NUM_THRUSTERS;
  
  voltage_msg.data.data = (float*)malloc(sizeof(float) * NUM_THRUSTERS);
  voltage_msg.data.size = NUM_THRUSTERS;
  voltage_msg.data.capacity = NUM_THRUSTERS;

  // Create publishers
  RCCHECK(rclc_publisher_init_default(
    &power_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
    "/reconrobot/thruster/power"));

  RCCHECK(rclc_publisher_init_default(
    &current_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
    "/reconrobot/thruster/current"));

  RCCHECK(rclc_publisher_init_default(
    &voltage_publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
    "/reconrobot/thruster/voltage"));

  // Create timer (500ms)
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(PUBLISH_INTERVAL_MS),
    timer_callback));

  // Create executor
  executor = rclc_executor_get_zero_initialized_executor();
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  Serial.println("PowerSensorNode Ready");
}

void loop() {
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  delay(10);
}