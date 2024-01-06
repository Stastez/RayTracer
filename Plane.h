#pragma once
#include "Geometry.h"

namespace RayTracer {

class Plane : public Geometry {
protected:
    glm::vec3 origin;
    glm::vec3 normal;

public:
    Plane();
    explicit Plane(const glm::vec3& color, float metalness);
    Plane(const glm::vec3& origin, const glm::vec3& normal);
    Plane(const glm::vec3& origin, const glm::vec3& normal, const glm::vec3& color, float metalness);
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
    [[nodiscard]] Ray reflectRay(const Ray& ray, const Intersection& intersection) const override;
};

} // RayTracer
