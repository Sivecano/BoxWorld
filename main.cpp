#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <list>
#include <functional>
#include <string>
#include "events.h"
//#include "globalevents.h"
#include "boxbase.h"
#include <random>

const int width = 1280;
const int height = 720;
const float elasticity = 1;

std::vector<Box> scene;
TTF_Font* font;
std::list<unsigned int> frametimes = {0,0,0,0,0,0,0,0,0,0};

void update(float dt)
{
    for (int i = 0; i < scene.size(); i++)
    {
        scene[i].shape.x += dt * scene[i].velocity.x;
        scene[i].shape.y += dt * scene[i].velocity.y;
        //scene[i].velocity.y += dt * 500;

        if (scene[i].shape.x < 0 || scene[i].shape.x + scene[i].shape.w > width) {
            scene[i].shape.x -= dt * scene[i].velocity.x;
            scene[i].velocity.x = (-2 * signbit(scene[i].shape.x) + 1) * scene[i].velocity.x;
        }

        if (scene[i].shape.y < 0 || scene[i].shape.y + scene[i].shape.h > height) {
            scene[i].shape.y -= dt * scene[i].velocity.y;
            scene[i].velocity.y = (-2 * signbit(scene[i].shape.y) + 1) * scene[i].velocity.y;
        }
    }

    for(int i = 0; i < scene.size(); i++)
        for (int j = i + 1; j < scene.size(); j++)
            if (boxphysics::are_touching(&scene[i], &scene[j])) {
                float tvx = scene[i].velocity.x, tvy = scene[i].velocity.y;
                boxphysics::collision(&scene[i], &scene[j], elasticity);
                scene[i].shape.x -= dt * tvx;
                scene[i].shape.y -= dt * tvy;
                //scene[j].shape.x += dt * scene[j].velocity.x;
                //scene[j].shape.y += dt * scene[j].velocity.y;
            }
}

void draw(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    for (int i = 0; i < scene.size(); i++) {
        SDL_SetRenderDrawColor(ren,255 - scene[i].mass * 255. / 50., 0, 100, 255);
        SDL_RenderFillRectF(ren, &scene[i].shape);
    }
    SDL_Colour textc = {0, 0,0, 255};


    SDL_Surface* t = TTF_RenderText_Solid(font, std::to_string(10000./(std::accumulate(frametimes.begin(), frametimes.end(), 0.000000001))).c_str(), textc);
    SDL_Texture* tx =SDL_CreateTextureFromSurface(ren, t);
    SDL_Rect dst = {5, 0, t->w * 20 / t->h, 20};
    SDL_RenderCopy(ren, tx, 0, &dst);
    SDL_RenderPresent(ren);
    SDL_FreeSurface(t);
    SDL_DestroyTexture(tx);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/TTF/Hack-Regular.ttf", 20);
    if (font == NULL)
    {
        SDL_Log("font didn't load");
        return 1;
    }

    scene.push_back(Box(1, 20, 50, 40, 40, true, 200));
    scene.push_back(Box(1, 200, 50, 40, 40, true));

    for (int i = 0; i < 2000; i++)
        scene.push_back(Box(rand() % 50 + 1, rand() % width, rand() % height, 10, 10, true, rand() % 400 - 200, rand() % 400 - 200));

    SDL_Window* win;
    SDL_Renderer* ren;
    bool running = true;
    unsigned int last_ticks = 0;
    unsigned int ticks;
    unsigned int dt;

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &win, &ren);

    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                running = false;

        ticks = SDL_GetTicks();
        dt = ticks - last_ticks;
        last_ticks = ticks;

        frametimes.pop_back();
        frametimes.push_front(dt);

        update(dt / 1000.);
        draw(ren);

        
        //update_event(dt/1000.);
        //physupdate_event(dt/1000.);
        //draw_event(ren);
    }

    return 0;

}