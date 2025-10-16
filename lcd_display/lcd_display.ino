#include <Arduino.h>
#include <WCharacter.h>

#define E 5
#define RW 6
#define RS 7
#define D4 8
#define D5 9
#define D6 10
#define D7 11

// first 3 bits are for command, one bit not used, last 4 bits are for data

void sendCommand(uint8_t cmd)
{
    // Send higher nibble
    digitalWrite(RS, LOW);
    digitalWrite(D4, (cmd & 0x10) ? HIGH : LOW);
    digitalWrite(D5, (cmd & 0x20) ? HIGH : LOW);
    digitalWrite(D6, (cmd & 0x40) ? HIGH : LOW);
    digitalWrite(D7, (cmd & 0x80) ? HIGH : LOW);
    write_signal();

    // Send lower nibble
    digitalWrite(RS, LOW);
    digitalWrite(D4, (cmd & 0x01) ? HIGH : LOW);
    digitalWrite(D5, (cmd & 0x02) ? HIGH : LOW);
    digitalWrite(D6, (cmd & 0x04) ? HIGH : LOW);
    digitalWrite(D7, (cmd & 0x08) ? HIGH : LOW);
    write_signal();
}

void write_signal()
{
    digitalWrite(E, HIGH);
    delayMicroseconds(1); // Enable pulse width >= 450ns
    digitalWrite(E, LOW);
    delayMicroseconds(50); // Wait for more than 37us
}

void send_data(uint8_t data)
{
    // Send higher nibble
    digitalWrite(RS, HIGH);
    digitalWrite(D4, (data & 0x10) ? HIGH : LOW);
    digitalWrite(D5, (data & 0x20) ? HIGH : LOW);
    digitalWrite(D6, (data & 0x40) ? HIGH : LOW);
    digitalWrite(D7, (data & 0x80) ? HIGH : LOW);
    write_signal();

    // Send lower nibble
    digitalWrite(RS, HIGH);
    digitalWrite(D4, (data & 0x01) ? HIGH : LOW);
    digitalWrite(D5, (data & 0x02) ? HIGH : LOW);
    digitalWrite(D6, (data & 0x04) ? HIGH : LOW);
    digitalWrite(D7, (data & 0x08) ? HIGH : LOW);
    write_signal();
}

void write_message(const char *msg, int line)
{
    if (line == 1)
    {
        sendCommand(0b10000000); // Set DDRAM address to 0x00
    }
    else if (line == 2)
    {
        sendCommand(0b11000000); // Set DDRAM address to 0x40
    }
    else
    {
        return; // Invalid line number
    }
    delayMicroseconds(50); // Small delay after cursor positioning
    
    while (*msg)
    {
        send_data(*msg++);
        delayMicroseconds(50); // Small delay between characters
    }
}

void displayNumber(int num, int line)
{
    // Position cursor on the specified line
    if (line == 1)
    {
        sendCommand(0b10000000); // Set DDRAM address to 0x00
    }
    else if (line == 2)
    {
        sendCommand(0b11000000); // Set DDRAM address to 0x40
    }
    else
    {
        return; // Invalid line number
    }
    delayMicroseconds(50);

    // Clear the line first by writing spaces
    for (int i = 0; i < 16; i++)
    {
        send_data(' ');
        delayMicroseconds(50);
    }

    // Go back to start of line
    if (line == 1)
    {
        sendCommand(0b10000000); // Set DDRAM address to 0x00
    }
    else if (line == 2)
    {
        sendCommand(0b11000000); // Set DDRAM address to 0x40
    }
    delayMicroseconds(50);

    // Convert number to string and display
    char buffer[16];
    sprintf(buffer, "Number: %d", num);
    
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        send_data(buffer[i]);
        delayMicroseconds(50);
    }
}

void setup()
{
    pinMode(E, OUTPUT);
    pinMode(RW, OUTPUT);
    pinMode(RS, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);

    digitalWrite(RW, LOW); // Write mode

    delay(50); // Wait for more than 40ms after Vcc rises to 2.7V

    // 4-bit initialization sequence (critical!)
    digitalWrite(RS, LOW);
    digitalWrite(D4, HIGH);  // 0x03
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    write_signal();
    delay(5);

    // Repeat for reliability
    digitalWrite(RS, LOW);
    digitalWrite(D4, HIGH);  // 0x03
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    write_signal();
    delayMicroseconds(150);

    // Set to 4-bit mode (CRITICAL - this was commented out!)
    digitalWrite(RS, LOW);
    digitalWrite(D4, LOW);   // 0x02
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    write_signal();
    delayMicroseconds(150);

    // Function set: 4-bit interface, 2-line display, 5x8 font
    sendCommand(0b00101000); // 0x28
    delayMicroseconds(50);

    // Display control: display on, cursor off, blink off
    sendCommand(0b00001100); // 0x0C
    delayMicroseconds(50);

    // Clear display
    sendCommand(0b00000001); // 0x01
    delay(2);                // Clear needs longer delay

    // Entry mode: increment cursor, no shift (CRITICAL!)
    sendCommand(0b00000110); // 0x06
    delayMicroseconds(50);

    
    // Display initial message
    write_message("Counting 1-100", 1);
    delay(1000); // Show initial message for 1 second
}

void loop()
{
    // Loop through numbers from 1 to 100
    for (int i = 1; i <= 100; i++)
    {
        displayNumber(i, 2); // Display current number on line 2
        delay(500); // Wait 500ms before showing next number
    }
    
    // After reaching 100, show completion message
    write_message("Complete!", 2);
    delay(2000); // Wait 2 seconds
    
    // Clear second line and restart
    sendCommand(0b11000000); // Move to second line
    delayMicroseconds(50);
    for (int i = 0; i < 16; i++)
    {
        send_data(' '); // Clear line
        delayMicroseconds(50);
    }
    delay(1000); // Wait 1 second before restarting
}
