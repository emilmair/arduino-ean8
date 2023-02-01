#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/processing.h"

uint8_t get_bit (uint8_t* buffer, uint32_t byte, uint8_t bit) {
    uint8_t data_byte = buffer[byte] >> bit;
    return data_byte & 1;
}

void set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value) {
    uint8_t mask = 1 << bit;
    if (!value && get_bit(buffer, byte, bit)) buffer[byte] &= ~mask;
    if (value && !get_bit(buffer, byte, bit)) buffer[byte] |= mask;
}

void fill_bits_without_data(uint8_t* buffer, uint32_t bytes, uint32_t bits, uint8_t value) {
    for (uint32_t i = bits; i < bytes*8; i++) {
        SET_BIT(buffer, i, value);
    }
}

uint32_t remove_trailing_bits(uint8_t* buffer, uint32_t bytes, uint8_t value) {
    for (uint32_t i = bytes*8-1; i > 0; i--) {
        if (GET_BIT(buffer, i) != value) {
            return i+1;
        }
    }
    return 0;
}

uint8_t* process_buffer(uint8_t* cleaned_buffer, uint32_t length_in_bits) {
    uint8_t* processed_buffer = (uint8_t*) malloc(9);
    memset(processed_buffer, 0, 9);
    for (uint32_t i = 0; i < BITS; i++) {
        uint32_t bit = ((length_in_bits/(float)BITS)/2.0) + ((length_in_bits/(float)BITS)*i);
        SET_BIT(processed_buffer, i, GET_BIT(cleaned_buffer, bit));
    }
    return processed_buffer;
}

uint8_t indexmap(uint8_t index) {
    switch (index) {
        case 0:
            return 0;
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 5;
        case 4:
            return 6;
        case 5:
            return 7;
        case 6:
            return 8;
        case 7:
            return 9;
        case 8:
            return 0;
        case 9:
            return 10;
        case 10:
            return 11;
        case 11:
            return 12;
        case 12:
            return 13;
        case 13:
            return 14;
        case 14:
            return 15;
        case 15:
            return 16;
        case 16:
            return 0;
        case 17:
            return 17;
        case 18:
            return 18;
        case 19:
            return 19;
        case 20:
            return 20;
        case 21:
            return 21;
        case 22:
            return 22;
        case 23:
            return 23;
        case 24:
            return 0;
        case 25:
            return 24;
        case 26:
            return 25;
        case 27:
            return 26;
        case 28:
            return 27;
        case 29:
            return 28;
        case 30:
            return 29;
        case 31:
            return 30;
        case 32:
            return 0;
        case 33:
            return 36;
        case 34:
            return 37;
        case 35:
            return 38;
        case 36:
            return 39;
        case 37:
            return 40;
        case 38:
            return 41;
        case 39:
            return 42;
        case 40:
            return 0;
        case 41:
            return 43;
        case 42:
            return 44;
        case 43:
            return 45;
        case 44:
            return 46;
        case 45:
            return 47;
        case 46:
            return 48;
        case 47:
            return 49;
        case 48:
            return 0;
        case 49:
            return 50;
        case 50:
            return 51;
        case 51:
            return 52;
        case 52:
            return 53;
        case 53:
            return 54;
        case 54:
            return 55;
        case 55:
            return 56;
        case 56:
            return 0;
        case 57:
            return 57;
        case 58:
            return 58;
        case 59:
            return 59;
        case 60:
            return 60;
        case 61:
            return 61;
        case 62:
            return 62;
        case 63:
            return 63;
    }
    return 0;
}

uint8_t* compress_ean8(uint8_t* processed_buffer) {
    uint8_t* compressed_buffer = (uint8_t*) malloc(8);
    memset(compressed_buffer, 0, 8);
    for (uint32_t i = 0; i < 64; i++) {
        SET_BIT(compressed_buffer, i, GET_BIT(processed_buffer, indexmap(i)));
    }
    return compressed_buffer;
}

uint8_t ean8map(uint8_t code) {
    switch (code) {
        case 0b1110010:
            return 0;
        case 0b1100110:
            return 1;
        case 0b1100011:
            return 2;
        case 0b1000010:
            return 3;
        case 0b1011100:
            return 4;
        case 0b1001110:
            return 5;
        case 0b1010000:
            return 6;
        case 0b1000100:
            return 7;
        case 0b1001000:
            return 8;
        case 0b1110100:
            return 9;
        case 0b0001101:
            return 0;
        case 0b0011001:
            return 1;
        case 0b0010011:
            return 2;
        case 0b0111101:
            return 3;
        case 0b0100011:
            return 4;
        case 0b0110001:
            return 5;
        case 0b0101111:
            return 6;
        case 0b0111011:
            return 7;
        case 0b0110111:
            return 8;
        case 0b0001011:
            return 9;
    }
    return 122;
}

const char* validate_ean8(uint8_t* compressed_buffer) {
    return "probably not so good idk\n";
}
