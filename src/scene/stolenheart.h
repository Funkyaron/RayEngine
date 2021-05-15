#ifndef SCENE_GENERATOR
#define SCENE_GENERATOR

#include "../geometry/sphere.h"
#include "../geometry/heart2.h"
#include "../geometry/hitable_list.h"
#include "../material/lambert.h"
#include "../material/dielectric.h"
#include "../util.h"

hitable* make_scene() {
    //int n = 400;
    int n = 2;
    hitable** list = new hitable*[n+1];

    float min_rad = 10.0;
    float max_rad = 13.0;
    for(int i = 0; i < n; i++) {
        vec3 center = random_in_unit_sphere();
        float scale = (max_rad - min_rad);
        float delta_s = sqrt( (scale * center.length() * scale * center.length()) / (center.x() * center.x() + center.y() * center.y() + center.z() * center.z()) );
        center = delta_s * center;
        float translate = min_rad;
        float delta_r = sqrt( (translate * translate) / (center.x() * center.x() + center.y() * center.y() + center.z() * center.z()) );
        center = center + delta_r * center;
        list[i] = new sphere(center, 0.6, new dielectric(1.5));
    }
    // -> Smaller spheres, nearer to the heart, let the camera zoom in and maybe a bit less spheres
    list[n] = new heart2(new lambert(vec3(1,0,0)));
    hitable* world = new hitable_list(list, n+1);
    return world;
}

#endif