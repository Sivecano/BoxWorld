#include "SDL2/SDL.h"
#pragma once

class Box
{
private:
    SDL_FRect shape;
    float mass;
    SDL_FPoint velocity;
    SDL_FPoint force;

public:
    Box(float x, float y, float h, float w, bool dynamic);
    ~Box();
    virtual void update(float dt);
    virtual void physupdate(float dt);
    void draw(SDL_Renderer* ren);
};
