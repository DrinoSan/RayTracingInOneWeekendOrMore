//
// Created by Sandrino Becirbegovic on 18.12.21.
//

#pragma once

#include "Ray.h"

struct hit_record
{
    point3      p;
    Vec3        normal;
    double      t;
};

class hittable
{
public:
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
