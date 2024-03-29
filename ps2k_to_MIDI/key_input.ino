#define MAX_PRESSED_KEY 6
PressedKeyData pressed_keys[MAX_PRESSED_KEY];

int table_note_filled[] = {0, -9, 0, -5, -3, -1, -2, -12, 0, -10, -8, -6, -4, 31, 30, 0, 0, 0, 11, 0, 0, 33, 32, 0, 0, 0, 14, 15, 13, 35, 34, 0, 0, 17, 16, 0, 36, 37, 0, 0, 0, 0, 19, 18, 40, 38, 39, 0, 0, 23, 21, 22, 20, 41, 0, 0, 0, 0, 24, 0, 43, 42, 44, 0, 0, 26, 25, 45, 47, 0, 46, 0, 0, 28, 29, 27, 0, 48, 49, 0, 0, 0, 30, 0, 50, 51, 0, 0, 0, 31, 0, 52, 0, 33, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -13, 0, -11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
int i;

byte instrument_pressed = 0b000;

/*
 * Do the action corresponding to the key
 */
void play_key(int key, int octave) {
  int key_nb = abs(key);
  bool key_isPressed = (key > 0);
  int raw_note;
  
  if(key_nb<256) {
    raw_note = table_note_filled[key_nb];
    if(raw_note > 0) {
      int note = octave*12+raw_note;
      play_note(note, key_isPressed, channel_play_OnOff);
      if(record_loop && (channel_play_OnOff & channel_record_OnOff) != 0) {
        loop_record(note, key_isPressed, channel_play_OnOff & channel_record_OnOff);
      }
    } else {
      if(key_isPressed) {
        switch(raw_note) {
          case -13: //ESC
            tap_loop();
            break;
          case -1: //F1
            record_loop = !record_loop;
            break;
  
           //Record instruments
          case -2: //F2
            channel_record_OnOff ^= 0x1;
            break;
          case -3: //3
            channel_record_OnOff ^= 0x2;
            break;
          case -4: //F4
            channel_record_OnOff ^= 0x4;
            break;
  
          case -5: //F5
            isLoopPlaying = !isLoopPlaying;
            if( isLoopPlaying) start_play_loop;
            if(!isLoopPlaying) channel_off(0b111);
            break;
  
           //Replay instruments
          case -6: //F6
            channel_replay_OnOff ^= 0x1;
            if((channel_replay_OnOff & 0b001) == 0) channel_off(0b001);
            break;
          case -7: //F7
            channel_replay_OnOff ^= 0x2;
            if((channel_replay_OnOff & 0b010) == 0) channel_off(0b010);
            break;
          case -8: //F8
            channel_replay_OnOff ^= 0x4;
            if((channel_replay_OnOff & 0b100) == 0) channel_off(0b100);
            break;
  
          //Play instruments
          case -9: //F9
            channel_off(0b111);
            break;
          case -10: //F10
            instrument_pressed |= 0b001;
            channel_play_OnOff = instrument_pressed;
            break;
          case -11: //F11
            instrument_pressed |= 0b010;
            channel_play_OnOff = instrument_pressed;
            break;
          case -12: //F12
            instrument_pressed |= 0b100;
            channel_play_OnOff = instrument_pressed;
            break;
        } //switch(note)
        updateLEDS();
      } else { //key released
        switch(raw_note) {
          case -10: //F10
            instrument_pressed &= 0b110;
            break;
          case -11: //F11
            instrument_pressed &= 0b101;
            break;
          case -12: //F12
            instrument_pressed &=  0b011;
            break;
        }
      } //if(key_isPressed)
    }
  } else { // Special keys
    if(key_nb == 381 && key_isPressed) { // PageUp
      octavier += 1;
    }
    if(key_nb == 378 && key_isPressed) { //PageDown
      octavier -= 1;
    }
  }
}

/*
 * Handles key events
 */
void input_key(int key) {
  PressedKeyFilterRes filt = filter_key(key);
  if(filt.filterIn) {
    play_key(key, filt.octave);
  }
}

/*
 * This function basically prevent to trigger multiple
 * time a note when the stay pressed on one key.
 * Because when kept pressed, multiple signals are sent.
 * 
 * It also takes a screenshot of some variable when the key was pressed to give it back when its released (such as octavier)
 */
PressedKeyFilterRes filter_key(int key_pressed) {
  if(key_pressed > 0) {                   //keyPressed
    for(i=0;i<MAX_PRESSED_KEY;i++) {      //loop on the currently pressed keys
      if(pressed_keys[i].key == key_pressed) {
        return {false, 0}; // The key has been found don't take it in consideration
      }
    }
    for(i=0;i<MAX_PRESSED_KEY;i++) {   // Insert the key in an empty space to register it
      if(pressed_keys[i].key == -1) {
        pressed_keys[i].key = key_pressed;
        pressed_keys[i].octave = octavier;
        return {true, octavier}; // Note that is the key couldn't have been registered it will be filtered out
      }
    }
  } else {                                //keyReleased
    for(i=0;i<MAX_PRESSED_KEY;i++) {      //loop on the currently pressed keys
      if(pressed_keys[i].key == -key_pressed) {
        pressed_keys[i].key = -1;
        return {true, pressed_keys[i].octave};
      }
    }
  }
  return {false, 0};
}
