#ifndef DIELECTRICH
#define DIELECTRICH

#include "material.h"

class dielectric: public material{
    public:
    float ref_idx;

    dielectric(float ri): ref_idx(ri) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        attenuation = vec3(1.0, 1.0, 1.0);

        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        vec3 refracted;

        float ni_over_nt;
        float reflect_prob;
        float cosine;

        if(dot(r_in.direction(), rec.normal) > 0) {
            // When ray shoots through object back into vacuum
            // ni_over_nt = ref_idx, surface normal has to be inverted
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = dot(unit_vector(r_in.direction()), rec.normal);
        } else {
            // When ray shoots into object
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(unit_vector(r_in.direction()), rec.normal);
        }

        if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            // Refracted ray exists
            reflect_prob = schlick(cosine, ref_idx);
        } else {
            // Refracted ray does not exist => total reflection
            reflect_prob = 1.0;
        }

        if(get_random_number() < reflect_prob) {
            scattered = ray(rec.p, reflected);
        } else {
            scattered = ray(rec.p, refracted);
        }

        return true;
    }

};

#endif