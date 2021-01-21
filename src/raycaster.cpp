#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "triangle.h"
#include "camera.h"
#include "lambert.h"
#include "metal.h"
#include <cfloat>
#include <stdlib.h>
//#include <cstdlib>

//float r = static_cast <float> (std::rand() % RAND_MAX) / static_cast <float> (RAND_MAX);
/*float get_random_number() {
    return float(std::rand() % RAND_MAX) / float(RAND_MAX);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(get_random_number(), get_random_number(), get_random_number()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}*/

vec3 color(const ray& r, hitable* world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0,0,0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    hitable* list[4];
    //list[0] = new sphere(vec3(0,0,-1),0.5);
    //list[0] = new triangle(vec3(0.0, -0.5, -1.5), vec3(0.5, 0.5, -1), vec3(-0.4, 0.4, -0.5));
    //list[1] = new sphere(vec3(0,-100.5,-1),100);
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambert(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambert(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2)));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8,0.8,0.8)));
    hitable* world = new hitable_list(list,4);

    camera cam;

    for(int j = ny-1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < ns; s++) {
                float u = float(i + get_random_number()) / float(nx);
                float v = float(j + get_random_number()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(ns);
            // Gamma correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}