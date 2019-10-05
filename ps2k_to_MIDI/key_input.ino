#define MAX_PRESSED_KEY 4

int pressed_keys[MAX_PRESSED_KEY];

int table_note_filled[] = {0, -9, 0, -5, -3, -1, -2, -12, 0, -10, -8, -6, -4, 31, 30, 0, 0, 0, 11, 0, 0, 33, 32, 0, 0, 0, 14, 15, 13, 35, 34, 0, 0, 17, 16, 0, 36, 37, 0, 0, 0, 0, 19, 18, 40, 38, 39, 0, 0, 23, 21, 22, 20, 41, 0, 0, 0, 0, 24, 0, 43, 42, 44, 0, 0, 26, 25, 45, 47, 0, 46, 0, 0, 28, 29, 27, 0, 48, 49, 0, 0, 0, 30, 0, 50, 51, 0, 0, 0, 31, 0, 52, 0, 33, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -13, 0, -11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

int key_found;
int i;

/*
 * Do the action corresponding to the key
 */
void play_key(int key) {
  int key_nb = abs(key);
  bool key_isPressed = (key > 0);
  int note;
  
  if(key_nb<256) {
    note = table_note_filled[key_nb];
    if(note > 0) {
      play_note(note, key_isPressed, channel_OnOff);
      if(record_loop) loop_record(note, key_isPressed, channel_OnOff);
    } else {
      switch(note) {
        case -13: //ESC
          if(key_isPressed) tap_loop();
          break;
        case -1: //F1
          if(key_isPressed) record_loop = !record_loop;
          break;
        case -10: //F10
          if(key_isPressed) channel_OnOff ^= 0x1;
          break;
        case -11: //F11
          if(key_isPressed) channel_OnOff ^= 0x2;
          break;
        case -12: //F12
          if(key_isPressed) channel_OnOff ^= 0x4;
          break;
      }
    }
  } else {
    //Serial.print("Sp");
    //Serial.println(key);
  }
}

/*
 * Handles key events
 */
void input_key(int key) {
  if(!filter_key(key)) return; //This key was already taken into account
  play_key(key);
}

/*
 * This function basically prevent to trigger multiple
 * time a note when the stay pressed on one key.
 */
bool filter_key(int key_pressed) {
  if(key_pressed > 0) {                   //keyPressed
    key_found = false;
    for(i=0;i<MAX_PRESSED_KEY;i++) {      //loop on the currently pressed keys
      if(pressed_keys[i] == key_pressed) {
        key_found = true;
        break;
      }
    }
    if(!key_found) {                      //if the key is not pressed already
      for(i=0;i<MAX_PRESSED_KEY;i++) {
        if(pressed_keys[i] == -1) {       //if there is an empty space
          pressed_keys[i] = key_pressed;  //add the key and play it
          return true;
        }
      }
    }
  } else {                                //keyReleased
    for(i=0;i<MAX_PRESSED_KEY;i++) {      //loop on the currently pressed keys
      if(pressed_keys[i] == -key_pressed) {
        pressed_keys[i] = -1;
        return true;
      }
    }
  }
  return false;
}
