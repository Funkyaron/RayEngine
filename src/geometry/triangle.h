#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.h"

class triangle: public hitable {
    public:
    vec3 p1;
    vec3 p2;
    vec3 p3;
    material* mat_ptr;

    triangle() {}
    triangle(vec3 _p1, vec3 _p2, vec3 _p3, material* _mat) {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;
        mat_ptr = _mat;
        normal = unit_vector(cross(p2 - p1, p3 - p1));
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    private:
    vec3 normal;
    bool point_in_polygon(vec3 hit_point) const;
    
};

bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    float numerator = dot((p1 - r.origin()), normal);
    float denominator = dot(r.direction(), normal);
    if(denominator == 0) {
        return false;
    }
    //At first only check for the plane in which the triangle lies
    float t = numerator / denominator;
    if(t >= t_min && t <= t_max) {
        if(point_in_polygon(r.point_at_parameter(t))) {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = normal;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

bool triangle::point_in_polygon(vec3 hit_point) const {
    vec3 hit_point_1 =  vec3(hit_point.x(), hit_point.y(), 0);

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
            intersections += 1;
        } else if(points[i].x() < 0 && points[(i+1) % 3].x() < 0) {
            //Trivial reject
        } else if(points[i].y() < 0 && points[(i+1) % 3].y() < 0) {
            //Trivial reject
        } else if(points[i].y() > 0 && points[(i+1) % 3].y() > 0) {
            //Trivial reject
        } else if(points[(i+1) % 3].y() == 0 && points[(i+1) % 3].x() > 0) {
            //Target point is on positive x axis. Leave decision for next point
        } else {
            //More intense calculation
            if(points[i].x() > 0 && points[i].y() == 0) {
                //Special case: Point is on the positive x axis
                if(points[(i+2) % 3].y() * points[(i+1) % 3].y() < 0) {
                    //Caution: The index i+2 thing only works for triangles
                    //Real change of sign
                    intersections += 1;
                }
            } else {
                //Intersection of the edge with positive x axis via linear interpolation
                float alpha = (-points[i].y()) / (points[(i+1) % 3].y() - points[i].y());
                vec3 x_intersect = (1-alpha)*points[i] + alpha*points[(i+1) % 3];
                if(x_intersect.x() > 0) {
                    intersections += 1;
                }
            }
        }
    }

    return (intersections % 2 == 1);
}


#endif