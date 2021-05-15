#ifndef SCENE_GENERATOR
#define SCENE_GENERATOR

#include "../geometry/sphere.h"
#include "../geometry/hitable_list.h"
#include "../material/lambert.h"
#include "../material/metal.h"
#include "../material/dielectric.h"
#include "../util.h"

hitable* make_scene() {
    int n = 500;
    hitable** list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,-1000,0), 1000, new lambert(vec3(0.5,0.5,0.5)));
    int i = 1;
    for(int a = -11; a < 11; a++) {
        for(int b = -11; b < 11; b++) {
            float choose_mat = get_random_number();
            vec3 center(a + 0.9 * get_random_number(), 0.2, b + 0.9 * get_random_number());
            if ((center - vec3(4,0.2,0)).length() > 0.9) {
                if(choose_mat < 0.8) {
                    list[i++] = new sphere(center, 0.2, new lambert(vec3(get_random_number() * get_random_number(), get_random_number() * get_random_number(), get_random_number() * get_random_number())));
                }
                else if (choose_mat < 0.95) {
                    list[i++] = new sphere(center, 0.2,
                        new metal(vec3(0.5 * (1 + get_random_number()), 0.5 * (1 + get_random_number()), 0.5 * (1 + get_random_number())), 0.5 * get_random_number()));
                }
                else {
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4,1,0), 1.0, new lambert(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4,1,0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    hitable* world = new hitable_list(list, i);
    return world;
}

#endif