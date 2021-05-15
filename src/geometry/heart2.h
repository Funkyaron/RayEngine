#ifndef HEART2H
#define HEART2H

#include "hitable.h"

class heart2: public hitable {
    public:
    vec3 f1_r, f2_r, f3_r, f1_l, f2_l, f3_l;
    material* mat_ptr;

    heart2() {}
    heart2(material* mat) {
        f1_r = vec3(3.2,2.5,0);
        f1_l = vec3(-3.2,2.5,0);
        f2_r = f2_l = vec3(0,2.5,0);
        f3_r = f3_l = vec3(0,0,1.5);
        mat_ptr = mat;
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 get_normal(vec3 p, vec3 f1, vec3 f2, vec3 f3) const;
};

bool heart2::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

    float dir_f2_f3_r = dot(r.direction(), cross(f2_r, f3_r));
    float dir_f3_f1_r = dot(r.direction(), cross(f3_r, f1_r));
    float dir_f1_f2_r = dot(r.direction(), cross(f1_r, f2_r));

    float or_f2_f3_r = dot(r.origin(), cross(f2_r, f3_r));
    float or_f3_f1_r = dot(r.origin(), cross(f3_r, f1_r));
    float or_f1_f2_r = dot(r.origin(), cross(f1_r, f2_r));

    float f1_f2_f3_r = dot(f1_r, cross(f2_r, f3_r));
    
    float a_r = dir_f2_f3_r * dir_f2_f3_r + dir_f3_f1_r * dir_f3_f1_r + dir_f1_f2_r * dir_f1_f2_r;
    float b_r = 2 * (dir_f2_f3_r * or_f2_f3_r + dir_f3_f1_r * or_f3_f1_r + dir_f1_f2_r * or_f1_f2_r);
    float c_r = or_f2_f3_r * or_f2_f3_r + or_f3_f1_r * or_f3_f1_r + or_f1_f2_r * or_f1_f2_r - f1_f2_f3_r * f1_f2_f3_r;

    float discriminant_r = b_r*b_r - 4*a_r*c_r;
    if(discriminant_r > 0) {
        float temp = (-b_r - sqrt(b_r*b_r - 4*a_r*c_r))/(2*a_r);
        if(temp < t_max && temp > t_min) {
            vec3 point = r.point_at_parameter(temp);
            if(point.x() >= 0) {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                vec3 rec_point = r.point_at_parameter(rec.t);
                rec.normal = get_normal(rec_point, f1_r, f2_r, f3_r);
                rec.mat_ptr = mat_ptr;
                return true;
            }
        } else {
            temp = (-b_r + sqrt(b_r*b_r - 4*a_r*c_r))/(2*a_r);
            if(temp < t_max && temp > t_min) {
                vec3 point = r.point_at_parameter(temp);
                if(point.x() >= 0) {
                    rec.t = temp;
                    rec.p = r.point_at_parameter(rec.t);
                    vec3 rec_point = r.point_at_parameter(rec.t);
                    rec.normal = get_normal(rec_point, f1_r, f2_r, f3_r);
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }
        }
    }

    float dir_f2_f3_l = dot(r.direction(), cross(f2_l, f3_l));
    float dir_f3_f1_l = dot(r.direction(), cross(f3_l, f1_l));
    float dir_f1_f2_l = dot(r.direction(), cross(f1_l, f2_l));

    float or_f2_f3_l = dot(r.origin(), cross(f2_l, f3_l));
    float or_f3_f1_l = dot(r.origin(), cross(f3_l, f1_l));
    float or_f1_f2_l = dot(r.origin(), cross(f1_l, f2_l));

    float f1_f2_f3_l = dot(f1_l, cross(f2_l, f3_l));
    
    float a_l = dir_f2_f3_l * dir_f2_f3_l + dir_f3_f1_l * dir_f3_f1_l + dir_f1_f2_l * dir_f1_f2_l;
    float b_l = 2 * (dir_f2_f3_l * or_f2_f3_l + dir_f3_f1_l * or_f3_f1_l + dir_f1_f2_l * or_f1_f2_l);
    float c_l = or_f2_f3_l * or_f2_f3_l + or_f3_f1_l * or_f3_f1_l + or_f1_f2_l * or_f1_f2_l - f1_f2_f3_l * f1_f2_f3_l;

    float discriminant_l = b_l*b_l - 4*a_l*c_l;
    if(discriminant_l > 0) {
        float temp = (-b_l - sqrt(b_l*b_l - 4*a_l*c_l))/(2*a_l);
        if(temp < t_max && temp > t_min) {
            vec3 point = r.point_at_parameter(temp);
            if(point.x() <= 0) {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                vec3 rec_point = r.point_at_parameter(rec.t);
                rec.normal = get_normal(rec_point, f1_l, f2_l, f3_l);
                rec.mat_ptr = mat_ptr;
                return true;
            }
        } else {
            temp = (-b_l + sqrt(b_l*b_l - 4*a_l*c_l))/(2*a_l);
            if(temp < t_max && temp > t_min) {
                vec3 point = r.point_at_parameter(temp);
                if(point.x() <= 0) {
                    rec.t = temp;
                    rec.p = r.point_at_parameter(rec.t);
                    vec3 rec_point = r.point_at_parameter(rec.t);
                    rec.normal = get_normal(rec_point, f1_l, f2_l, f3_l);
                    rec.mat_ptr = mat_ptr;
                    return true;
                }
            }
        }
    }

    return false;
}

vec3 heart2::get_normal(vec3 p, vec3 f1, vec3 f2, vec3 f3) const {
    float p_f2_f3 = dot(p, cross(f2,f3));
    float p_f3_f1 = dot(p, cross(f3,f1));
    float p_f1_f2 = dot(p, cross(f1,f2));

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