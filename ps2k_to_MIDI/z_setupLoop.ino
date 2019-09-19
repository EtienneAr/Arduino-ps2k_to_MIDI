void ISR_func(int key_code) {
  digitalWrite(13,HIGH);
  input_key(key_code);
  digitalWrite(13,LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  
  for(i=0;i<MAX_PRESSED_KEY;i++) {
    pressed_keys[i] = -1;
  }
  ps2k_attach(ISR_func);
  ps2k_init(3, 4);
}


void loop() {
  play_loop();
  
}
