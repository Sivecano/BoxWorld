//
// Created by sivecano on 14/04/2021.
//

#ifndef BOXWORLD_VECTOR_H
#define BOXWORLD_VECTOR_H
#include "cmath"

struct vector {
    float x;
    float y;

    vector(): x(0), y(0)
    {
    }

    vector(float x, float y) : x(x), y(y)
    {

    }

    float len() const
    {
        return sqrt(x*x + y*y);
    }

    float squarelen() const
    {
        return x*x + y*y;
    }

    vector unit() const
    {
        return *this / len();
    }


    /// operations with other vectors that return vectors
    vector operator + (vector other) const
    {
        return {x + other.x, y + other.y};
    }

    vector operator - (vector other) const
    {
        return {x - other.x, y - other.y};
    }

    void operator +=(vector other)
    {
        x += other.x;
        y += other.y;
    }

    void operator -=(vector other)
    {
        x -= other.x;
        y -= other.y;
    }


    /// operations with other vector that returns float
    float operator * (vector other) const  // dot product
    {
        return x * other.x + y * other.y;
    }

    /// operations with scalars
    vector operator *(float scale) const // scalar multiple
    {
        return {x * scale, y * scale};
    }
    vector operator / (float scale) const
    {
        return {x / scale, y / scale};
    }

    void operator *=(float scale)
    {
        x *= scale;
        y *= scale;
    }

    void operator /=(float scale)
    {
        x /= scale;
        y /= scale;
    }

};

vector cross(vector vec1, vector vec2); // cross product





#endif //BOXWORLD_VECTOR_H
