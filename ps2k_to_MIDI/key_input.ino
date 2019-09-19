#define MAX_PRESSED_KEY 4

int pressed_keys[MAX_PRESSED_KEY];

int table_note_filled[] = {0, -9, 0, -5, -3, -1, -2, -12, 0, -10, -8, -6, -4, 31, 30, 0, 0, 0, 11, 0, 0, 33, 32, 0, 0, 0, 14, 15, 13, 35, 34, 0, 0, 17, 16, 0, 36, 37, 0, 0, 0, 0, 19, 18, 40, 38, 39, 0, 0, 23, 21, 22, 20, 41, 0, 0, 0, 0, 24, 0, 43, 42, 44, 0, 0, 26, 25, 45, 47, 0, 46, 0, 0, 28, 29, 27, 0, 48, 49, 0, 0, 0, 30, 0, 50, 51, 0, 0, 0, 31, 0, 52, 0, 33, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -13, 0, -11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

int key_found;
int i;

/*
 * Handles key_pressed events
 */
void play_key(int key) {
  int note;
  if(key<256) {
    note = table_note_filled[key];
    if(note > 0) {
      play_note(note);
      if(record_loop) loop_record(note);
    } else {
      switch(note) {
        case -13: //ESC
          tap_loop();
          break;
        case -1: //F1
          record_loop = !record_loop;
          break;
        case -2: //F2
          //EventList::print();
          break;
      }
    }
  } else {
    Serial.print("Sp");
    Serial.println(key);
  }
}

/*
 * Handle key_released events
 */
void stop_key(int key) {
  if(key<256) stop_note(table_note_filled[key]);
}


/*
 * This function basically prevent to trigger multiple
 * time a note when the stay pressed on one key.
 */
void input_key(int key_pressed) {
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
          play_key(key_pressed);
          pressed_keys[i] = key_pressed;  //add the key and play it
          break;
        }
      }
    }
  } else {                                //keyReleased
    for(i=0;i<MAX_PRESSED_KEY;i++) {      //loop on the currently pressed keys
      if(pressed_keys[i] == -key_pressed) {
        stop_key(-key_pressed);
        pressed_keys[i] = -1;
        break;
      }
    }
  }
}
