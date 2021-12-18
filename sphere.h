//
// Created by Sandrino Becirbegovic on 18.12.21.
//

#pragma once

#include "hittable.h"
#include "Vec3.h"

class sphere : public hittable
{
public:
    sphere() = default;
    sphere( point3 cen, double r ) : center{cen}, radius{r} {};

    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;
    double radius;
};

bool sphere::hit(const Ray &r, double t_min, double t_max, hit_record &rec) const
{
    Vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if ( root < t_min || t_max < root )
    {
        root = (-half_b + sqrtd) / a;
        if ( root < t_min || t_max < root )
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = ( rec.p - center ) / radius;

    return true;
}

