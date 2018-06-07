void saveState() {
  if (EEPROM.isReady()) {
    for (int i = 0; i < 8; i++) {
      saveInput.stepseq[i] = seq[i];
      saveInput.repeatsstep[i] = repeats[i];
      saveInput.gatemode[i] = gateMode[i];
    }
    saveInput.playmode = playMode;
    saveInput.laststep = lastStep;
    saveInput.cvmode = CVmode;
    saveInput.potmode = potMode;
    saveInput.gateselect = gateSelect;
    saveInput.resetselect = resetSelected;


    // write data to eeprom
    EEPROM.updateBlock(address, saveInput);
  }
}



void loadState() {
  //LOAD LAST SAVED STATE

  EEPROM.readBlock(address, saveOutput);

  for (int i = 0; i < 8; i++) {
    seq[i] = saveOutput.stepseq[i];
    repeats[i] = saveOutput.repeatsstep[i];
    gateMode[i]= saveOutput.gatemode[i];
  }

  playMode = saveOutput.playmode;
  lastStep = saveOutput.laststep;
  CVmode = saveOutput.cvmode;
  potMode = saveOutput.potmode;
  gateSelect = saveOutput.gateselect;
  resetSelected = saveOutput.resetselect;

}
