#include "DcResettableFuse.h"

// Constructor for the DcResettableFuse class
DcResettableFuse::DcResettableFuse()
    : _shiftLoadPin(0), _clockPin(0), _dataOutPin(0), _numRegisters(1) {}

/**
 * Initializes the shift register interface used to read fuse states.
 *
 * @param shiftLoadPin   The pin connected to the shift/load (S/L) pin of the shift register.
 * @param clockPin       The pin connected to the clock (CLK) pin of the shift register.
 * @param dataOutPin     The pin connected to the serial data output (DO) pin of the shift register.
 * @param numRegisters   The number of 8-bit shift registers in the chain (max: MAX_SHIFT_REGISTERS).
 * @return true on successful initialization.
 */
bool DcResettableFuse::begin(uint8_t numRegisters) {
    _shiftLoadPin = SHIFT_LOAD_PIN;
    _clockPin = CLOCK_PIN;
    _dataOutPin = DATA_OUT_PIN;

    // Clamp number of registers to max allowed
    _numRegisters = (numRegisters <= MAX_SHIFT_REGISTERS) ? numRegisters : MAX_SHIFT_REGISTERS;

    // Configure pin modes
    pinMode(_shiftLoadPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataOutPin, INPUT);

    // Set initial logic levels
    digitalWrite(_shiftLoadPin, HIGH); // Idle state for shift/load
    digitalWrite(_clockPin, LOW);      // Idle low for clock
    return true;
}

/**
 * Reads all fuse states from the shift registers and stores them in the provided boolean array.
 *
 * @param fuseStates  A boolean array to store the state (true = tripped, false = normal) of each fuse.
 * @return The total number of fuses read (equal to number of registers * 8).
 */
uint8_t DcResettableFuse::readAllStates(bool fuseStates[]) {
    // Load the current fuse states into the shift register outputs
    digitalWrite(_shiftLoadPin, LOW);
    delayMicroseconds(5);               // Ensure latch time is met
    digitalWrite(_shiftLoadPin, HIGH);  // Capture the fuse states

    uint8_t totalFuses = _numRegisters * FUSES_PER_REGISTER;

    // Iterate over each shift register
    for (uint8_t reg = 0; reg < _numRegisters; reg++) {
        uint8_t value = 0;

        // Read 8 bits from the shift register serially
        for (int i = 0; i < 8; i++) {
            digitalWrite(_clockPin, HIGH);
            delayMicroseconds(5);                     // Pulse clock high          // Read bit and store in proper position
            fuseStates[reg * 8 + i] = digitalRead(_dataOutPin); // Store directly in fuseStates array
            delayMicroseconds(5);                     // Pulse clock low
            digitalWrite(_clockPin, LOW);
        }
    }

    return totalFuses;
}
