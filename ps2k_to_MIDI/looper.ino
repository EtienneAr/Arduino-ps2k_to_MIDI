long int loop_start, loop_period;
bool isTapingLoop = false;



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
  EventList::add(note, millis());
}
