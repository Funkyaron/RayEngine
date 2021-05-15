#ifndef UTILH
#define UTILH

#include "vec3.h"

float get_random_number() {
    return float(std::rand() % RAND_MAX) / float(RAND_MAX);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(get_random_number(), get_random_number(), get_random_number()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

vec3 random_in_unit_disc() {
    vec3 p;
    do {
        p = 2 * vec3(get_random_number(), get_random_number(), 0) - vec3(1,1,0);
    } while (dot(p,p) >= 1.0);
    return p;
}

#endif