#pragma once

#include "Geometry.h"

#include <vector>

namespace RayTracer {

class Scene final : public Geometry {
private:
    std::vector<Geometry*> objects;

public:
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
    void addObject(Geometry* object);
    void addObjects(const std::initializer_list<Geometry*>& objects);
};

} // RayTracer
