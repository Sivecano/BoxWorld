#include "/usr/include/SDL2/SDL.h"
#include <vector>
#include "events.h"

void a()
{
    SDL_Log("a");
}

void b()
{
    SDL_Log("b");
}

void c()
{
    SDL_Log("c");
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    events::event<void> update;
    SDL_Window* win;
    SDL_Renderer* ren;
    update.sub(a);
    update.sub(a);
    update.sub(b);
    update.unsub(b);
    update.sub(c);
    update();
    

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &win, &ren);

    SDL_Delay(100);

    return 0;

}