long int loop_start = 0, loop_period = 1;
bool isTapingLoop = false;

bool isLoopPlaying = false;
int curr_noteLoop = 0;


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
  if(!isLoopPlaying) play_loop();
}

void play_loop() {
  Event* e = EventList::get(0);
  
}
