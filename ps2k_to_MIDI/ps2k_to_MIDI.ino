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
    static void clean();
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
struct PressedKeyData {
  int key;
  int octave;
};

struct PressedKeyFilterRes {
  bool filterIn;
  int octave;
};
 
void input_key(int key_pressed);
void play_key(int key);
PressedKeyFilterRes filter_key(int key_pressed);


/*
 * Note playing
 */
int octavier = 1; //Start at "first" octave. (Can be negative...)
byte channel_play_OnOff = 0b111 ;
byte channel_replay_OnOff = 0b111;
byte channel_record_OnOff = 0b111;
void play_note(int note, bool play, byte channel);
void channel_off(byte channel);
