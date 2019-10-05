unsigned long int loop_start = 0;
unsigned long int loop_period = -1;
bool isTapingLoop = false;

bool isLoopPlaying = false;
Event* curr_keyLoop = 0;
int long loop_playTime;


inline void tap_loop() {
  if(!isTapingLoop) {
    loop_start = millis();
    isTapingLoop = true;
    record_loop = true;
  } else {
    loop_period = millis()-loop_start;
    isTapingLoop = false;
    start_play_loop();
  }
}

inline void loop_record(int key) {
  if(isTapingLoop) EventList::add(key, millis() - loop_start);
  else EventList::add(key, (millis() - loop_start) % loop_period);

}

void start_play_loop() {
  curr_keyLoop = EventList::get(0);
  int period_nb = (millis() - loop_start) / loop_period;
  loop_playTime = curr_keyLoop->event_time + period_nb * loop_period + loop_start;
  isLoopPlaying = true;
}

inline void play_loop() {
  if(isLoopPlaying && loop_playTime < millis()) {
    play_key(curr_keyLoop->key, false);
    //get next key
    int period_nb = (millis() - loop_start) / loop_period;
    curr_keyLoop = curr_keyLoop->next_event;
    if(curr_keyLoop != NULL) {
      loop_playTime = curr_keyLoop->event_time + period_nb * loop_period + loop_start;
    } else {
      //End of the list, go back to first event
      curr_keyLoop = EventList::get(0);
      loop_playTime = curr_keyLoop->event_time + (period_nb + 1) * loop_period + loop_start;
    }
  }
}
