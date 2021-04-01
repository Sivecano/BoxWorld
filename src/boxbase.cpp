#include "boxbase.h"
#include "globalevents.h"

Box::Box(float x, float y, float h, float w, bool dynamic)
{
    update_event.sub(this, &Box::update);
    //update_event.sub(this, Box::update);
}

Box::~Box()
{

}

void Box::update(float dt)
{
    SDL_Log("update");
}
void Box::physupdate(float dt)
{

}
void Box::draw(SDL_Renderer* ren)
{

}
