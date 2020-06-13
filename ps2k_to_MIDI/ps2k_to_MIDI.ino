#include "src/ps2keypolled/ps2keypolled.h"

/*
 * Looper
 */
void tap_loop();
inline void loop_record(int key);
bool record_loop = false;
void start_play_loop();
bool isLoopPlaying = false;

/*
 * List
 */
class Event {
  public:
    int note;
    bool play;
    byte channel;
    long int event_time;
    Event* next_event;
    
    Event(int note, bool play, byte channel, long int event_time) {
      this->note = note;
      this->play = play;
      this->channel = channel;
      this->event_time = event_time;
      this->next_event = NULL;
    }
};

class EventList {
  public:
    static void add(int note, bool play, byte channel, long int event_time);
    static Event* get(int i);  
    //static void print();
  
  private:
    static Event* first_event = NULL;
};

/*
 * leds
 */
void initLEDS();
void updateLEDS();

/*
 * key_input
 */
void input_key(int key_pressed);
void play_key(int key);
bool filter_key(int key_pressed);


/*
 * Note playing
 */
byte channel_play_OnOff = 0b111 ;
byte channel_replay_OnOff = 0b111;
byte channel_record_OnOff = 0b000;
void play_note(int note, bool play, byte channel);
