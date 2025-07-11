// test_PowerSensor.cpp

#include <Arduino.h>
#include <unity.h>
#include "PowerSensor.h"

// ---- Mock Classes ----
class MockWireClass {
public:
    int beginTransmission(uint8_t addr) { lastAddr = addr; return 0; }
    int write(uint8_t val) { lastWrite = val; return 1; }
    int endTransmission() { callCount++; return mockResult; }
    void setMockResult(int result) { mockResult = result; }
    void reset() { callCount = 0; }
    uint8_t lastAddr = 0;
    uint8_t lastWrite = 0;
    int callCount = 0;
    int mockResult = 0;
};
MockWireClass MockWire;

class MockSerialClass {
public:
    void print(float val, int prec = 2) { lastPrint = val; printCount++; }
    void print(const char* str) {}
    void println(const char* str) {}
    float lastPrint = 0;
    int printCount = 0;
};
MockSerialClass MockSerial;

class MockINA260 {
public:
    float getPower() { return mockPower; }
    float getCurrent() { return mockCurrent; }
    float getBusVoltage_mV() { return mockBusVoltage; }
    float getShuntVoltage_mV() { return mockShuntVoltage; }
    float mockPower = 1.23f;
    float mockCurrent = 0.45f;
    float mockBusVoltage = 5000.0f;
    float mockShuntVoltage = 10.0f;
};
class MockINA3221 {
public:
    float getPower(int ch) { return 2.34f + ch; }
    float getCurrent(int ch) { return 0.56f + ch; }
    float getBusVoltage_mV(int ch) { return 3300.0f + 100 * ch; }
    float getShuntVoltage_mV(int ch) { return 5.0f * ch; }
};

// ---- Replace global objects ----
#define Wire MockWire
#define Serial MockSerial

// ---- Test Fixture ----
PowerSensor sensor;
MockINA260 mockINA260s[2];
MockINA3221 mockINA3221;

void setUp(void) {
    // Called before each test
    sensor._initialized = true;
    sensor._SensorCount = 12;
    sensor.INA260_sensors = mockINA260s;
    sensor.INA3221_sensor = mockINA3221;
}

void tearDown(void) {
    // Called after each test
}

// ---- Tests ----

void test_begin_detects_sensors(void) {
    MockWire.setMockResult(0); // Simulate device found
    sensor._SensorCount = 0;
    bool result = sensor.begin();
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT(sensor._SensorCount > 0);
}

void test_readPower_returns_values(void) {
    float arr[12] = {0};
    mockINA260s[0].mockPower = 1.0f;
    mockINA260s[1].mockPower = 2.0f;
    int count = sensor.readPower(arr);
    TEST_ASSERT_EQUAL(sensor._SensorCount, count);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0f, arr[0]);
}

void test_readCurrent_returns_values(void) {
    float arr[12] = {0};
    mockINA260s[0].mockCurrent = 0.5f;
    mockINA260s[1].mockCurrent = 1.5f;
    int count = sensor.readCurrent(arr);
    TEST_ASSERT_EQUAL(sensor._SensorCount, count);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5f, arr[0]);
}

void test_readLoadVoltage_returns_values(void) {
    float arr[12] = {0};
    mockINA260s[0].mockBusVoltage = 5000.0f;
    mockINA260s[0].mockShuntVoltage = 10.0f;
    int count = sensor.readLoadVoltage(arr);
    TEST_ASSERT_EQUAL(sensor._SensorCount, count);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 5.01f, arr[0]);
}

void test_readPower_nullptr(void) {
    int count = sensor.readPower(nullptr);
    TEST_ASSERT_EQUAL(0, count);
}

void test_readCurrent_nullptr(void) {
    int count = sensor.readCurrent(nullptr);
    TEST_ASSERT_EQUAL(0, count);
}

void test_readLoadVoltage_nullptr(void) {
    int count = sensor.readLoadVoltage(nullptr);
    TEST_ASSERT_EQUAL(0, count);
}

void test_readPower_uninitialized(void) {
    sensor._initialized = false;
    float arr[12] = {0};
    int count = sensor.readPower(arr);
    TEST_ASSERT_EQUAL(0, count);
}

void test_readPowerHigh_prints(void) {
    MockSerial.printCount = 0;
    sensor.readPowerHigh();
    TEST_ASSERT(MockSerial.printCount > 0);
}

void test_readPowerLow_prints(void) {
    MockSerial.printCount = 0;
    sensor.readPowerLow();
    TEST_ASSERT(MockSerial.printCount > 0);
}

// ---- Main ----
void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_begin_detects_sensors);
    RUN_TEST(test_readPower_returns_values);
    RUN_TEST(test_readCurrent_returns_values);
    RUN_TEST(test_readLoadVoltage_returns_values);
    RUN_TEST(test_readPower_nullptr);
    RUN_TEST(test_readCurrent_nullptr);
    RUN_TEST(test_readLoadVoltage_nullptr);
    RUN_TEST(test_readPower_uninitialized);
    RUN_TEST(test_readPowerHigh_prints);
    RUN_TEST(test_readPowerLow_prints);
    UNITY_END();
}

void loop() {}