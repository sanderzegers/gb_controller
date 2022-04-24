/* Joystick-Sender
 *  
 *  Get current joystick & button input and transfer via Gameboy Link cable
 *  Optimized for Digispark ATtiny85 compatible
 */

#include "DigiJoystick.h"

#define ledPin 1

byte bitcounter = 7;
volatile byte bytecounter = 0;
volatile byte capturedBytes[32];
volatile byte input = 0;
byte capturedByte;


#define PULSE_TIME 20


char myBuf[8];

int clockPin = 2;
int mosi = 1;
int miso = 0;

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(mosi, OUTPUT);
  pinMode(miso, INPUT);
  digitalWrite(clockPin, HIGH);
  capturedBytes[0] = 0;

}


byte getJoystickValue() {

  capturedByte = 0;

  for (int i = 7; i >= 0; i--) {
    PORTB &= 0b11111011; //digitalWrite(clockPin, LOW);
    delayMicroseconds(PULSE_TIME);
    PORTB |= 0b00000100;//digitalWrite(clockPin, HIGH);
    delayMicroseconds(PULSE_TIME);
    input = PINB & B00000001;
    capturedByte = capturedByte + (input << i);
  }
}




// Clock rising interrupt handler
void INT_clockRising() {

  input = input + ((PINB & B00000001) << bitcounter);

  if (bitcounter == 0) {
    bitcounter = 7;
    capturedBytes[bytecounter] = input;
    input = 0;
    bytecounter++;
  }
  else {
    bitcounter--;
  }
}




void loop() {

  DigiJoystick.delay(15);

  getJoystickValue();

  bytecounter = 1;

    if (capturedByte != 0) {

        if (capturedByte & 1) { // Right
          myBuf[0] = 255;
        }
        else if (capturedByte & 2) { // Left
          myBuf[0] = 0;
        }
        else myBuf[0] = 127;

        if (capturedByte & 4) { // Up
          myBuf[1] = 0;
        }
        else if (capturedByte & 8) { // Down
          myBuf[1] = 255;
        }
        else myBuf[1] = 127;

        if (capturedByte & 16) { // A
          myBuf[6] |= 0x02;
        }
        else myBuf[6] &= ~0x02;

        if (capturedByte & 32) { // B
          myBuf[6] |= 0x01;
        }
        else myBuf[6] &= ~0x01;

        if (capturedByte & 64) { // select
          myBuf[6] |= 0x04;
        }
        else myBuf[6] &= ~0x04;
        if (capturedByte & 128) { // start
          myBuf[6] |= 0x08;
        }
        else myBuf[6] &= ~0x08;

        DigiJoystick.setValues(myBuf);
      bytecounter = 0;
    }

    else {

      //center joystick + release all buttons
      myBuf[6] = 0;
      myBuf[0] = 127;
      myBuf[1] = 127;
      DigiJoystick.setValues(myBuf);
      input = 0;
    }
  }
