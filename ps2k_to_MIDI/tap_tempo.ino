long int tempo_start, tempo_period;
bool isTapingTempo = false;

void tap_tempo() {
  if(!isTapingTempo) {
    tempo_start = millis();
    isTapingTempo = true;
  } else {
    tempo_period = millis()-tempo_start;
    isTapingTempo = false;
    Serial.println("Start : " + String(tempo_start) + " tempo : " + String(tempo_period));
  }
}