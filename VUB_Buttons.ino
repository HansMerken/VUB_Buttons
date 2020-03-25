#include <Arduino.h>
#include <HardwareSerial.h>
#include <Print.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "pins.h"

//Constants Tim


LiquidCrystal_I2C lcd(0x3f, 20,  4);




//Constants Hans

// define bytes to send
unsigned int RR = 0;
// Number of breaths per minute setting
unsigned int VT = 0;
// Tidal volume= target to deliver
unsigned int PK = 50;
//Peak pressure
unsigned int TS = 0;
// Breath Trigger Sensitivity = amount the machine should look for
float IE = 0;
// Inspiration-expiration rate
unsigned int PP = 0;
//PEEP Pressure = Max pressure to deliver
bool MO = false; //false = Pressure
//Mode

unsigned int PKtresh = 10;
unsigned int VTtresh = 10;
unsigned int PPtresh = 5;





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

void setup() {
  //for debugging
  Serial.begin(115200);
  //init LCD
  lcd.backlight();
  lcd.init();
  //print values void
  printLetters();
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

  printValues();


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
  // PK Pressure 0 & 1
  PK = PK +  buttons[0] * jumpValue(0);
  PK = PK -  buttons[1] * jumpValue(1);
  // VT 2 & 3
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
    clearValues();
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
  //1
  Serial.print("Mode=");
  Serial.println(MO);
  //2
  Serial.print("PK=");
  Serial.println(PK);
  //3
  Serial.print("VT=");
  Serial.println(VT);
  //4
  Serial.print("RR=");
  Serial.println(RR);
  //5
  Serial.print("TR=");
  Serial.println(TS);
  //6
  Serial.print("IE=");
  Serial.println(IE);
  //7
  Serial.print("PP=");
  Serial.println(PP);
  //8
  Serial.print("PKtresh=");
  Serial.println(PKtresh);
  //9
  Serial.print("VTtresh=");
  Serial.println(VTtresh);
  //10
  Serial.print("PPtresh=");
  Serial.println(PPtresh);





}


void printValues() {
  lcd.setCursor(12, 2);
  if (MO == true) lcd.print("VOLUME");
  if (MO == false) lcd.print("PRESSURE");
  lcd.setCursor(3, 0);
  lcd.print(PK);
  lcd.setCursor(7, 0);
  lcd.print(PKtresh);
  lcd.setCursor(3, 1);
  lcd.print(VT);
  lcd.setCursor(7, 1);
  lcd.print(VTtresh);
  lcd.setCursor(15, 0);
  lcd.print(RR);
  lcd.setCursor(15, 1);
  lcd.print(TS);
  lcd.setCursor(3, 2);
  lcd.print(PP);
  lcd.setCursor(7, 2);
  lcd.print(PPtresh);
  lcd.setCursor(15, 3);
  lcd.print(IE);
}
void printLetters()
{
  lcd.setCursor(0, 0);
  lcd.print("PK");
  lcd.setCursor(0, 1);
  lcd.print("VT");
  lcd.setCursor(12, 0);
  lcd.print("RR");
  lcd.setCursor(12, 1);
  lcd.print("TS");
  lcd.setCursor(0, 2);
  lcd.print("PP");
  lcd.setCursor(12, 3);
  lcd.print("IE");
}

void clearValues()
{
  lcd.setCursor(12, 2);
  lcd.print("        ");
  lcd.setCursor(3, 0);
  lcd.print("   ");
  lcd.setCursor(7, 0);
  lcd.print("   ");
  lcd.setCursor(3, 1);
  lcd.print("   ");
  lcd.setCursor(7, 1);
  lcd.print("   ");
  lcd.setCursor(15, 0);
  lcd.print("   ");
  lcd.setCursor(15, 1);
  lcd.print("   ");
  lcd.setCursor(3, 2);
  lcd.print("   ");
  lcd.setCursor(7, 2);
  lcd.print("   ");
  lcd.setCursor(15, 3);
  lcd.print("   ");
}
