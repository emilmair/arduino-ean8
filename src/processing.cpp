#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include "../include/processing.h"

 void set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value) {
    uint8_t shifted_bit = value << bit++;
    buffer[byte] |= shifted_bit;
}

uint8_t get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit) {
    uint8_t data_byte = buffer[byte] >> bit;
    return data_byte & 1;
}

void fill_bits_without_data(uint8_t* buffer, uint32_t bytes, uint32_t bits, uint8_t value) {
    for (int i = bits; i < bytes*8; i++) {
        SET_BIT(buffer, i, value);
    }
}


uint32_t remove_trailing_bits(uint8_t* buffer, uint32_t bytes, uint8_t value) {
    for (int i = bytes*8-1; i > 0; i--) {
        if (GET_BIT(buffer, i) != value) {
            return i+1;
        }
    }
    return 0;
}

uint8_t* process_buffer(uint8_t* cleaned_buffer, uint32_t length_in_bits) {
    uint8_t* processed_buffer = (uint8_t*) malloc(9);
    memset(processed_buffer, 0, 9);
    for (int i = 0; i < BITS; i++) {
        uint32_t bit = ((length_in_bits/(float)BITS)/2.0) + ((length_in_bits/(float)BITS)*i);
        SET_BIT(processed_buffer, i, GET_BIT(cleaned_buffer, bit));
    }
    return processed_buffer;
}

uint8_t* validate_ean8(uint8_t* processed_buffer) {
    uint8_t* validated_buffer = (uint8_t*) malloc(42);

    // TODO

    return validated_buffer;
}

uint16_t decode_ean8(uint8_t* ean8_code) {
    uint16_t digit = 42;

    // TODO

    return digit;
}

