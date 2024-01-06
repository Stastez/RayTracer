#pragma once
#include "Geometry.h"

namespace RayTracer {

class Plane : public Geometry {
protected:
    glm::vec3 origin;
    glm::vec3 normal;

public:
    Plane();
    explicit Plane(const glm::vec3& color);
    Plane(const glm::vec3& origin, const glm::vec3& normal);
    Plane(const glm::vec3& origin, const glm::vec3& normal, const glm::vec3& color);
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
};

} // RayTracer
