#include <iostream>
#include <cfloat>
#include "ray.h"
#include "triangle.h"

int main() {
    vec3 p1 = vec3(0.4, -0.4, -1.5);
    vec3 p2 = vec3(0.0, 0.4, -2.0);
    vec3 p3 = vec3(-0.4, -0.4, -2.5);
    ray r = ray(vec3(0.0, 0.0, 0.0), vec3(-0.1, 0.0, -1.0) - vec3(0.0, 0.0, 0.0));

    vec3 v1 = p2 - p1;
    vec3 v2 = p3 - p1;

    vec3 normal = unit_vector(cross(v1,v2));
    std::cout << "Normal: " << normal << "\n";

    float t = 0;
    if(dot(r.direction(), normal) != 0) {
        t = dot((p1 - r.origin()), normal) / dot(r.direction(), normal);
    }

    vec3 hit_point = r.point_at_parameter(t);
    std::cout << "Hitpoint: " << hit_point << "\n";

    

    /*hitable* tri = new triangle(p1, p2, p3);
    hit_record rec;
    if(tri->hit(r, 0.001, FLT_MAX, rec)) {
        std::cout << "Normal: " << rec.normal << "\n";
        std::cout << "Hitpoint: " << rec.p << "\n";
    } else {
        std::cout << "No hit\n";
    }*/
}