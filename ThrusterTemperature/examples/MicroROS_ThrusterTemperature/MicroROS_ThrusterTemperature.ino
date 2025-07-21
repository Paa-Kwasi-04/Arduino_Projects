/**
 * @file ThrusterTemperature.ino
 * @brief Micro-ROS Thruster Temperature Publisher
 * @details Publishes 8 thruster temperatures as Float32MultiArray
 */

#include <micro_ros_arduino.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/float32_multi_array.h>
#include "ThrusterTemperature.h"

// CS pins for 8 thrusters (0,1,2,3,4,5,9,10)
const uint8_t cs_pins[] = {0, 1, 2, 3, 4, 5, 9, 10};
const uint8_t sensorCount = sizeof(cs_pins)/sizeof(cs_pins[0]);

// Micro-ROS configuration
#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// ROS entities
ThrusterTemperature tempSensors;
rcl_publisher_t publisher;
std_msgs__msg__Float32MultiArray temp_msg;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;
rclc_executor_t executor;

void error_loop() {
  while(1) {
    delay(100);
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time) {
  (void) last_call_time;
  if (timer != NULL) {
    float temperatures[sensorCount];
    tempSensors.readAllTemperatures(temperatures);
    
    // Copy temperatures to message
    for (uint8_t i = 0; i < sensorCount; i++) {
      temp_msg.data.data[i] = temperatures[i];
    }
    
    RCSOFTCHECK(rcl_publish(&publisher, &temp_msg, NULL));
    
    // Debug output
    Serial.println("Published temperatures:");
    for (uint8_t i = 0; i < sensorCount; i++) {
      Serial.print("Thruster ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(temp_msg.data.data[i], 1);
      Serial.println("°C");
    }
    Serial.println("-------------------------------");
  }
}

void setup() {
  // Initialize serial
  Serial.begin(9600);
  while (!Serial);  // Wait for serial console

  // Initialize temperature sensors
  if (!tempSensors.begin(cs_pins, sensorCount)) {
    Serial.println(F("Sensor initialization failed!"));
    while (1);
  }
  tempSensors.setThresholds(30.0, 70.0);
  
  // Set up Micro-ROS transport
  set_microros_transports();
  delay(2000);  // Wait for agent

  // Initialize Micro-ROS
  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
  RCCHECK(rclc_node_init_default(&node, "ThrusterTemperatureNode", "", &support));

  // Initialize message memory
  temp_msg.data.data = (float*)malloc(sizeof(float) * sensorCount);
  temp_msg.data.size = sensorCount;
  temp_msg.data.capacity = sensorCount;

  // Create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
    "/reconrobot/thruster/temperature"));

  // Create timer (500ms)
  RCCHECK(rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(500),
    timer_callback));

  // Create executor
  executor = rclc_executor_get_zero_initialized_executor();
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  Serial.println(F("ThrusterTemperatureNode Ready"));
  Serial.println(F("-------------------------------"));
}

void loop() {
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  delay(10);
}