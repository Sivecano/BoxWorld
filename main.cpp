#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include <vector>
#include <functional>
#include "events.h"
//#include "globalevents.h"
#include "boxbase.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Box test(0, 0, 10, 10, true);


    SDL_Window* win;
    SDL_Renderer* ren;
    bool running = true;
    unsigned int last_ticks = 0;
    unsigned int ticks;
    unsigned int dt;



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
        
        //update_event(dt/1000.);
        //physupdate_event(dt/1000.);
        //draw_event(ren);
    }

    return 0;

}