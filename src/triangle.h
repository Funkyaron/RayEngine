#ifndef TRIANGLEH
#define TRIANGLEH

#include "hitable.h"

class triangle: public hitable {
    public:
    vec3 p1;
    vec3 p2;
    vec3 p3;

    triangle() {}
    triangle(vec3 _p1, vec3 _p2, vec3 _p3) {
        p1 = _p1;
        p2 = _p2;
        p3 = _p3;
        normal = unit_vector(cross(p2 - p1, p3 - p1));
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    private:
    vec3 normal;
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
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = normal;
        return true;
    }
    return false;
}


#endif