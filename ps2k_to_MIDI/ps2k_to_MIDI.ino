#include <ps2keypolled.h>

/*
 * Looper
 */
void tap_loop();
inline void loop_record(int note);
bool record_loop = false;
void start_play_loop();

/*
 * List
 */
class Event {
  public:
    long int note;
    int event_time;
    Event* next_event;
    
    Event(int note, long int event_time) {
      this->note = note;
      this->event_time = event_time;
      this->next_event = NULL;
    }
};

class EventList {
  public:
    static void add(int note, long int event_time);
    static Event* get(int i);  
    //static void print();
  
  private:
    static Event* first_event = NULL;
};


/*
 * key_input
 */
void play_key(int key);
void stop_key(int key);
void input_key(int key_pressed);

/*
 * Note playing
 */
 void play_note(int note);
 void stop_note(int note);
