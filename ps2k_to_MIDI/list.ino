static Event* EventList::first_event;

static void EventList::add(int note, long int event_time) {
  Event* ptr = new Event(note, event_time);
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

/*
static void EventList::print() {
  Event* ptr = first_event;
  Serial.println("List");
  while(ptr != NULL) {
    Serial.print("(" + String(ptr->note) + ", " + String(ptr->event_time) + ")");
    ptr = ptr->next_event;
  }
  Serial.println();
}
*/
