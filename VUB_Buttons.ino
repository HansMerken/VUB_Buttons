#include <Arduino.h>
#include <HardwareSerial.h>
#include <Print.h>
#include <Wire.h>

#include "pins.h"

// constants won't change. They're used here to set pin numbers:
int buttonState;             // the current reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.

unsigned long debounceDelay = 50; // the debounce time; increase if the output flickers
uint32_t lastRequestedValueTime = 0;
uint32_t loopMillis;

const int numButtons = 11;
unsigned long lastDebounceTime[2][numButtons] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; // the last time the output pin was toggled
//make an array with all button pins and last button state
int buttonPins[2][numButtons] = { {
    BUTTON_VOLUMEPRESSURE_UP,
    BUTTON_VOLUMEPRESSURE_DOWN,
    BUTTON_VOLUME_UP,
    BUTTON_VOLUME_DOWN,
    BUTTON_BPM_UP,
    BUTTON_BPM_DOWN,
    BUTTON_TRIG_UP,
    BUTTON_TRIG_DOWN,
    BUTTON_MUTE,
    BUTTON_BREATH,
    BUTTON_MODE
  }, {
    HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH
  }
};
int buttons [numButtons] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


bool test = false;

// define bytes to send
byte RR = 0;
// Number of breaths per minute setting
byte VT = 0;
// Tidal volume= target to deliver
byte PP = 0;
//Peak pressure = Max pressure to deliver
byte TS = 0;
// Breath Trigger Sensitivity = amount the machine should look for
byte IE = 0;
// Inspiration-expiration rate
bool MO = false; //false = Pressure
//Mode

void setup() {
  //for debugging
  Serial.begin(115200);

  //declare all buttons

  pinMode(BUTTON_MODE, INPUT_PULLUP);

  pinMode(BUTTON_VOLUMEPRESSURE_UP, INPUT_PULLUP);
  pinMode(BUTTON_VOLUMEPRESSURE_DOWN, INPUT_PULLUP);

  pinMode(BUTTON_VOLUME_UP, INPUT_PULLUP);
  pinMode(BUTTON_VOLUME_DOWN, INPUT_PULLUP);

  pinMode(BUTTON_BPM_UP, INPUT_PULLUP);
  pinMode(BUTTON_BPM_DOWN, INPUT_PULLUP);

  pinMode(BUTTON_TRIG_UP, INPUT_PULLUP);
  pinMode(BUTTON_TRIG_DOWN, INPUT_PULLUP);

  pinMode(BUTTON_START_STOP, INPUT_PULLUP);

  pinMode(BUTTON_BREATH, INPUT_PULLUP);

  pinMode(BUTTON_MUTE, INPUT_PULLUP);

  pinMode(ALARMPIN, INPUT_PULLUP);

}

void loop() {
  loopMillis = millis();
  //read button inputs
  buttonsRead();
  //array with buttons is filled with data

  //edit parameters

  //send parameters
    serialSend();
  //Update screen

  delay(100);
}


void buttonsRead() {
  //read out the buttons with debounce
  for (int i = 0; i < numButtons; i++)
  {
    //sample the state of the button - is it pressed or not?
    int  reading = digitalRead(buttonPins[0][i]);
    //filter out any noise by setting a time buffer
    if ( (millis() - lastDebounceTime[0][i]) > debounceDelay) {
      if ( reading == HIGH && buttonPins[1][i] != HIGH) {
        buttonPins[1][i] = reading;
        lastDebounceTime[0][i] = millis(); //set the current time
        lastDebounceTime[1][i] = 0; //reset the first time counter for jumpvalue

      }
      else if ( reading == LOW && buttonPins[1][i] != LOW) {
        buttonPins[1][i] = reading;
        lastDebounceTime[0][i] = millis(); //set the current time

        if (lastDebounceTime[1][i] == 0)
        {
          lastDebounceTime[1][i] = millis(); //set the current time to the first time counter for jumpvalue
        }

      }//close if/else
    }//close if(time buffer)
  }

  //change the sign of the buttons
  for (int j = 0; j < numButtons; j++)
  {
    if (buttonPins[1][j] == 0)
    {
      buttons[j] = 1;
    }
    else
    {
      buttons[j] = 0;
    }

  }
  //make the buttons edit the values
  // PP Pressure 0 & 1
  PP = PP +  buttons[0] * jumpValue(0);
  PP = PP -  buttons[1] * jumpValue(1);
  // PP Pressure 2 & 3
  VT = VT +  buttons[2] * jumpValue(2);
  VT = VT -  buttons[3] * jumpValue(3);
  //RR 4 & 5
  RR = RR +  buttons[4] * jumpValue(4);
  RR = RR -  buttons[5] * jumpValue(5);
  //TS 6 & 7
  TS = TS +  buttons[6] * jumpValue(6);
  TS = TS -  buttons[7] * jumpValue(7);

  //mode button here
  //if mode is VOLUME and button is pressed: goto PRESSURE
  if (buttons[10] == 1)
  {
    MO = !MO;
  }

}


int jumpValue(int i) {

  //  if (loopMillis - lastRequestedValueTime < 200) {
  //    return 0;
  // }
  //  lastRequestedValueTime = loopMillis;
  //Serial.println(loopMillis);
  //Serial.println(lastDebounceTime[1][i]);
 // Serial.println(loopMillis-lastDebounceTime[1][0]);



  if ( loopMillis - lastDebounceTime[1][i] > 4000) {
    return 10;
  }
  if ( loopMillis - lastDebounceTime[1][i] > 2000) {
    return 5;
  }
  if (loopMillis - lastDebounceTime[1][i] > 1000) {
    return 3;
  }
  if (loopMillis - lastDebounceTime[1][i] > 500) {
    return 2;
  }
  return 1;
}

void serialSend()
{
  Serial.print("Mode=");
  Serial.println(MO);

  Serial.print("PP=");
  Serial.println(PP);
  Serial.print("VT=");
  Serial.println(VT);
  Serial.print("RR=");
  Serial.println(RR);
  Serial.print("TR=");
  Serial.println(TS);

}
