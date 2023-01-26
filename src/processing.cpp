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
    uint8_t* validated_buffer = (uint8_t*) malloc(8);
    const uint8_t bits[64] = {0, 3, 4, 5, 6, 7, 8, 9 , 0,10, 11, 12, 13, 14, 15, 16, 0, 17, 18,19, 20, 21, 22, 23, 0, 24, 25, 26, 27, 28, 29, 30,
                      0, 36, 37, 38, 39, 40, 41, 42, 0, 43, 44, 45, 46, 47, 48, 49, 0, 50, 51, 52, 53, 54, 55, 56, 0, 57, 58, 59, 60, 61, 62, 63};
    for (int i = 0; i < 64; i++) {
        SET_BIT(validated_buffer, i, GET_BIT(processed_buffer, bits[i]));
    }
    return validated_buffer;
}

uint16_t decode_ean8(uint8_t* ean8_code) {
    uint8_t* fake_map = (uint8_t*) malloc(127);

    // A set
    fake_map[0b01110010] = 0;
    fake_map[0b01100110] = 1;
    fake_map[0b01100011] = 2;
    fake_map[0b01000010] = 3;
    fake_map[0b01011100] = 4;
    fake_map[0b01001110] = 5;
    fake_map[0b01010000] = 6;
    fake_map[0b01000100] = 7;
    fake_map[0b01001000] = 8;
    fake_map[0b01110100] = 9;

    // C set
    fake_map[0b00001101] = 0;
    fake_map[0b00011001] = 1;
    fake_map[0b00010011] = 2;
    fake_map[0b00111101] = 3;
    fake_map[0b00100011] = 4;
    fake_map[0b00110001] = 5;
    fake_map[0b00101111] = 6;
    fake_map[0b00111011] = 7;
    fake_map[0b00110111] = 8;
    fake_map[0b00001011] = 9;

    uint16_t digit = 0;
    digit += fake_map[ean8_code[0]] * 1000;
    digit += fake_map[ean8_code[1]] * 100;
    digit += fake_map[ean8_code[2]] * 10;
    digit += fake_map[ean8_code[3]];

        return digit;
}

