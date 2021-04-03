#include "boxbase.h"
#include "globalevents.h"

Box::Box(float mass, float x, float y, float h, float w, bool dynamic, float vx, float vy):
shape({x, y, h, w}), velocity({vx, vy}), is_dynamic(dynamic), mass(mass)
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

void boxphysics::collision(Box* box1, Box* box2, float elasticity)
{
    float* v1 = &box1->velocity.x;
    float* v2 = &box2->velocity.x;
    bool y = false;
    float dy = (box1->velocity.y- box2->velocity.y > 0) ? (box2->shape.y - box1->shape.y - box1->shape.h) : (box2->shape.y + box2->shape.h - box1->shape.y);
    float dx = (box1->velocity.x- box2->velocity.x > 0) ? (box2->shape.x - box1->shape.x - box1->shape.w) : (box2->shape.x + box2->shape.w - box1->shape.x) ;

    if ((dy / (box1->velocity.y- box2->velocity.y)) > (dx / (box1->velocity.x- box2->velocity.x)))
    {
        v1 = &box1->velocity.y;
        v2 = &box2->velocity.y;
        y = true;
    }

    float dv = *v1 - *v2;
    float t = (y ? dy: dx) / dv;

    box1->shape.x += t * box1->velocity.x;
    box1->shape.y += t * box1->velocity.y;
    box2->shape.x += t * box2->velocity.x;
    box2->shape.y += t * box2->velocity.y;

    if (!box1->is_dynamic){
        *v2 = dv * (1 + elasticity) + *v2;
        return;
    }
    if (!box2->is_dynamic){
        *v1 = -dv * elasticity + *v2;
        return;
    }

    *v1 = dv * (box1->mass - elasticity * box2->mass) / (box1->mass + box2->mass) + *v2;
    *v2 = dv * (box1->mass + elasticity * box1->mass) / (box1->mass + box2->mass) + *v2;
}