#include "HitableList.hpp"

HitableList::HitableList() : list{}, size{} { }

HitableList::HitableList(Hitable **list, int n) : list{list}, size{n} { }

bool HitableList::hit(const Ray& r, f32 tMin, f32 tMax, HitRecord& rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    f32 closestSoFar = tMax;

    for (int i = 0; i < size; i++)
    {
        if (list[i]->hit(r, tMin, closestSoFar, tempRec))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}