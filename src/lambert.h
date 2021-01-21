#ifndef LAMBERTH
#define LAMBERTH

#include "material.h"

float get_random_number() {
    return float(std::rand() % RAND_MAX) / float(RAND_MAX);
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(get_random_number(), get_random_number(), get_random_number()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class lambert: public material {
    public:
    vec3 albedo;

    lambert(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }
};

#endif