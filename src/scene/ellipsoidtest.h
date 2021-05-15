#ifndef SCENE_GENERATOR
#define SCENE_GENERATOR

#include "../geometry/sphere.h"
#include "../geometry/ellipsoid.h"
#include "../geometry/hitable_list.h"
#include "../material/lambert.h"
#include "../material/metal.h"
#include "../material/dielectric.h"

hitable* make_scene() {
    hitable** list = new hitable*[4];
    list[0] = new sphere(vec3(0,-101,0), 100, new lambert(vec3(0.3,0.7,0)));
    list[1] = new sphere(vec3(3,0,0), 1, new metal(vec3(0.3,0.3,0.1), 0.1));
    list[2] = new sphere(vec3(-3,0,0), 1, new lambert(vec3(0.9,0.9,1)));
    //list[3] = new sphere(vec3(0,0,0), 1, new metal(vec3(0.5,0.5,0.5),0.1));
    list[3] = new ellipsoid(vec3(2,0,3), vec3(0,1,0), vec3(1,0,-0.5), new dielectric(1.5));
    hitable* world = new hitable_list(list,4);
    return world;
}

#endif