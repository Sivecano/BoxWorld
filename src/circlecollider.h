//
// Created by sivecano on 03/04/2021.
//

#ifndef BOXWORLD_CIRCLECOLLIDER_H
#define BOXWORLD_CIRCLECOLLIDER_H
#include "SDL2/SDL.h"


class Circle {
public:
    SDL_FPoint position;
    SDL_FPoint velocity;
    float mass;
    float radius;

    Circle(float x, float y, float r, float mass, float vx = 0, float vy = 0);
    void draw(SDL_Renderer* ren, SDL_Color colour);


};

namespace circlecollisions
{
    bool are_touching(Circle* circle1, Circle* circle2);
    void collision(Circle* circle1, Circle* circle2, float elasticity = 1);
};


#endif //BOXWORLD_CIRCLECOLLIDER_H
