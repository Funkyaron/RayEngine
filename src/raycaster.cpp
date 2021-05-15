#include <iostream>
#include "sphere.h"
#include "triangle.h"
#include "ellipsoid.h"
#include "heart.h"
#include "heart2.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambert.h"
#include "metal.h"
#include "dielectric.h"
#include "REImage.h"
#include <cfloat>
#include <stdlib.h>

//#include "../lib/lodepng/lodepng.h"

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

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
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    /*int n = 500;
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
    hitable* world = new hitable_list(list, i);*/

    /*hitable** list = new hitable*[4];
    list[0] = new sphere(vec3(0,-101,0), 100, new lambert(vec3(0.3,0.7,0)));
    list[1] = new sphere(vec3(3,0,0), 1, new metal(vec3(0.3,0.3,0.1), 0.1));
    list[2] = new sphere(vec3(-3,0,0), 1, new lambert(vec3(0.9,0.9,1)));
    //list[3] = new sphere(vec3(0,0,0), 1, new metal(vec3(0.5,0.5,0.5),0.1));
    list[3] = new ellipsoid(vec3(2,0,3), vec3(0,1,0), vec3(1,0,-0.5), new dielectric(1.5));
    hitable* world = new hitable_list(list,4);*/

    /*hitable** list = new hitable*[6];
    //list[0] = new heart(new lambert(vec3(0.9,0.05,0.05)));
    //list[0] = new heart2(new metal(vec3(0.5,0.5,0.5), 0.1));
    list[0] = new heart2(new dielectric(1.5));
    list[1] = new sphere(vec3(2.5,0,2.5), 0.5, new lambert(vec3(1,0,0)));
    list[2] = new sphere(vec3(2.5,0,-2.5), 0.5, new lambert(vec3(0,1,0)));
    list[3] = new sphere(vec3(-2.5,0,2.5), 0.5, new lambert(vec3(0,0,1)));
    list[4] = new sphere(vec3(-2.5,0,-2.5), 0.5, new lambert(vec3(0.9,0.9,0.9)));
    list[5] = new sphere(vec3(0,-103,0), 100, new metal(vec3(0.4,0.4,0.4), 0.1));
    hitable* world = new hitable_list(list,6);*/

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

    vec3 lookfrom(2,3,16);
    vec3 lookat(0,0,0);
    float dist_to_focus = (lookfrom - lookat).length();
    float aperture = 0.1;
    camera cam(lookfrom, lookat, vec3(0,1,0), 60, float(width)/float(height), aperture, dist_to_focus);

    //const char* filename = "test.png";
    //std::vector<unsigned char> image;
    //image.resize(width * height * 4);

    REImage image = REImage(width, height);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            vec3 col(0,0,0);
            for(int s = 0; s < samples; s++) {
                float u = float(x + get_random_number()) / float(width);
                float v = float((height - y - 1) + get_random_number()) / float(height);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world, 0);
            }
            col /= float(samples);
            image.set_pixel(x, y, col);
            /*// Gamma correction
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            image[4 * width * y + 4 * x + 0] = char(255.99 * col[0]);
            image[4 * width * y + 4 * x + 1] = char(255.99 * col[1]);
            image[4 * width * y + 4 * x + 2] = char(255.99 * col[2]);
            image[4 * width * y + 4 * x + 3] = 255; // Alpha

            //std::cout << ir << " " << ig << " " << ib << "\n";*/
        }
    }
    //encodeOneStep(filename, image, width, height);

    //const char* filename = "test.png";
    std::string filename = "test.png";
    image.print_to_png(filename);

    return 0;
}