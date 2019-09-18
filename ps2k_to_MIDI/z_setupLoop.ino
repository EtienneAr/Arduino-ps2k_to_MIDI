void setup() {
  Serial.begin(115200);
  for(i=0;i<MAX_PRESSED_KEY;i++) {
    pressed_keys[i] = -1;
  }
   ps2k_init(3, 4);
}


void loop() {
  input_key(key_pressed = ps2k_getkey());
  
}
