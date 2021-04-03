//
// Created by sivecano on 03/04/2021.
//

#include "circlecollider.h"

Circle::Circle(float x, float y, float r, float mass, float vx, float vy):
position({x, y}), radius(r), mass(mass), velocity({vx, vy})
{

}

void Circle::draw(SDL_Renderer* ren, SDL_Color colour)
{
    SDL_SetRenderDrawColor(ren, colour.r, colour.g, colour.b, colour.a);
    //SDL_RenderDrawPoint();
}

bool circlecollisions::are_touching(Circle* circle1, Circle* circle2)
{
    return (pow(circle1->position.x - circle2->position.x, 2) +
            pow(circle1-> position.y - circle2->position.y, 2))
            < pow(circle1->radius + circle2->radius, 2);
}

void circlecollisions::collision(Circle* circle1, Circle* circle2, float elasticity)
{
    return;
}


