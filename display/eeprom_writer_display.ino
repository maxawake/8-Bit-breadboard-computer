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
byte data[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70,
               0x7f, 0x7b, 0x77, 0x1f, 0x4e, 0x3d, 0x4f, 0x47};

void setup() {
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_CLOCK, OUTPUT);
    pinMode(SHIFT_LATCH, OUTPUT);
    digitalWrite(WRITE_ENABLE, HIGH);
    pinMode(WRITE_ENABLE, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(57600);

    Serial.println("Erasing EEPROM...");
    for (int address = 0; address < 2048; address++) {
        writeEEPROM(address, 0xff);
        Serial.print(".");
    }

    byte digits[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70,
               0x7f, 0x7b};
    
    Serial.println("\nWriting EEPROM...");
    Serial.println("Writing ones places");
    for (int value = 0; value < 256; value++) {
        writeEEPROM(value, digits[value % 10]);
    }

    Serial.println("Writing tens places");
    for (int value = 0; value < 256; value++) {
        writeEEPROM(value + 256, digits[(value / 10) % 10]);
    }

    Serial.println("Writing hundreds places");
    for (int value = 0; value < 256; value++) {
        writeEEPROM((byte)value + 512, digits[(value / 100) % 10]);
    }

    Serial.println("Writing nothing (0x00)");
    for (int value = 0; value < 256; value++) {
        writeEEPROM((byte)value + 768, 0x00);
    }

    Serial.println("Writing negative numbers ones");
    for (int value = -128; value < 128; value++) {
        writeEEPROM((byte)value + 1024, digits[abs(value) % 10]);
    }

    Serial.println("Writing negative numbers tens");
    for (int value = -128; value < 128; value++) {
        writeEEPROM((byte)value + 1280, digits[abs(value / 10) % 10]);
    }

    Serial.println("Writing negative numbers hundreds");
    for (int value = -128; value < 128; value++) {
        writeEEPROM((byte)value + 1536, digits[abs(value / 100) % 10]);
    }

    Serial.println("Writing negative numbers sign (0x01)");
    for (int value = -128; value < 128; value++) {
        if (value < 0) {
            writeEEPROM((byte)value + 1792, 0x01);
        }
        else {
            writeEEPROM((byte)value + 1792, 0x00);
        }
    }

    Serial.println("Done!");

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
