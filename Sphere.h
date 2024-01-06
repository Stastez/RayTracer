#pragma once

#include "Geometry.h"

namespace RayTracer {

class Sphere : public Geometry {
protected:
    glm::vec3 center;
    float radius;

public:
    Sphere();
    Sphere(const glm::vec3& center, float radius);
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
};

} // RayTracer
