#pragma once

#include "Hitable.hpp"

class HitableList : public Hitable
{
public:
    Hitable **list;
    int size;
public:
    HitableList();
    HitableList(Hitable **list, int n);

    virtual bool hit(const Ray& r, f32 tMin, f32 tMax, HitRecord& rec) const;
};
