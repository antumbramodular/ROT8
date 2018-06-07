void buttons() {
  read4021();
  for (int i = 0; i < 3; i++) {
    button(i);
  }
  for (int i = 0; i < 8; i++) {
    state(i);
  }
}

void button(int id) {
  if (!resetActive) {
    if (digitalRead(id + 11) == LOW) {

      //button is active
      if (!buttonActive[id]) {
        buttonActive[id] = true;
        buttonTimer[id] = millis();
      }

      if ((millis() - buttonTimer[0]) > prepTime && buttonActive[0] && buttonActive[2]) {
        resetPrep = true;
      }

      //set flag and change mode if long press is active
      if (!resetPrep) {
        if ((millis() - buttonTimer[id]) > modeTime && !menuactive) {
          menuactive = true;
          if (mode == id + 1) {
            mode = 0;
          } else {
            mode = id + 1;
          }
          change = true;
        }
      }

      //if buttons 1 & 3 are pressed long reset to default
      if ((millis() - buttonTimer[0]) > resetTime && buttonActive[0] && buttonActive[2]) {
        resetActive = true;
        buttonActive[0] = false;
        buttonActive[2] = false;
        lastStep = 7;
        for (int i = 0; i < 8; i++) {
          seq[i] = 0;
          repeats[i] = 0;
          gateMode[i] = 0;
        }
        resetSelected = 0;
        clk = 0;
        playhead = 0;
        setplayhead();
        CVmode = 1;
        potMode = 2;
        playMode = 0;
        gateCV = 50;
        change = true;
        resBlink = true;
        blinknumber = 0;
        saveState();
      }

    } else {
      if (!resetPrep) {
        //if a long press was active, turn off flag
        if (buttonActive[id] && menuactive) {
          buttonActive[id] = false;
          menuactive = false;
        }

        if (mode == 0 || mode == 4 || mode == 5 || mode == 6) {

          //switch to gate length select
          if (id == 0 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            if (mode != 4) {
              mode = 4;
            } else {
              mode = 0;
            }
            change = true;

          }

          //switch to last step page
          if (id == 2 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            if (mode != 5) {
              mode = 5;
            } else {
              mode = 0;
            }
            change = true;
          }

        }

        if (mode == 1) {
          if (id == 0 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            mode = 0;
            change = true;
          }

          if (id == 2 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
          }
        }

        if (mode == 3) {
          if (id == 2 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            mode = 0;
            change = true;
          }
          if (id == 0 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
          }
        }

        //menu mode cursor change
        if (mode == 2) {
          if (id == 1 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            if (menuCurs < 1) {
              menuCurs = menuCurs + 1;
            } else {
              menuCurs = 0;
            }
            change = true;
          }

          if (buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
          }
        }

        //switch playmode if you are not in menu mode or repeat mode
        if (mode != 2 && mode != 6) {
          if (id == 1 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            if (playMode < 3) {
              playMode = playMode + 1;
            } else {
              playMode = 0;
            }
            change = true;
          }
        }

        if (mode == 6) {
          if (id == 1 && buttonActive[id] && !menuactive) {
            buttonActive[id] = false;
            if (gateMode[selectedStep] < 3) {
              gateMode[selectedStep] = gateMode[selectedStep] + 1;
            } else {
              gateMode[selectedStep] = 0;
            }
            change = true;
          }
        }
      } else {
        resetPrep = false;
        change = true;
      }
    }
  }
}

bool readBut(int i) {
  int result;
  byte b = RegisterValue & buts[i];
  if (b == buts[i]) {
    result = true;
  } else {
    result = false;
  }
  return result;
}

void state(int i) {
  bool fclick = true;

  if (readBut(i) == HIGH) {
    //step button is active
    if (!sButtonActive[i]) {
      sButtonActive[i] = true;
      sButtonTimer[i] = millis();
    }

    if (mode == 0) {
      if ((millis() - sButtonTimer[i]) > modeTime) {
        mode = 6;
        selectedStep = i;
        repeatsMenu = true;
        change = true;
      }
    }
  } else {
    if (sButtonActive[i] && repeatsMenu) {
      sButtonActive[i] = false;
      repeatsMenu = false;
      lclicked = 8;
    }

    //if mode is 0 buttons enable/disable steps
    if (mode == 0 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      if (seq[i] == 0) {
        seq[i] = 1;
      } else {
        seq[i] = 0;
      }
      saveState();
    }

    //if mode is 1 playhead jumps to selected step
    if (mode == 1 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      playhead = i;
      setplayhead();
    }

    //if mode is 2 menu is active
    if (mode == 2 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      if (menuCurs == 0) {
        if (i < 4) {
          CVmode = i;
        }
      }
      if (menuCurs == 1) {
        if (i < 4) {
          potMode = i;
        }
      }
      saveState();
    }

    //if mode is 3 buttons select sequencer reset time
    if (mode == 3 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      resetSelected = i;
      resetCount = resetBank[resetSelected];
      saveState();
    }

    //if mode is 4 buttons select gate length
    if (mode == 4 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      gateSelect = i;
      gateCV = gateBank[gateSelect];
      saveState();
    }

    //if mode is 5 buttons select last step
    if (mode == 5 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      lastStep = i;
      saveState();
    }

    //if mode is 6, buttons select repats
    if (mode == 6 && sButtonActive[i] && !repeatsMenu) {
      sButtonActive[i] = false;
      fclick = false;
      repeats[selectedStep] = i;
      clicked = i;

      if (clicked == lclicked && !fclick) {
        mode = 0;
      }

      lclicked = clicked;
      saveState();
    }
    change = true;
    //save state after button press
  }
}
