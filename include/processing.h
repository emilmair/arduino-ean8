#ifndef ARDUINO_EAN8_PROCESSING_H
#define ARDUINO_EAN8_PROCESSING_H

#include <stdint.h>
#include <stdio.h>

#define BITS 67
#define WHITE 1
#define BLACK 0
#define GET_BIT(BUFFER, B) get_bit((BUFFER), (B)/8, 7-(B-(((B)/8)*8)))
#define SET_BIT(BUFFER, B, V) set_bit((BUFFER), (B)/8, 7-(B-(((B)/8)*8)), (V))
#ifndef UPLOAD
#define MSG(S) printf(S)
#define MSGC(C) printf("%c", (C))
#define PRINT(BUFFER, SIZE) printf("(%i) [0: ", SIZE); for (uint32_t I = 0; I < (SIZE); I++) { printf("%i", GET_BIT(BUFFER, I)); if (I % 8 == 7 && I < SIZE-1) {printf("] [%i: ", I/8+1);}} printf("]\n")
#endif

/// set bit at buffer[byte] to value.
void set_bit(uint8_t* buffer, uint32_t byte, uint8_t bit, uint8_t value);

/// retrieve bit at buffer[byte].
uint8_t get_bit(uint8_t* buffer, uint32_t byte, uint8_t bit);

/// fill the last bytes*8-bits bits with datapoints of a certain value
void fill_bits_without_data(uint8_t* buffer, uint32_t bytes, uint32_t bits, uint8_t value);

/// get remaining number of bits if trailing datapoints equaling a certain value were removed.
uint32_t remove_trailing_bits(uint8_t* buffer, uint32_t bytes, uint8_t value);

/// process datapoints into new buffer of size 9 (67 bits), where every ean8 bit takes up a real bit in memory.
uint8_t* process_buffer(uint8_t* cleaned_buffer, uint32_t length_in_bits);

/// process bits into an array of 8 bytes, the least significant 7 bits of each byte representing one digit. assert that the code is valid.
uint8_t* compress_ean8(uint8_t* processed_buffer);

/// returns null-terminated char array of what is wrong with your data
const char* validate_ean8(uint8_t* compressed_buffer);

/// returns ean8 digit from least significant 7 bits
uint8_t ean8map(uint8_t code);

#endif //ARDUINO_EAN8_PROCESSING_H
