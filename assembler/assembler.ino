#include <Arduino.h>

// Data pins
#define D0 2
#define D1 3
#define D2 4
#define D3 5
#define D4 6
#define D5 7
#define D6 8
#define D7 9

// Address pins
#define A0 14
#define A1 15
#define A2 16
#define A3 17

#define WRITE_ENABLE 13

void setAddress(int address) {
    digitalWrite(A0, (address >> 0) & 1);
    digitalWrite(A1, (address >> 1) & 1);
    digitalWrite(A2, (address >> 2) & 1);
    digitalWrite(A3, (address >> 3) & 1);
}

void setData(byte value) {
    digitalWrite(D0, (value >> 0) & 1);
    digitalWrite(D1, (value >> 1) & 1);
    digitalWrite(D2, (value >> 2) & 1);
    digitalWrite(D3, (value >> 3) & 1);
    digitalWrite(D4, (value >> 4) & 1);
    digitalWrite(D5, (value >> 5) & 1);
    digitalWrite(D6, (value >> 6) & 1);
    digitalWrite(D7, (value >> 7) & 1);
}

byte addition[] = {
    0b00011110, // 0 - LDA 14
    0b00101111, // 1 - ADD 15
    0b11100000, // 2 - OUT
    0b11110000, // 3 - HLT
    0b00000000, // 4 - NOP
    0b00000000, // 5 - NOP
    0b00000000, // 6 - NOP
    0b00000000, // 7 - NOP
    0b00000000, // 8 - NOP
    0b00000000, // 9 - NOP
    0b00000000, // 10 - NOP
    0b00000000, // 11 - NOP
    0b00000000, // 12 - NOP
    0b00000000, // 13 - NOP
    0b00000101, // 14 - NOP 5
    0b00000101, // 15 - NOP 5
};

byte multiplication[] ={
    0b00011110, // 0 - LDA 14
    0b00111100, // 1 - SUB 12
    0b01110110, // 2 - JC 6
    0b00011101, // 3 - LDA 13
    0b11100000, // 4 - OUT
    0b11110000, // 5 - HLT
    0b01001110, // 6 - STA 14
    0b00011101, // 7 - LDA 13
    0b00101111, // 8 - ADD 15
    0b01001101, // 9 - STA 13
    0b01100000, // 10 - JMP
    0b00000000, // 11 - NOP
    0b00000001, // 12 - NOP 1
    0b00000000, // 13 - NOP
    0b00001000, // 14 - NOP 8
    0b00001000, // 15 - NOP 8
};

void setup() {
    Serial.begin(57600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    digitalWrite(WRITE_ENABLE, HIGH);
    pinMode(WRITE_ENABLE, OUTPUT);

    digitalWrite(D0, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);


    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);

    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);

    byte program[sizeof(multiplication)];
    memcpy(program, multiplication, sizeof(multiplication));

    for (int address = 0; address < 16; address++) {
        Serial.print("Setting address to ");
        Serial.println(address, HEX);
        setAddress(address);
        delay(200);

        Serial.print("Setting data");
        Serial.println(program[address], BIN);
        setData(program[address]);
        delay(200);

        Serial.println("Writing...");
        digitalWrite(WRITE_ENABLE, LOW);
        delay(10);
        digitalWrite(WRITE_ENABLE, HIGH);
        delay(10);
    }
    Serial.println("Done.");
}

void loop() {

}