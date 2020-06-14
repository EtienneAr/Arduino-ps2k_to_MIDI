#define LED_0_R 13
#define LED_0_G 6

#define LED_3_R 7
#define LED_3_G 8

#define LED_2_R 9
#define LED_2_G 10

#define LED_1_R 11
#define LED_1_G 12

#define LED_SETUP_DELAY 100

void initLEDS() {
  //Mode
  pinMode(LED_0_R, OUTPUT);
  pinMode(LED_0_G, OUTPUT);
  pinMode(LED_1_R, OUTPUT);
  pinMode(LED_1_G, OUTPUT);
  pinMode(LED_2_R, OUTPUT);
  pinMode(LED_2_G, OUTPUT);
  pinMode(LED_3_R, OUTPUT);
  pinMode(LED_3_G, OUTPUT);

  //On
  digitalWrite(LED_0_R, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_0_G, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_1_R, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_1_G, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_2_R, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_2_G, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_3_R, HIGH); delay(LED_SETUP_DELAY);
  digitalWrite(LED_3_G, HIGH); delay(LED_SETUP_DELAY);

  //Off
  digitalWrite(LED_0_R, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_0_G, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_1_R, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_1_G, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_2_R, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_2_G, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_3_R, LOW); delay(LED_SETUP_DELAY);
  digitalWrite(LED_3_G, LOW); delay(LED_SETUP_DELAY);

  //Update
  updateLEDS();
}

void updateLEDS() {
  // LED 0
  digitalWrite(LED_0_G, isLoopPlaying);
  digitalWrite(LED_0_R, record_loop);

  // Instruments
  // 1-
  digitalWrite(LED_1_G, channel_replay_OnOff & 0b001);
  digitalWrite(LED_1_R, channel_record_OnOff & 0b001);

  // 2-
  digitalWrite(LED_2_G, channel_replay_OnOff & 0b010);
  digitalWrite(LED_2_R, channel_record_OnOff & 0b010);

  // 3-
  digitalWrite(LED_3_G, channel_replay_OnOff & 0b100);
  digitalWrite(LED_3_R, channel_record_OnOff & 0b100);
  
}
