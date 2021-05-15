
#include <iostream>
#include <cfloat>
#include <stdlib.h>

#include "camera.h"
#include "REImage.h"


#include "scene/hearttest.h"


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
    unsigned width = 400;
    unsigned height = 300;
    int samples = 200;
    std::cout << "Hello Image!";


    hitable* world = make_scene();

    vec3 lookfrom(2,3,16);
    vec3 lookat(0,0,0);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0,1,0), 60, float(width)/float(height), aperture, dist_to_focus);

    REImage image = REImage(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            vec3 col(0,0,0);
            for(int s = 0; s < samples; s++) {
                float u = float(x + get_random_number()) / float(width);
                float v = float((height - y - 1) + get_random_number()) / float(height);
                ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(samples);
            image.set_pixel(x, y, col);
        }
    }

    std::string filename = "test.png";
    image.print_to_png(filename);

    return 0;
}