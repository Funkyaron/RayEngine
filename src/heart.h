#ifndef HEARTH
#define HEARTH

#include "hitable.h"
#include "ellipsoid.h"

class heart: public hitable {
    public:
    ellipsoid* right_half;
    ellipsoid* left_half;
    material* mat_ptr;

    heart() {}
    heart(material* mat) {
        right_half = new ellipsoid(vec3(3.2,2.5,0), vec3(0,2.5,0), vec3(0,0,1.5), mat);
        left_half = new ellipsoid(vec3(-3.2,2.5,0), vec3(0,2.5,0), vec3(0,0,1.5), mat);
        mat_ptr = mat;
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

bool heart::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    if(right_half->hit(r, t_min, t_max, rec) && rec.p.x() >= 0) {
        return true;
    } else if (left_half->hit(r, t_min, t_max, rec) && rec.p.x() <= 0) {
        return true;
    } else {
        return false;
    }
}

#endif