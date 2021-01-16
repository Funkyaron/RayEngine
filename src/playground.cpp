#include <iostream>
#include <cfloat>
#include "ray.h"
#include "triangle.h"

int main() {
    vec3 p1 = vec3(0.01, -0.4, 2.0);
    vec3 p2 = vec3(0.0, 0.1, -2.0);
    vec3 p3 = vec3(-0.01, -0.4, -6.0);
    ray r = ray(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, -1.0) - vec3(0.0, 0.0, 0.0));

    /*vec3 v1 = p2 - p1;
    vec3 v2 = p3 - p1;

    vec3 normal = unit_vector(cross(v1,v2));
    std::cout << "Normal: " << normal << "\n";

    float t = 0;
    if(dot(r.direction(), normal) != 0) {
        t = dot((p1 - r.origin()), normal) / dot(r.direction(), normal);
    }

    vec3 hit_point = r.point_at_parameter(t);
    std::cout << "Hitpoint: " << hit_point << "\n";

    //Now the real fun begins: Point-in-polygon test!

    //I will try out to always project in 2D along the z axis, no matter which normal component is the biggest

    vec3 hit_point_1 = vec3(hit_point.x(), hit_point.y(), 0);

    vec3 points[3];
    points[0] = vec3(p1.x(), p1.y(), 0);
    points[1] = vec3(p2.x(), p2.y(), 0);
    points[2] = vec3(p3.x(), p3.y(), 0);

    //Imagine hitpoint as origin
    points[0] -= hit_point_1;
    points[1] -= hit_point_1;
    points[2] -= hit_point_1;

    //Count the number of intersections with edges of the polygon
    int intersections = 0;

    for(int i = 0; i < 3; i++) {
        if(points[i].x() > 0 && points[(i+1) % 3].x() > 0 && points[i].y() * points[(i+1) % 3].y() < 0) {
            //Trivial accept
            std::cout << "Trivial accept\n";
            intersections += 1;
        } else if(points[i].x() < 0 && points[(i+1) % 3].x() < 0) {
            //Trivial reject
            std::cout << "Trivial reject\n";
        } else if(points[i].y() < 0 && points[(i+1) % 3].y() < 0) {
            //Trivial reject
            std::cout << "Trivial reject\n";
        } else if(points[i].y() > 0 && points[(i+1) % 3].y() > 0) {
            //Trivial reject
            std::cout << "Trivial reject\n";
        } else if(points[(i+1) % 3].y() == 0 && points[(i+1) % 3].x() > 0) {
            std::cout << "Target point is on positive x axis. Leave decision for next point\n";
        } else {
            //More intense calculation
            if(points[i].x() > 0 && points[i].y() == 0) {
                //Special case: Point is on the positive x axis
                if(points[(i+2) % 3].y() * points[(i+1) % 3].y() < 0) {
                    //Caution: The index i+2 thing only works for triangles
                    //Real change of sign
                    std::cout << "Point is on positive x axis. Intersection because of real change of sign\n";
                    intersections += 1;
                } else {
                    std::cout << "Point is on positive x axis, but there is no intersection\n";
                }
            } else {
                //Intersection of the edge with positive x axis via linear interpolation
                float alpha = (-points[i].y()) / (points[(i+1) % 3].y() - points[i].y());
                vec3 x_intersect = (1-alpha)*points[i] + alpha*points[(i+1) % 3];
                if(x_intersect.x() > 0) {
                    std::cout << "Non-trivial accept\n";
                    intersections += 1;
                } else {
                    std::cout << "Non-trivial reject\n";
                }
            }
        }
    }

    std::cout << "Is point in polygon? ";
    if(intersections % 2 == 1) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
    */
    

    

    hitable* tri = new triangle(p1, p2, p3);
    hit_record rec;
    std::cout << "Is point in polygon? ";
    if(tri->hit(r, 0.001, FLT_MAX, rec)) {
        std::cout << "Yes\n";
        std::cout << "Normal: " << rec.normal << "\n";
        std::cout << "Hitpoint: " << rec.p << "\n";
    } else {
        std::cout << "No\n";
    }
}