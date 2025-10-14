#line 1 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
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
#define A4 18
#define A5 19
#define A6 11
#define A7 12

#define WRITE_ENABLE 13

#line 25 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
void setAddress(int address);
#line 37 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
void setData(byte value);
#line 126 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
void setup();
#line 186 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
void loop();
#line 25 "/home/max/Repos/8-Bit-breadboard-computer/assembler/assembler.ino"
void setAddress(int address)
{
    digitalWrite(A0, (address >> 0) & 1);
    digitalWrite(A1, (address >> 1) & 1);
    digitalWrite(A2, (address >> 2) & 1);
    digitalWrite(A3, (address >> 3) & 1);
    digitalWrite(A4, (address >> 4) & 1);
    digitalWrite(A5, (address >> 5) & 1);
    digitalWrite(A6, (address >> 6) & 1);
    digitalWrite(A7, (address >> 7) & 1);
}

void setData(byte value)
{
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

// byte multiplication[] ={
//     0b00011110, // 0 - LDA 14
//     0b00111100, // 1 - SUB 12
//     0b01110110, // 2 - JC 6
//     0b00011101, // 3 - LDA 13
//     0b11100000, // 4 - OUT
//     0b11110000, // 5 - HLT
//     0b01001110, // 6 - STA 14
//     0b00011101, // 7 - LDA 13
//     0b00101111, // 8 - ADD 15
//     0b01001101, // 9 - STA 13
//     0b01100000, // 10 - JMP
//     0b00000000, // 11 - NOP
//     0b00000001, // 12 - NOP 1
//     0b00000000, // 13 - NOP
//     0b00001000, // 14 - NOP 8
//     0b00001000, // 15 - NOP 8
// };

byte multiplication[] = {
    0b00010000, // 0 - ISTR: LDA
    0b00011100, // 1 - MEM: 28
    0b00110000, // 2 - ISTR: SUB
    0b00011000, // 3 - MEM: 24
    0b01110000, // 4 - ISTR: JC
    0b00001010, // 5 - MEM: 10
    0b00010000, // 6 - ISTR: LDA
    0b00011010, // 7 - MEM: 26
    0b11100000, // 8 - OUT
    0b11110000, // 9 - HLT
    0b01000000, // 10 - ISTR: STA
    0b00011100, // 11 - MEM: 28
    0b00010000, // 12 - ISTR: LDA
    0b00011010, // 13 - MEM: 26
    0b00100000, // 14 - ISTR: ADD
    0b00011110, // 15 - MEM: 30
    0b01000000, // 16 - ISTR: STA
    0b00011010, // 17 - MEM: 26
    0b01100000, // 18 - ISTR: JMP
    0b00000000, // 19 - MEM: 0
    0b00000000, // 20 - NOP
    0b00000000, // 21 - NOP
    0b00000000, // 22 - NOP
    0b00000000, // 23 - NOP
    0b00000001, // 24 - DATA
    0b00000000, // 25 - NOP
    0b00000000, // 26 - NOP
    0b00000000, // 27 - NOP
    0b00001000, // 28 - DATA
    0b00000000, // 29 - NOP
    0b00001000, // 30 - DATA
    0b00000000, // 31 - NOP
    0b00000000, // 32 - NOP
    0b00000000, // 33 - NOP
    0b00000000, // 34 - NOP
    0b00000000, // 35 - NOP
};

void setup()
{
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
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(A6, OUTPUT);
    pinMode(A7, OUTPUT);

    byte program[sizeof(multiplication)];
    memcpy(program, multiplication, sizeof(multiplication));

    for (int address = 0; address < sizeof(program); address++)
    {
        Serial.print("Setting address to ");
        Serial.println(address, HEX);
        setAddress(address);
        delay(200);

        Serial.print("Setting data ");
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

void loop()
{
}
