
#ifndef DC_RESETTABLE_FUSE_H
#define DC_RESETTABLE_FUSE_H

#include <Arduino.h>

#define MAX_SHIFT_REGISTERS 8  // Adjust if needed
#define FUSES_PER_REGISTER 8
#define MAX_FUSES (MAX_SHIFT_REGISTERS * FUSES_PER_REGISTER)
#define SHIFT_LOAD_PIN  26
#define CLOCK_PIN       27
#define DATA_OUT_PIN    25

class DcResettableFuse {
public:
    DcResettableFuse();

    /**
     * @brief Initialize the resettable fuse(s)
     * @param shiftLoadPin Pin to load the fuse states into the shift registers (S/L)
     * @param clockPin Pin to clock data out (CLK)
     * @param dataOutPin Pin to read serial data from the last module's DO pin
     * @param numRegisters Number of daisy-chained shift registers (modules)
     * @return true if initialization succeeded, false otherwise
     */
    bool begin(uint8_t numRegisters = 1);

    /**
     * @brief Reads the fuse states as a boolean array
     * @param fuseStates Pre-allocated boolean array where results will be stored
     * @return The number of fuses read (numRegisters * 8)
     */
    uint8_t readAllStates(bool fuseStates[]);

private:
    uint8_t _shiftLoadPin;
    uint8_t _clockPin;
    uint8_t _dataOutPin;
    uint8_t _numRegisters;
};

#endif  // DC_RESETTABLE_FUSE_H
