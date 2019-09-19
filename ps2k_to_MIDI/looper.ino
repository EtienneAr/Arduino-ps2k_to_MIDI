long int loop_start = 0;
long int loop_period = 1;
bool isTapingLoop = false;

bool isLoopPlaying = false;
Event* curr_noteLoop = 0;
int long loop_playTime;


inline void tap_loop() {
  if(!isTapingLoop) {
    loop_start = millis();
    isTapingLoop = true;
  } else {
    loop_period = millis()-loop_start;
    isTapingLoop = false;
    Serial.println("Start : " + String(loop_start) + " loop : " + String(loop_period));
  }
}

inline void loop_record(int note) {
  EventList::add(note, (millis() - loop_start) % loop_period);
  if(!isLoopPlaying) start_play_loop();
}

void start_play_loop() {
  curr_noteLoop = EventList::get(0);
  int period_nb = (millis() - loop_start) / loop_period;
  loop_playTime = curr_noteLoop->event_time + (period_nb + 1) * loop_period + loop_start;
  isLoopPlaying = true;
  Serial.println("isLoopPlaying " + String(isLoopPlaying) + " Playtime " + String(loop_playTime) + " millis() " + String(millis()));
}

inline void play_loop() {
  if(isLoopPlaying && loop_playTime < millis()) {
    play_note(curr_noteLoop->note);
    //get next note
    int period_nb = (millis() - loop_start) / loop_period;
    curr_noteLoop = curr_noteLoop->next_event;
    if(curr_noteLoop != NULL) {
      loop_playTime = curr_noteLoop->event_time + period_nb * loop_period + loop_start;
    } else {
      //End of the list, go back to first event
      curr_noteLoop = EventList::get(0);
      loop_playTime = curr_noteLoop->event_time + (period_nb + 1) * loop_period + loop_start;
    }
  }
}
