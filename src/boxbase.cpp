#include "boxbase.h"
#include "globalevents.h"

Box::Box(float x, float y, float h, float w, bool dynamic)
{
    //update_event.sub(this, &Box::update);
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


bool boxphysics::are_touching(Box* box1, Box* box2)
{
    float dx = box1->shape.x - box2->shape.x;
    float dy = box1->shape.y - box2->shape.y;

    return (dx < box1->shape.w && -dx < box2->shape.w) && (dy < box1->shape.h && -dy < box2->shape.h);
}

void boxphysics::collision(Box* box1, Box* box2)
{
    float* v1 = &box1->velocity.x;
    float* v2 = &box2->velocity.x;

    if (box1->shape.y - box2->shape.y < box1->shape.h && box2->shape.y - box1->shape.y < box2->shape.h)
    {
        v1 = &box1->velocity.y;
        v2 = &box2->velocity.y;
    }

    if (!box1->is_dynamic){
        *v2 = -*v2;
        return;
    }
    if (!box2->is_dynamic){
        *v1 = -*v1;
        return;
    }

    float dv = *v1 - *v2;
    float a = box2->mass/box1->mass;
    *v1 = dv* (1-a)/(1+a) + *v2;
    *v2 += 2* dv / (1 + a);
}