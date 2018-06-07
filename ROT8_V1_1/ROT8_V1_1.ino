#include <ShiftOutX.h>
#include <ShiftPinNo.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>

#define latchPin 5         //Pin connected to latch pin (ST_CP) of 74HC595
#define clockPin 6         //Pin connected to clock pin (SH_CP) of 74HC595
#define dataPin 4          //Pin connected to Data pin (DS) of 74HC595

#define indataPin 8        // Pin 3 of CD4021
#define inclockPin 9       // Pin 10 of CD4021
#define inlatchPin 10      // Pin 9 of CD4021

#define clkIn 2            // Clock jack input pin
#define resPin 3            // Reset jack input pin
#define gatePin 7          // Gate output pin
#define CV1in A0           // CV1 input pin
#define CV2in A1           // CV2 input pin
#define OE A2
#define potPin A3           // CV1 input pin

#define but1 11            // Button 1 input
#define but2 12            // Button 2 input
#define but3 13            // Button 3 input


//registers
shiftOutX regOne(5, 4, 6, MSBFIRST, 3);
byte RegisterValue = 72;
byte pRegisterValue = 0;
long pin[24] = {shPin1, shPin2, shPin3, shPin4, shPin5, shPin6, shPin7, shPin8, shPin9, shPin10, shPin11, shPin12, shPin13, shPin14, shPin15, shPin16, shPin17, shPin18, shPin19, shPin20, shPin21, shPin22, shPin23, shPin24};

//defaults
bool seq[8];

int lastStep = 7;
int gateTime = 50;
int menuCurs = 0;
int gateSelect = 0;
int gateBank[] = {5, 13, 25, 38, 50, 63, 75, 88};
int gateMode[] = {0, 0, 0, 0, 0, 0, 0, 0};
int repeats[] = {0, 0, 0, 0, 0, 0, 0, 0};
int gateCV = 50;
int CVrange[] = {lastStep, 95, 7, 1};
int potRange[] = {lastStep, 95, 7, 1};
int selectedStep = 0;
int clicked;
int lclicked;

bool pause = false;

bool change = false;
bool resBlink = false;
int blinknumber = 0;
bool ledblinkres = false;
unsigned long resBlinkMillis = 0;
bool resetActive = false;


//clock in
bool clkin = false;
bool pclk = false;

int CV1 = 0;
int CV2 = 0;
int CV1p = 3;
int CV2p = 0;
int pot = 0;
int potp = 0;
int par = 0;
int parp = 0;
int CVmode = 0;
int potMode = 0;

//play
int rstep = 0;
int clk = 0;
int playhead = 0;
bool count = false;
int stepCheck = 0;

//RESET
bool resIn = false;
bool pRes = false;

//pendulum
bool pendulum = false;
bool pendulumcheck = false;
bool pendulumend = false;

//buttons
bool buttonActive[3];
unsigned long buttonTimer[3];
byte buts[8] = {B1, B10, B100, B1000, B10000, B100000, B1000000, B10000000};
bool pbuts[8];

//menu & modes
int mode = 0;
int stepMode = 0;
int playMode = 0 ;
bool menumode = false;
bool menuactive = false;

bool repeatsMenu = false;
bool sButtonActive[8];
bool repBlinkRes0 = false;
bool repBlinkRes1 = false;
bool repeat = false;
bool gateHold = false;
int repeatCount = 0;
int resetCount = 0;
int resetSelected = 0;
int resetBank[] = {0, 4, 8, 16, 32, 64, 128, 256};
long stepCount = 0;
unsigned long sButtonTimer[8];
unsigned long repBlinkMillis0 = 0;
unsigned long repBlinkMillis1 = 0;

//time to change modes
unsigned long modeTime = 1000;
unsigned long prepTime = 500;
unsigned long resetTime = 3000;
bool resetPrep = false;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
unsigned long pressedMillis = 0;
unsigned long pMillis = 0;
unsigned long blinkMillis = 0;
long pulse = 0;
float pw = 0;
long gate = 4;

bool ledblink = false;

unsigned long testMillis = 0;
bool testSeq = false;

//EEPROM SAVE SETUP

//SAVE ADDRESS
int address = 0;

struct save {
  bool stepseq[8];
  bool repeatsstep[8];
  bool gatemode[8];
  int playmode;
  int cvmode;
  int potmode;
  int laststep;
  int gateselect;
  int resetselect;
};

save saveInput;
save saveOutput;



void setup() {
  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(indataPin, INPUT);
  pinMode(inlatchPin, OUTPUT);
  pinMode(inclockPin, OUTPUT);

  pinMode(but1, INPUT_PULLUP);
  pinMode(but2, INPUT_PULLUP);
  pinMode(but3, INPUT_PULLUP);

  pinMode(OE, OUTPUT);

  pinMode(clkIn, INPUT);
  pinMode(resIn, INPUT);
  pinMode(CV1in, INPUT);
  pinMode(CV2in, INPUT);
  pinMode(gatePin, OUTPUT);


  loadState();
  regOne.allOff();
  digitalWrite(OE, LOW);

  bootanim();
  change = true;

}

void loop() {
  currentMillis = millis();
  buttons();
  CV();

  //internal step sequencer
  /*
    if (currentMillis - testMillis >= 80) {
    if (!testSeq) {
      testSeq = true;
      clkin = HIGH;
    } else {
      testSeq = false;
      clkin = LOW;
    }
    testMillis = currentMillis;
    }
  */

  //RESET INPUT
  resIn = digitalRead(resPin);
  if (resIn != pRes) {
    if (resIn == LOW) {
      clk = 0;
      playhead = 0;
      stepCount = 0;
      setplayhead();
    }
    pRes = resIn;
  }

  //if tune mode or pause is inactive, play sequence
  if (mode != 1  && !pause) {
    trig();
  }

  //set the gate low
  if (currentMillis - pMillis >= gate && !gateHold) {
    digitalWrite(gatePin, LOW);
  }



  if (change) {
    leds();
  }

  blinking();

}
