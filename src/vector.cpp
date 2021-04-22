//
// Created by sivecano on 14/04/2021.
//

#include "vector.h"

vector cross (vector vec1, vector vec2)
{
    return vector(vec1.x * vec2.y - vec1.y * vec2.y,  vec1.y * vec2.y - vec1.x * vec2.y);
}
