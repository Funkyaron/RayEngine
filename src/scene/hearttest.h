#ifndef SCENE_GENERATOR
#define SCENE_GENERATOR

#include "../geometry/sphere.h"
#include "../geometry/heart2.h"
#include "../geometry/hitable_list.h"
#include "../material/lambert.h"
#include "../material/metal.h"
#include "../material/dielectric.h"

hitable* make_scene() {
    hitable** list = new hitable*[6];
    //list[0] = new heart(new lambert(vec3(0.9,0.05,0.05)));
    //list[0] = new heart2(new metal(vec3(0.5,0.5,0.5), 0.1));
    list[0] = new heart2(new dielectric(1.5));
    list[1] = new sphere(vec3(2.5,0,2.5), 0.5, new lambert(vec3(1,0,0)));
    list[2] = new sphere(vec3(2.5,0,-2.5), 0.5, new lambert(vec3(0,1,0)));
    list[3] = new sphere(vec3(-2.5,0,2.5), 0.5, new lambert(vec3(0,0,1)));
    list[4] = new sphere(vec3(-2.5,0,-2.5), 0.5, new lambert(vec3(0.9,0.9,0.9)));
    list[5] = new sphere(vec3(0,-103,0), 100, new metal(vec3(0.4,0.4,0.4), 0.1));
    hitable* world = new hitable_list(list,6);
    return world;
}

#endif