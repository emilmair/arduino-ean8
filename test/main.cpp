#define DATA {7, 193, 240, 124, 0, 0, 62, 0, 127, 255, 7, 192, 15, 128, 0, 248, 0, 0, 124, 31, 7, 193, 240, 127, 255, 248, 62, 0, 124, 0, 255, 193, 255, 128, 0, 248, 62, 0, 3, 255, 7, 193, 255, 255, 248}
#define LENGTH 45
#define LENGTH_BITS 357

#include "../include/processing.h"
#include <cstdlib>
#include <cstring>
#include <stdio.h>

void evaluate(uint8_t* buffer, uint32_t bytes, uint32_t bits) {
    uint32_t length_in_bits = bytes*8;

    MSG("\ninitial buffer:\n");
    PRINT(buffer, length_in_bits);

    // fill bits containing no data
    fill_bits_without_data(buffer, bytes, bits, WHITE);
    MSG("\nbuffer with filled empty datapoints:\n");
    PRINT(buffer, length_in_bits);

    // strip trailing WHITE datapoints
    length_in_bits = remove_trailing_bits(buffer, bytes, WHITE);
    MSG("\nbuffer with removed trailing bits:\n");
    PRINT(buffer, length_in_bits);

    // process datapoints into ean8 bits
    uint8_t* processed_buffer = process_buffer(buffer, length_in_bits);
    free(buffer);
    MSG("\nprocessed data:\n");
    PRINT(processed_buffer, BITS);

    // validate ean8 code and strip start/stop/separator bits
    uint8_t* compressed_buffer = compress_ean8(processed_buffer);
    free(processed_buffer);
    MSG("\ncompressed ean8 data:\n");
    PRINT(compressed_buffer, 64);

    // validate
    MSG("\nean8 validation result:\n");
    MSG(validate_ean8(compressed_buffer));

    // decode ean8 code
    MSG("\ndecoded ean8 data (x means unknown value): \n");
    for (uint32_t i = 0; i < 8; i++) {
        MSGC(ean8map(compressed_buffer[i])+48);
    }
    MSG("\n");
}

int main() {
    printf("main\n");
    uint8_t data[] = DATA;
    uint8_t* buffer = (uint8_t*) malloc(LENGTH);
    memcpy(buffer, data, LENGTH);
    evaluate(buffer, LENGTH, LENGTH_BITS);
    return 0;
}