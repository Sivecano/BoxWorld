#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include <vector>
#include <functional>
#include "events.h"
#include "globalevents.h"
#include "boxbase.h"

class Test
{
public:
    void f(int a)
    {
        SDL_Log("%i",a);
    }
    int a()
    {
        SDL_Log("a called");
        return 0;
    }
};

void printnum(int a)
{
    SDL_Log("%d\n", a);
}

int printhello()
{
    SDL_Log("Hello\n");
    return 0;
}


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Test t;



    events::event<void, int> noout;
    events::event<int> noin;

    noout.sub(printnum);
    noin.sub(printhello);
    noout.sub(&t, &Test::f);
    noin.sub(&t, &Test::a);
    noin.sub(&t, &Test::a);

    noin();
    noout(5);
    noin.unsub(&t, &Test::a);
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
        
        update_event(dt/1000.);
        physupdate_event(dt/1000.);
        draw_event(ren);
    }

    return 0;

}