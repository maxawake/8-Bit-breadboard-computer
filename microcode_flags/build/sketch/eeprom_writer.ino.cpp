#include <Arduino.h>
#line 10 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
void setAddress(int address, bool outputEnable);
#line 19 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
byte readEEPROM(int address);
#line 32 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
byte readNLines(int address, int lines);
#line 46 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
void writeEEPROM(int address, byte value);
#line 116 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
void setup();
#line 156 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
void loop();
#line 0 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
#line 1 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer.ino"
// #include <Arduino.h>

// #define SHIFT_DATA 2
// #define SHIFT_CLOCK 3
// #define SHIFT_LATCH 4
// #define EEPROM_D0 5
// #define EEPROM_D7 12
// #define WRITE_ENABLE 13

// void setAddress(int address, bool outputEnable) {
//     shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
//     shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, address);

//     digitalWrite(SHIFT_LATCH, LOW);
//     digitalWrite(SHIFT_LATCH, HIGH);
//     digitalWrite(SHIFT_LATCH, LOW);
// }

// byte readEEPROM(int address) {
//     for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
//         pinMode(pin, INPUT);
//     }

//     setAddress(address, /*outputEnabele*/ true);
//     byte buffer = 0;
//     for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
//         buffer = (buffer << 1) + digitalRead(pin);
//     }
//     return buffer;
// }

// byte readNLines(int address, int lines) {
//     for (int base = 0; base < lines; base += 16) {
//         byte data[16];
//         for (int offset = 0; offset < 16; offset++) {
//             data[offset] = readEEPROM(address + base + offset);
//         }

//         char buffer[80];
//         sprintf(buffer, "%03x: %02x %02x %02x %02x  %02x %02x %02x %02x   %02x %02x %02x %02x  %02x %02x %02x %02x", address + base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);

//         Serial.println(buffer);
//     }
// }

// void writeEEPROM(int address, byte value) {
//     setAddress(address, /*outputEnabele*/ false);

//     for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
//         pinMode(pin, OUTPUT);
//     }

//     for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
//         digitalWrite(pin, value & 1);
//         value = value >> 1;
//     }
//     digitalWrite(WRITE_ENABLE, LOW);
//     delayMicroseconds(1);
//     digitalWrite(WRITE_ENABLE, HIGH);
//     delay(10); // wait for write to complete

//     // Reset data pins to INPUT after writing
//     for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
//         pinMode(pin, INPUT);
//     }
// }

// // test string
// // byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
// //                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

// // 0 to 16 in hex (0 - F)
// byte data[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70,
//                0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47};

// void setup() {
//     pinMode(SHIFT_DATA, OUTPUT);
//     pinMode(SHIFT_CLOCK, OUTPUT);
//     pinMode(SHIFT_LATCH, OUTPUT);
//     digitalWrite(WRITE_ENABLE, HIGH);
//     pinMode(WRITE_ENABLE, OUTPUT);
//     pinMode(LED_BUILTIN, OUTPUT);

//     Serial.begin(57600);

//     Serial.println("Erasing EEPROM...");
//     for (int address = 0; address < 2048; address++) {
//         writeEEPROM(address, 0xff);
//         Serial.print(".");
//     }

//     byte digits[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70,
//                0x7f, 0x7b};
    
//     Serial.println("\nWriting EEPROM...");
//     Serial.println("Writing ones places");
//     for (int value = 0; value < 256; value++) {
//         writeEEPROM(value, digits[value % 10]);
//     }

//     Serial.println("Writing tens places");
//     for (int value = 0; value < 256; value++) {
//         writeEEPROM(value + 256, digits[(value / 10) % 10]);
//     }

//     Serial.println("Writing hundreds places");
//     for (int value = 0; value < 256; value++) {
//         writeEEPROM((byte)value + 512, digits[(value / 100) % 10]);
//     }

//     Serial.println("Writing nothing (0x00)");
//     for (int value = 0; value < 256; value++) {
//         writeEEPROM((byte)value + 768, 0x00);
//     }

//     Serial.println("Writing negative numbers ones");
//     for (int value = -128; value < 128; value++) {
//         writeEEPROM((byte)value + 1024, digits[abs(value) % 10]);
//     }

//     Serial.println("Writing negative numbers tens");
//     for (int value = -128; value < 128; value++) {
//         writeEEPROM((byte)value + 1280, digits[abs(value / 10) % 10]);
//     }

//     Serial.println("Writing negative numbers hundreds");
//     for (int value = -128; value < 128; value++) {
//         writeEEPROM((byte)value + 1536, digits[abs(value / 100) % 10]);
//     }

//     Serial.println("Writing negative numbers sign (0x01)");
//     for (int value = -128; value < 128; value++) {
//         if (value < 0) {
//             writeEEPROM((byte)value + 1792, 0x01);
//         }
//         else {
//             writeEEPROM((byte)value + 1792, 0x00);
//         }
//     }

//     Serial.println("Done!");

//     readNLines(0, 256);
//     Serial.println("Exiting.");
// }

// void loop() {
      
//       while(true) {
//         digitalWrite(LED_BUILTIN, HIGH);
//         delay(100);
//         digitalWrite(LED_BUILTIN, LOW);
//         delay(100);
//       }
// }

#line 1 "/home/max/Nextcloud/Projects/8 Bit Computer/Arduino Firmware/eeprom_writer/eeprom_writer_microcode.ino"
#include <Arduino.h>

#define SHIFT_DATA 2
#define SHIFT_CLOCK 3
#define SHIFT_LATCH 4
#define EEPROM_D0 5
#define EEPROM_D7 12
#define WRITE_ENABLE 13

void setAddress(int address, bool outputEnable) {
    shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, (address >> 8) | (outputEnable ? 0x00 : 0x80));
    shiftOut(SHIFT_DATA, SHIFT_CLOCK, MSBFIRST, address);

    digitalWrite(SHIFT_LATCH, LOW);
    digitalWrite(SHIFT_LATCH, HIGH);
    digitalWrite(SHIFT_LATCH, LOW);
}

byte readEEPROM(int address) {
    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
        pinMode(pin, INPUT);
    }

    setAddress(address, /*outputEnabele*/ true);
    byte buffer = 0;
    for (int pin = EEPROM_D7; pin >= EEPROM_D0; pin--) {
        buffer = (buffer << 1) + digitalRead(pin);
    }
    return buffer;
}

byte readNLines(int address, int lines) {
    for (int base = 0; base < lines; base += 16) {
        byte data[16];
        for (int offset = 0; offset < 16; offset++) {
            data[offset] = readEEPROM(address + base + offset);
        }

        char buffer[80];
        sprintf(buffer, "%03x: %02x %02x %02x %02x  %02x %02x %02x %02x   %02x %02x %02x %02x  %02x %02x %02x %02x", address + base, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);

        Serial.println(buffer);
    }
}

void writeEEPROM(int address, byte value) {
    setAddress(address, /*outputEnabele*/ false);

    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
        pinMode(pin, OUTPUT);
    }

    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
        digitalWrite(pin, value & 1);
        value = value >> 1;
    }
    digitalWrite(WRITE_ENABLE, LOW);
    delayMicroseconds(1);
    digitalWrite(WRITE_ENABLE, HIGH);
    delay(10); // wait for write to complete

    // Reset data pins to INPUT after writing
    for (int pin = EEPROM_D0; pin <= EEPROM_D7; pin++) {
        pinMode(pin, INPUT);
    }
}

// test string
// byte data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

// 0 to 16 in hex (0 - F)
// byte data[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70,
//                0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47};

#define HLT 0b1000000000000000
#define MI  0b0100000000000000
#define RO  0b0010000000000000
#define IO  0b0001000000000000
#define II  0b0000100000000000
#define AI  0b0000010000000000
#define AO  0b0000001000000000
#define EO  0b0000000100000000
#define SU  0b0000000010000000
#define BI  0b0000000001000000
#define OI  0b0000000000100000
#define CE  0b0000000000010000
#define CO  0b0000000000001000
#define FI  0b0000000000000100
#define J   0b0000000000000010
#define JM  0b0000000000000001


uint16_t data[] = {
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0000 - NOP
    MI|CO, RO|II|CE,    IO|MI,  RO|AI,  0,      0,  0,  0, // 0001 - LDA
    MI|CO, RO|II|CE,    IO|MI,  RO|BI,  EO|AI,  0,  0,  0, // 0010 - ADD
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0011 

    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0100
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0101
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0110 
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 0111 

    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1000
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1001
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1010
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1011

    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1100
    MI|CO, RO|II|CE,    0,      0,      0,      0,  0,  0, // 1101 
    MI|CO, RO|II|CE,    AO|OI,  0,      0,      0,  0,  0, // 1110 - OUT
    MI|CO, RO|II|CE,    HLT,    0,      0,      0,  0,  0, // 1111 - HLT
};

void setup() {
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_CLOCK, OUTPUT);
    pinMode(SHIFT_LATCH, OUTPUT);
    digitalWrite(WRITE_ENABLE, HIGH);
    pinMode(WRITE_ENABLE, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(57600);

    Serial.print("Erasing EEPROM");
    for (int address = 0; address < 2048; address++) {
        writeEEPROM(address, 0x00);
        if (address % 64 == 0) {
            Serial.print(".");
        }
    }
    Serial.print(" done.\n");

    Serial.print("Writing EEPROM");
    for (int address = 0; address < sizeof(data)/sizeof(data[0]); address++) {
        writeEEPROM(address, data[address] >> 8);
        if (address % 64 == 0) {
            Serial.print(".");
        }
    }

    for (int address = 0; address < sizeof(data)/sizeof(data[0]); address++) {
        writeEEPROM(address + 128, data[address]);
        if (address % 64 == 0) {
            Serial.print(".");
        }
    }
    Serial.print(" done.\n");

    
    readNLines(0, 256);
    Serial.println("Exiting.");
}

void loop() {
      
      while(true) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
      }
}

