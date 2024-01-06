#pragma once

#include "Geometry.h"

namespace RayTracer {

class Sphere final : public Geometry {
protected:
    glm::vec3 center;
    float radius;

public:
    Sphere();
    Sphere(const glm::vec3& center, float radius);
    Sphere(const glm::vec3& center, float radius, const glm::vec3& color);
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
};

} // RayTracer
