void play_note(int note, bool play, byte channel) {
  byte status_byte = play ? 0x9 : 0x8;
  status_byte = (status_byte << 4) + channel; 
  Serial.write(status_byte);
  Serial.write(12+note);
  Serial.write(100);
}
