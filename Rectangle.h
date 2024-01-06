#pragma once
#include "Plane.h"

namespace RayTracer {

class Rectangle final : public Plane {
protected:
    glm::vec2 size;
    glm::vec3 xAxis, yAxis;

public:
    Rectangle();
    Rectangle(const glm::vec3& origin, const glm::vec3& xAxis, const glm::vec3& yAxis, const glm::vec2& size);
    Intersection intersect(const Ray& ray) override;
};

} // RayTracer
