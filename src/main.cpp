#define THRESHOLD 750
#define BUFFER_LENGTH 500 // datapoints/8
#define TIMEOUT 500000 // microseconds

#define UPLOAD
#define MSG(S) Serial.print(S)
#define MSGC(C) Serial.write(C)
#define PRINT(BUFFER, SIZE) MSG("("); MSG(SIZE); MSG(") [0: "); for (uint32_t I = 0; I < (SIZE); I++) { MSG(GET_BIT(BUFFER, I)); if (I % 8 == 7 && I < SIZE-1) { MSG("] ["); MSG(I/8+1); MSG(": ");}} MSG("]\n")

#include <Arduino.h>
#include <processing.h>

void evaluate(uint8_t* buffer, uint32_t bytes, uint32_t bits) {
    uint32_t length_in_bits = bytes*8;

    MSG("\ninitial buffer:\n");
    //PRINT(buffer, length_in_bits);

    // fill bits containing no data
    fill_bits_without_data(buffer, bytes, bits, WHITE);
    MSG("\nbuffer with filled empty datapoints:\n");
    //PRINT(buffer, length_in_bits);

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

bool reading;
bool stop;
uint64_t last_black_timestamp;
uint8_t* buffer;
uint32_t bit_index;
uint8_t color;

void setup() {
    Serial.begin(9600);

    // initialization
    reading = false;
    bit_index = 0;
    color = WHITE;
    buffer = malloc(BUFFER_LENGTH);
    memset(buffer, 0xFF, BUFFER_LENGTH);
}

void loop() {
    if (stop) return;

    // obtain values
    double value = analogRead(A0);
    color = value < THRESHOLD;
    Serial.print(color);

    // start reading
    if (!reading && color == BLACK) {
        reading = true;
    }

    // read
    if (reading) {
        SET_BIT(buffer, bit_index, color);
        bit_index++;
    }

    // stop reading
    if (reading && color == BLACK) last_black_timestamp = micros();
    if (reading && micros() > last_black_timestamp+TIMEOUT) {
        Serial.print("stopped reading. bit index: [");
        Serial.print(bit_index);
        Serial.print("] ");
        evaluate(buffer, BUFFER_LENGTH, bit_index);
        stop = true;
    }
}