#ifndef ELLIPSOIDH
#define ELLIPSOIDH

#include "hitable.h"

class ellipsoid: public hitable {
    public:
    vec3 f1;
    vec3 f2;
    vec3 f3;
    material* mat_ptr;

    ellipsoid() {}
    ellipsoid(vec3 _f1, vec3 _f2, vec3 _f3, material* mat) {
        f1 = _f1;
        f2 = _f2;
        f3 = _f3;
        mat_ptr = mat;
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 get_normal(vec3 p) const;
};

bool ellipsoid::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

    float dir_f2_f3 = dot(r.direction(), cross(f2, f3));
    float dir_f3_f1 = dot(r.direction(), cross(f3, f1));
    float dir_f1_f2 = dot(r.direction(), cross(f1, f2));

    float or_f2_f3 = dot(r.origin(), cross(f2, f3));
    float or_f3_f1 = dot(r.origin(), cross(f3, f1));
    float or_f1_f2 = dot(r.origin(), cross(f1, f2));

    float f1_f2_f3 = dot(f1, cross(f2, f3));
    
    float a = dir_f2_f3 * dir_f2_f3 + dir_f3_f1 * dir_f3_f1 + dir_f1_f2 * dir_f1_f2;
    float b = 2 * (dir_f2_f3 * or_f2_f3 + dir_f3_f1 * or_f3_f1 + dir_f1_f2 * or_f1_f2);
    float c = or_f2_f3 * or_f2_f3 + or_f3_f1 * or_f3_f1 + or_f1_f2 * or_f1_f2 - f1_f2_f3 * f1_f2_f3;

    float discriminant = b*b - 4*a*c;
    if(discriminant > 0) {
        float temp = (-b - sqrt(b*b - 4*a*c))/(2*a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            //rec.normal = unit_vector(rec.p); // This is wrong, but we'll figure that out
            vec3 rec_point = r.point_at_parameter(rec.t);
            rec.normal = get_normal(rec_point);
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b*b - 4*a*c))/(2*a);
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            //rec.normal = unit_vector(rec.p); // Dito
            vec3 rec_point = r.point_at_parameter(rec.t);
            rec.normal = get_normal(rec_point);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

vec3 ellipsoid::get_normal(vec3 point) const {

    float p_f2_f3 = dot(point, cross(f2,f3));
    float p_f3_f1 = dot(point, cross(f3,f1));
    float p_f1_f2 = dot(point, cross(f1,f2));

    vec3 result = vec3((f2.y() * f3.z() - f2.z() * f3.y()) * 2 * p_f2_f3
        + (f3.y() * f1.z() - f3.z() * f1.y()) * 2 * p_f3_f1
        + (f1.y() * f2.z() - f1.z() * f2.y()) * 2 * p_f1_f2,
    (f2.z() * f3.x() - f2.x() * f3.z()) * 2 * p_f2_f3
        + (f3.z() * f1.x() - f3.x() * f1.z()) * 2 * p_f3_f1
        + (f1.z() * f2.x() - f1.x() * f2.z()) * 2 * p_f1_f2,
    (f2.x() * f3.y() - f2.y() * f3.x()) * 2 * p_f2_f3
        + (f3.x() * f1.y() - f3.y() * f1.x()) * 2 * p_f3_f1
        + (f1.x() * f2.y() - f1.y() * f2.x()) * 2 * p_f1_f2);
    
    return unit_vector(result);
}

#endif