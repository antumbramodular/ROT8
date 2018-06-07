void trig() {
  //CLOCK INPUT
  clkin = digitalRead(2);

  if (clkin != pclk) {
    if (clkin == LOW) {

      if (resetCount != 0) {
        if (stepCount >= resetCount) {
          clk = 0;
          playhead = 0;
          stepCount = 0;
          setplayhead();
        }
      }

      //if there are repeats on a step, set flag
      if (repeatCount < repeats[clk]) {
        repeat = true;
      } else {
        repeat = false;
      }
      
      stepCount = stepCount + 1;

      pw = currentMillis - pulse;
      pulse = currentMillis;

      //set gate time to fixed values if CV mode is not set to gate time, otherwise use CV value for gate time.
      gate = round(pw / 100 * gateCV);

      //gate modes
      if (seq[clk] == 1) {
        if (gateMode[clk] == 0 && repeatCount == 0) {
          digitalWrite(gatePin, HIGH);
        }

        if (gateMode[clk] == 1) {
          digitalWrite(gatePin, HIGH);
        }

        if (gateMode[clk] == 2) {
          digitalWrite(gatePin, HIGH);
          gateHold = true;
        }

        if (gateMode[clk] == 3) {
          if (random(0, 2) == 1) {
            digitalWrite(gatePin, HIGH);
          }
        }
      } else {
        digitalWrite(gatePin, LOW);
      }

      if (!repeat) {
        repeatCount = 0;
        gateHold = false;
        setplayhead();

        //PLAYMODES:
        switch (playMode) {
          case 0:
            //FWD
            clk++;
            if (clk > lastStep) {
              clk = 0;
            }
            break;

          case 1:
            //BWD
            clk--;
            if (clk < 0) {
              clk = lastStep;
            }
            if (clk > lastStep) {
              clk = lastStep;
            }
            break;

          case 2:
            //PENDULUM MODE
            if (clk >= lastStep) {
              pendulum = true;
            }

            if (clk <= 0) {
              pendulum = false;
            }

            if (pendulum) {
              clk--;
            } else {
              clk++;
            }
            break;

          case 3:
            //RAND MODE
            rstep = random(0, lastStep + 1);
            clk = rstep;
            break;
        }
        playhead = clk;
      } else {
        repeatCount = repeatCount + 1;
        setplayhead();
      }

      pMillis = currentMillis;

    }
    pclk = clkin;
  }
}

void setplayhead() {
  for (int i = 0; i < 8; i++) {
    if (i == playhead) {
      regOne.pinOn(pin[i]);
    } else {
      regOne.pinOff(pin[i]);
    }
  }
}


