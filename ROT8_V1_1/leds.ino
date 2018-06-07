void leds() {

  //if mode is 0 or 1 indicate which step is active
  if (mode == 0 || mode == 1) {
    for (int i = 0; i < 8; i++) {
      if (i <= lastStep) {
        if (seq[i] == 1 && repeats[i] < 1) {
          regOne.pinOn(pin[i + 8]);
        }
        if (seq[i] == 0 && repeats[i] < 1) {
          regOne.pinOff(pin[i + 8]);
        }
      } else {
        regOne.pinOff(pin[i + 8]);
      }
    }
  }

  //if mode is 0 indicate which stepmode is active
  if (mode == 0) {
    regOne.pinOff(pin[16]);
    regOne.pinOff(pin[21]);
  }

  //if menu is not active show which playmode is active
  if (mode != 2 && mode != 6) {
    for (int i = 0; i < 4; i++) {
      if (i == playMode) {
        regOne.pinOn(pin[i + 17]);
      } else {
        regOne.pinOff(pin[i + 17]);
      }
    }
  }

  //repeats page
  if (mode == 6) {
    for (int i = 0; i < 4; i++) {
      if (i == gateMode[selectedStep]) {
        regOne.pinOn(pin[i + 17]);
      } else {
        regOne.pinOff(pin[i + 17]);
      }
    }

    for (int i = 0; i < 8; i++) {
      if (i <= repeats[selectedStep] && i != selectedStep) {
        regOne.pinOn(pin[i + 8]);
      }
      if (i > repeats[selectedStep] && i != selectedStep) {
        regOne.pinOff(pin[i + 8]);
      }
    }
  }

  //tune mode
  if (mode == 1) {
    regOne.pinOff(pin[21]);
  }


  //menu mode
  if (mode == 2) {
    regOne.pinOff(pin[16]);
    regOne.pinOff(pin[21]);
    if (!resBlink) {
      //CV mode select
      if (menuCurs == 0) {
        regOne.pinOn(pin[17]);
        regOne.pinOn(pin[18]);
        regOne.pinOff(pin[19]);
        regOne.pinOff(pin[20]);
        for (int i = 0; i < 8; i++) {
          if (i == CVmode) {
            regOne.pinOn(pin[i + 8]);
          } else {
            regOne.pinOff(pin[i + 8]);
          }
        }
      }

      //Pot mode select
      if (menuCurs == 1) {
        regOne.pinOff(pin[17]);
        regOne.pinOff(pin[18]);
        regOne.pinOn(pin[19]);
        regOne.pinOn(pin[20]);
        for (int i = 0; i < 8; i++) {
          if (i == potMode) {
            regOne.pinOn(pin[i + 8]);
          } else {
            regOne.pinOff(pin[i + 8]);
          }
        }

      }
    }
  }

  //gate length select
  if (mode == 4) {
    regOne.pinOn(pin[16]);
    regOne.pinOff(pin[21]);
    for (int i = 0; i < 8; i++) {
      if (i <= map(gateCV, 0, 96, 0, 8)) {
        regOne.pinOn(pin[i + 8]);
      } else {
        regOne.pinOff(pin[i + 8]);
      }
    }
    regOne.pinOff(pin[16]);
  }

  //reset select page
  if (mode == 3) {
    for (int i = 0; i < 8; i++) {
      if (i == resetSelected) {
        regOne.pinOn(pin[i + 8]);
      } else {
        regOne.pinOff(pin[i + 8]);
      }
    }
  }

  //if lastStep mode is active show sequence range
  if (mode == 5) {
    regOne.pinOn(pin[21]);
    regOne.pinOff(pin[16]);

    for (int i = 0; i < 8; i++) {
      if (i <= lastStep) {
        regOne.pinOn(pin[i + 8]);
      } else {
        regOne.pinOff(pin[i + 8]);
      }
    }
  }
  change = false;
}

void blinks(int ledno, int blinkspeed) {
  if (currentMillis - blinkMillis >= blinkspeed) {
    if (!ledblink) {
      regOne.pinOn(pin[ledno]);
      ledblink = true;
    } else {
      regOne.pinOff(pin[ledno]);
      ledblink = false;
    }
    blinkMillis = currentMillis;
  }
}

void blinking() {
  if (mode == 0) {
    if (currentMillis - repBlinkMillis1 >= 40) {
      if (!repBlinkRes1) {
        repBlinkRes1 = true;
      } else {
        repBlinkRes1 = false;
      }
      repBlinkMillis1 = currentMillis;
    }

    if (currentMillis - repBlinkMillis0 >= 80) {
      if (!repBlinkRes0) {
        repBlinkRes0 = true;
      } else {
        repBlinkRes0 = false;
      }
      repBlinkMillis0 = currentMillis;
    }

    for (int i = 0; i < 8; i++) {
      if (repeats[i] > 0 && seq[i] == 1) {
        if (!repBlinkRes1) {
          regOne.pinOn(pin[i + 8]);
        } else {
          regOne.pinOff(pin[i + 8]);
        }
      }

      if (repeats[i] > 0 && seq[i] == 0) {
        if (!repBlinkRes0) {
          regOne.pinOn(pin[i + 8]);
        } else {
          regOne.pinOff(pin[i + 8]);
        }
      }
    }
  }

  if (mode == 6) {
    if (currentMillis - repBlinkMillis1 >= 40) {
      if (!repBlinkRes1) {
        repBlinkRes1 = true;
      } else {
        repBlinkRes1 = false;
      }
      repBlinkMillis1 = currentMillis;
    }

    if (currentMillis - repBlinkMillis0 >= 80) {
      if (!repBlinkRes0) {
        repBlinkRes0 = true;
      } else {
        repBlinkRes0 = false;
      }
      repBlinkMillis0 = currentMillis;
    }
    if (selectedStep == repeats[selectedStep]) {
      if (!repBlinkRes1) {
        regOne.pinOn(pin[selectedStep + 8]);
      } else {
        regOne.pinOff(pin[selectedStep + 8]);
      }
    } else {
      if (!repBlinkRes0) {
        regOne.pinOn(pin[selectedStep + 8]);
      } else {
        regOne.pinOff(pin[selectedStep + 8]);
      }
    }
  }

  if (mode == 1) {
    blinks(16, 80);
  }

  if (mode == 3) {
    blinks(21, 80);
  }

  if (resBlink) {
    if (currentMillis - resBlinkMillis >= 80) {
      if (!ledblinkres) {
        for (int i = 17; i < 21; i++) {
          regOne.pinOn(pin[i]);
        }
        ledblinkres = true;
        blinknumber++;
      } else {
        for (int i = 17; i < 21; i++) {
          regOne.pinOff(pin[i]);
        }
        ledblinkres = false;
      }
      resBlinkMillis = currentMillis;
    }
    if (blinknumber >= 4) {
      resBlink = false;
      resetActive = false;
      change = true;
    }
  }
}

void bootanim() {
  int del = 200;
  regOne.pinOn(pin[8]);
  regOne.pinOn(pin[15]);
  delay(del);
  regOne.pinOff(pin[8]);
  regOne.pinOff(pin[15]);
  regOne.pinOn(pin[9]);
  regOne.pinOn(pin[14]);
  delay(del);
  regOne.pinOff(pin[9]);
  regOne.pinOff(pin[14]);
  regOne.pinOn(pin[10]);
  regOne.pinOn(pin[13]);
  delay(del);
  regOne.pinOff(pin[10]);
  regOne.pinOff(pin[13]);
  regOne.pinOn(pin[11]);
  regOne.pinOn(pin[12]);
  delay(del);
  regOne.pinOff(pin[11]);
  regOne.pinOff(pin[12]);
  regOne.pinOn(pin[16]);
  regOne.pinOn(pin[21]);
  delay(del);
  regOne.pinOff(pin[16]);
  regOne.pinOff(pin[21]);
  regOne.pinOn(pin[17]);
  regOne.pinOn(pin[20]);
  delay(del);
  regOne.pinOff(pin[17]);
  regOne.pinOff(pin[20]);
  regOne.pinOn(pin[18]);
  regOne.pinOn(pin[19]);
  delay(del);
  regOne.pinOff(pin[18]);
  regOne.pinOff(pin[19]);
  delay(del);
}

