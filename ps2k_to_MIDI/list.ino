static Event* EventList::first_event;

static void EventList::add(int note, bool play, byte channel, long int event_time) {
  Event* ptr = new Event(note, play, channel, event_time);
  if(first_event == NULL || first_event->event_time > ptr->event_time) {
    ptr->next_event = first_event;
    first_event = ptr;
  } else {
    Event* running_ptr = first_event;
    while(running_ptr->next_event != NULL) {
      if(running_ptr->next_event->event_time > ptr->event_time) break;
      running_ptr = running_ptr->next_event;
    }
    ptr->next_event = running_ptr->next_event;
    running_ptr->next_event = ptr;
  }
}

static Event* EventList::get(int i) {
  Event* ptr = first_event;
  while(i > 0 && ptr != NULL) {
    ptr = ptr->next_event;
    i--;
  }
  return ptr;
}

/*
static void EventList::print() {
  Event* ptr = first_event;
  Serial.println("List");
  while(ptr != NULL) {
    Serial.print("(" + String(ptr->key) + ", " + String(ptr->event_time) + ")");
    ptr = ptr->next_event;
  }
  Serial.println();
}
*/
