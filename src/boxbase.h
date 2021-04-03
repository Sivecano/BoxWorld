#include "SDL2/SDL.h"
#pragma once


class Box
{
public:
    SDL_FRect shape;
    float mass;
    SDL_FPoint velocity;
    bool is_dynamic;

    Box(float mass, float x, float y, float h, float w, bool dynamic = true, float vx = 0, float vy = 0);
    ~Box();
    virtual void update(float dt);
    virtual void physupdate(float dt);
    void draw(SDL_Renderer* ren);
};

namespace boxphysics{
    bool are_touching(Box* box1, Box* box2);
    void collision(Box* box1, Box* box2, float elasticity = 1);


};