#pragma once
#include "Plane.h"

namespace RayTracer {

class Rectangle final : public Plane {
protected:
    glm::vec3 point1, point2, point3;
    glm::vec3 xAxis, yAxis;

public:
    Rectangle();
    Rectangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
    Rectangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3, const glm::vec3& color, float metalness);
    [[nodiscard]] Intersection intersect(const Ray& ray) const override;
};

} // RayTracer
