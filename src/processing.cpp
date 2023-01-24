#include <cstdlib>

#include "../include/processing.h"

static void set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value) {
    uint8_t shifted_bit = value << bit++;
    buffer[byte] |= shifted_bit;
}

static uint8_t get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit) {
    uint8_t data_byte = buffer[byte] >> bit;
    return data_byte & 1;
}

static void remove_trailing_bits(uint8_t* buffer, uint32_t* length_in_bits, uint8_t value) {
    for (int byte = *length_in_bits/8; byte > 0; byte--) {
        for (int bit = 7; bit > 0; bit--) {
            if (get_bit(buffer, byte, bit) != value) {
                *length_in_bits = byte*8 + bit;
                buffer = (uint8_t*) realloc(buffer, *length_in_bits/8 + 1);
                break;
            }
        }
    }
}

static uint8_t* process_buffer(uint8_t* cleaned_buffer, uint32_t* length_in_bits) {
    uint8_t* processed_buffer = (uint8_t*) malloc(42);

    // TODO

    return processed_buffer;
}

static uint8_t* validate_ean8(uint8_t processed_buffer) {
    uint8_t* validated_buffer = (uint8_t*) malloc(42);

    // TODO

    return validated_buffer;
}

static uint16_t decode_ean8(uint8_t* ean8_code) {
    uint16_t digit = 42;

    // TODO

    return digit;
}

