#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include <vector>
#include <list>
#include <queue>
#include <functional>
#include <string>
#include "vector"
#include "events.h"
//#include "globalevents.h"
#include "boxbase.h"
#include <random>
#include "circlecollider.h"
#define INSANITY

const int width = 1920;
const int height = 1080;
const float elasticity = 1.;
const int simres = 1;

std::vector<Box> scene;
std::vector<Circle> cscene;
TTF_Font* font;
std::list<unsigned int> frametimes = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void update(float dt)
{
    for (int i = 0; i < scene.size(); i++)
    {
        //scene[i].velocity.y += dt * 500;
        scene[i].shape.x += dt * scene[i].velocity.x;
        scene[i].shape.y += dt * scene[i].velocity.y;

        if ((scene[i].shape.x < 0) || (scene[i].shape.x + scene[i].shape.w > width)) {
            scene[i].velocity.x = elasticity * (2 * signbit(scene[i].shape.x) - 1) * abs(scene[i].velocity.x);
            scene[i].shape.x +=  (1 + elasticity)* !signbit(scene[i].shape.x) * (width - scene[i].shape.w) - scene[i].shape.x;
        }

        if ((scene[i].shape.y < 0) || (scene[i].shape.y + scene[i].shape.h > height)) {
            scene[i].velocity.y = elasticity * (2 * signbit(scene[i].shape.y) - 1) * abs(scene[i].velocity.y);
            scene[i].shape.y += (1 + elasticity) * !signbit(scene[i].shape.y) *(height - scene[i].shape.h) - scene[i].shape.y;
        }
    }
	
    for(int i = 0; i < scene.size(); i++)
        for (int j = 0; j < scene.size(); j++)
            if (i != j)
                if (boxphysics::are_touching(&scene[i], &scene[j])) {
                    boxphysics::collision(&scene[i], &scene[j], elasticity);
                    //scene[j].shape.x += dt * scene[j].velocity.x;
                    //scene[j].shape.y += dt * scene[j].velocity.y;
                }
}

void cupdate(float dt)
{
    for (auto & circl : cscene)
    {
        /*if (circl.position.y > height - (circl.radius + 20))
            circl.velocity.x = 0;
        else
            circl.velocity.y += dt * 500;*/

        circl.position +=  circl.velocity * dt;

        // float elasticity = 1;
    }
    //TODO: look at time order
    std::queue<int> check;
    for (int i = 0; i < cscene.size(); i++)
        check.push(i);

    const int max_iter = 100000;
    int iter = 0;

    while(!check.empty() && iter++ < max_iter) {
        int i = check.front();
        check.pop();
        if ((cscene[i].position.x < cscene[i].radius) || (cscene[i].position.x + cscene[i].radius > width)) {
            cscene[i].velocity.x =
                    elasticity * (2 * (cscene[i].position.x < cscene[i].radius) - 1) * abs(cscene[i].velocity.x);
            cscene[i].position.x += (1 + elasticity) * (width - cscene[i].radius - cscene[i].position.x +
                                                        (cscene[i].position.x < cscene[i].radius) *
                                                        (2 * cscene[i].radius - width));
#ifdef INSANITY
            check.push(i);
#endif
        }

        if ((cscene[i].position.y < cscene[i].radius) || (cscene[i].position.y + cscene[i].radius > height)) {
            cscene[i].velocity.y =
                    elasticity * (2 * (cscene[i].position.y < cscene[i].radius) - 1) * abs(cscene[i].velocity.y);
            cscene[i].position.y += (1 + elasticity) * (height - cscene[i].radius - cscene[i].position.y +
                                                        (cscene[i].position.y < cscene[i].radius) *
                                                        (2 * cscene[i].radius - height));
#ifdef INSANITY
            check.push(i);
#endif
        }

        for (int j = i + 1; j < cscene.size(); j++)
            if (circlecollisions::are_touching(cscene[i], cscene[j])) {
                circlecollisions::collision(cscene[i], cscene[j], elasticity);
#ifdef INSANITY
                check.push(i);
                check.push(j);
#endif
            }

    }

}

void draw(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, 20, 20, 20, 255);
    SDL_RenderClear(ren);
    /*for (int i = 0; i < scene.size(); i++) {
        SDL_SetRenderDrawColor(ren,255 - scene[i].mass * 255. / 10, 0, 100, 255);
        SDL_RenderFillRectF(ren, &scene[i].shape);
    }*/
}

void renderfps(SDL_Renderer* ren)
{
  // TODO: renderoutput total energy of system over time
    SDL_Surface* t = TTF_RenderText_Solid(font, std::to_string(10000./(std::accumulate(frametimes.begin(), frametimes.end(), 0.000000001))).c_str(), {240, 240,240, 255});
    SDL_Texture* tx =SDL_CreateTextureFromSurface(ren, t);
    SDL_Rect dst = {5, 0, t->w * 20 / t->h, 20};
    SDL_RenderCopy(ren, tx, nullptr, &dst);
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

    // scene.push_back(Box(4, 40,  10, 40, 40, true, 100, 700));
    // scene.push_back(Box(4, 40,  10, 40, 40, true, 100, 700));
    // scene.push_back(Box(4, 40, 200, 40, 40, true, 100, 400));
    // scene.push_back(Box(10, 40, 150, 40, 40, true, 100));

    cscene.emplace_back(40, 200,  40, 4, 100);
    cscene.emplace_back(400, 200, 40, 4, -100);
    cscene.emplace_back(40, 150, 40,4, 100);

    float r;
    for (int i = 0; i < 100; i++)
        cscene.emplace_back((i * 25) % (width - 25) + 25, 25 + ((i * 25) / width), 20, 1, rand() % 800 - 400, rand() % 1600 - 800);

    for (int i = 0; i < 100; i++)
         scene.emplace_back(rand() % 4 + 1, (i % 50) * 40, int(i / 50) * 25 , 30, 30, true, rand() % 2 + 1, rand() % 2 + 1);

    SDL_Window* win;
    SDL_Renderer* ren;
    bool running = true;
    unsigned int last_ticks = SDL_GetTicks();
    unsigned int ticks;
    unsigned int dt;

    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN , &win, &ren);

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
        for (int i = 0; i < simres; i++) {
           //update(dt / 1000. / simres);
            cupdate(dt / 1000. / simres);
        }
        draw(ren);
        /*for (Box b : scene)
        {
            if (isinf(b.shape.x)  || isinf(b.shape.y) || isinf(b.velocity.x) || isinf(b.velocity.y))
                SDL_Log("BOX INF");
            if(isnan(b.velocity.y) || isnan(b.shape.x) || isnan(b.shape.y) || isnan(b.velocity.x))
                SDL_Log("BOX NAN");
            if(b.shape.x < 0 || b.shape.x > width || b.shape.y < 0 || b.shape.y > height)
                SDL_Log("BOX OUTSIDE");
        }*/

        for (Circle c: cscene)
        {
            if (isinf(c.position.x) || isinf(c.position.y) || isinf(c.velocity.y) || isinf(c.velocity.x))
                SDL_Log("CIRCLE INF");
            if (isnan(c.velocity.x)  || isnan(c.velocity.y) || isnan(c.position.x) || isnan(c.position.y))
                SDL_Log("CIRCLE NAN");
            if (c.position.x < c.radius || c.position.x > width - c.radius || c.position.y < c.radius || c.position.y > height - c.radius)
                SDL_Log("CIRCLE OUTSIDE");
        }

        //update_event(dt/1000.);
        //physupdate_event(dt/1000.);
        //draw_event(ren);
        for(Circle c : cscene)
            filledCircleRGBA(ren, c.position.x, c.position.y, c.radius, 200., 0, 0, 255);
        renderfps(ren);
        SDL_RenderPresent(ren);
    }

    TTF_Quit();
    SDL_Quit();


    return 0;

}
