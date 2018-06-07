void read4021() {
  digitalWrite(inlatchPin, 1);
  digitalWrite(inlatchPin, 0);
  RegisterValue = shiftIn(indataPin, inclockPin);
}

byte shiftIn(int myDataPin, int myClockPin) {
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
  for (i = 7; i >= 0; i--)
  {
    digitalWrite(myClockPin, 0);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      myDataIn = myDataIn | (1 << i);
    }
    else {
      pinState = 0;
    }
    digitalWrite(myClockPin, 1);

  }
  return myDataIn;
}
