void play_note(int note, bool play) {
  if(play) {
    Serial.println("Play " + String(note));
  } else {
    Serial.println("Stop " + String(note));
  }
}
