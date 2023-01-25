#include <Arduino.h>

#include "../include/processing.h"

#define THRESHOLD 750
#define BUFFER_LENGTH 250 // datapoints/8
#define TIMEOUT 500000 // microseconds

// timeout calculation
uint64_t time_since_black;
uint64_t now;
uint64_t last;

// reading process
bool reading;
uint8_t color;
char* buffer;
uint32_t byte_index; // bytes in buffer
uint8_t bit_index; // bits in byte

void save_datapoint(uint8_t datapoint) {
    set_bit(buffer, byte_index, bit_index)
    if (bit_index >= 8) {bit_index = 0; byte_index++;}
}

void evaluate() {
    // strip trailing WHITE datapoints
    uint32_t length_in_bits = byte_index*8 + bit_index;
    remove_trailing_bits(buffer, &length_in_bits, WHITE);

    // process datapoints into ean8 bits
    uint8_t* processed_buffer = process_buffer(buffer, &length_in_bits);
    free(buffer);

    // validate ean8 code and strip start/stop/separator bits
    uint8_t* validated_buffer = validate_ean8(processed_buffer);
    free(processed_buffer);

    // decode ean8 code
    uint16_t digit1 = decode_ean8(validated_buffer);
    uint16_t digit2 = decode_ean8(validated_buffer+4);

    Serial.println(digit1);
    Serial.println(digit2);
}

void setup() {
    // hardware
    pinMode(A0, INPUT);
    Serial.begin(9600);

    // initialization
    bool reading = false;
    uint8_t color = WHITE;
    buffer = malloc(BUFFER_LENGTH);
    uint64_t time_since_black = 0;
    uint64_t now = 0;
    uint64_t last = 0;
    uint32_t byte_index = 0;
    uint8_t bit_index = 0;

    // clear buffer
    memset(buffer, WHITE, BUFFER_LENGTH);
}

void loop() {
    // obtain values
    double value = analogRead(A0);
    color = value < THRESHOLD;

    // start reading process
    if (!reading and color == BLACK) {
        reading = true;
    }

    // continue reading process
    if (reading) {
        save_datapoint(color);
    }

    // stop reading process after timeout
    if (reading) {
        now = micros();
        if (value == BLACK) {
            time_since_black = 0;
        } else {
            time_since_black += now-last;
        }
        last = now;

        if (time_since_black > TIMEOUT) {
            reading = false;
            evaluate();
        }
    }
}