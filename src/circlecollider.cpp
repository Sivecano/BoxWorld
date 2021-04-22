//
// Created by sivecano on 03/04/2021.
//

#include "circlecollider.h"
#include "vector.h"

Circle::Circle(float x, float y, float r, float mass, float vx, float vy):
position({x, y}), radius(r), mass(mass), velocity({vx, vy})
{

}


bool circlecollisions::are_touching(Circle circle1, Circle circle2)
{
    return ((circle1.position - circle2.position).squarelen() < pow(circle1.radius + circle2.radius, 2));
}

void circlecollisions::collision(Circle &circle1, Circle &circle2, float elasticity)
{
    vector dv = circle1.velocity - circle2.velocity; // distance of circle 1 relative to circle 2
    if (dv.squarelen() < 0.0000001)
        return;

    float d = circle1.radius + circle2.radius; // distance that they should have
    float t = (d - (circle1.position -circle2.position).len()) / dv.len(); // time since collision

    // go back to moment of collision
    circle1.position -= circle1.velocity * t;
    circle2.position -= circle2.velocity * t;

    vector vecd = circle2.position - circle1.position; // vector from circle1 to circle 2 center to center vecd.len() should be d

    vector vpar = vecd * ((vecd * dv) / (d*d)); // velocity parallel to distance vector
    vector vprp =  dv - vpar; // velocity perpendicular to distance vector

    vector vp1 = vpar * (circle1.mass - elasticity * circle2.mass) / (circle1.mass + circle2.mass); // new vpar for circle 1
    vector vp2 = vpar * (circle1.mass + elasticity * circle1.mass) / (circle1.mass + circle2.mass); // new vpar for circle 2

    circle1.velocity = vp1 + vprp + circle2.velocity;
    circle2.velocity = vp2 + vprp + circle2.velocity;

    // we progress by the amount of time since the collision
    circle1.position += circle1.velocity * t;
    circle2.position += circle2.velocity * t;

    return;
}

/**
 *
 */


