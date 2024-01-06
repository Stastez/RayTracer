#pragma once
#include "Geometry.h"

namespace RayTracer {

class Plane : public Geometry {
protected:
    glm::vec3 origin;
    glm::vec3 normal;

public:
    Plane();
    Plane(const glm::vec3& origin, const glm::vec3& normal);
    Intersection intersect(const Ray& ray) override;
};

} // RayTracer
