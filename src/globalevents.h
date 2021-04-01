#ifndef GLOBAL_EVENTS_H
#define GLOBAL_EVENTS_H
#include<events.h>
extern events::event<void, float> update_event;
extern events::event<void, float> physupdate_event;
extern events::event<void, SDL_Renderer*> draw_event;


#endif