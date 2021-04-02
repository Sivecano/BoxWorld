#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <functional>
#include <string>
#include "events.h"
//#include "globalevents.h"
#include "boxbase.h"

SDL_FRect a[2];
float v1=1000, v2=200;
float m1=2, m2=1;
unsigned int dt;
TTF_Font* font;

void update(float dt)
{
    a[0].x += dt * v1;
    a[1].x += dt * v2;

    if (a[0].x < 0) v1 = abs(v1);
    if (a[0].x + a[0].w> 800) v1 = - abs(v1);
    if (a[1].x < 0)  v2 = abs(v2);
    if (a[1].x + a[1].w> 800) v2 = - abs(v2);

    if (a[0].x - a[1].x < a[0].w && a[1].x - a[0].x < a[1].w)
    {
        float dv = v1 - v2;
        float a = m2/m1;
        v1 = dv* (1-a)/(1+a) + v2;
        v2 += 2* dv / (1 + a);
    }


}

void draw(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 200, 0, 100, 255);
    SDL_RenderFillRectF(ren, a);
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_RenderFillRectF(ren, a + 1);
    SDL_Colour textc = {0, 0,0, 255};
    
    SDL_Surface* t = TTF_RenderText_Solid(font, std::to_string(1000./(dt + 0.000001)).c_str(), textc);
    SDL_Texture* tx =SDL_CreateTextureFromSurface(ren, t);
    SDL_Rect dst = {0, 0, t->w * 20 / t->h, 20};
    SDL_RenderCopy(ren, tx, 0, &dst);
    SDL_RenderPresent(ren);
    SDL_FreeSurface(t);
    SDL_DestroyTexture(tx);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    font = TTF_OpenFont("/usr/share/fonts/TTF/Hack-Regular.ttf", 12);
    if (font == NULL)
    {
        SDL_Log("font didn't load");
        return 1;
    }

    Box test(0, 0, 10, 10, true);

    a[1].h = a[1].w = a[0].h = a[0].w = 20;
    a[0].y = a[1].y = 100;
    a[0].x = 0;
    a[1].x = 40;



    SDL_Window* win;
    SDL_Renderer* ren;
    bool running = true;
    unsigned int last_ticks = 0;
    unsigned int ticks;

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &win, &ren);

    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                running = false;

        ticks = SDL_GetTicks();
        dt = ticks - last_ticks;
        last_ticks = ticks;

        update(dt / 1000.);
        draw(ren);
        
        //update_event(dt/1000.);
        //physupdate_event(dt/1000.);
        //draw_event(ren);
    }

    return 0;

}