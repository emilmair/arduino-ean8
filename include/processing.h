#ifndef ARDUINO_EAN8_PROCESSING_H
#define ARDUINO_EAN8_PROCESSING_H
#include <cstdint>

/// set bit at buffer[byte] to value.
static void set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value);

/// retrieve bit at buffer[byte].
static uint8_t get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit);

/// remove trailing datapoints equaling a certain value from buffer.
static void remove_trailing_bits(uint8_t* buffer, uint32_t* length_in_bits, uint8_t value);

/// process datapoints into new buffer of size 9 (67 bits), where every ean8 bit takes up a real bit in memory.
static uint8_t* process_buffer(uint8_t* cleaned_buffer, uint32_t* length_in_bits);

/// process bits into an array of 8 bytes, the least significant 7 bits of each byte representing one digit. assert that the code is valid.
static uint8_t* validate_ean8(uint8_t processed_buffer);

/// decode 4 bytes, the least significant 7 bits of each byte containing an ean8 digit, into one integer.
static uint16_t decode_ean8(uint8_t* ean8_code);

#endif //ARDUINO_EAN8_PROCESSING_H
