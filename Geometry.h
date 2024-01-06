#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace RayTracer {

struct Intersection
{
    bool exists;
    glm::vec3 position;
    float distance;
    glm::vec3 color;
};

class Geometry
{
protected:
    glm::vec3 color = {0.3, 0.3, 0.3};

public:
    Geometry();
    explicit Geometry(const glm::vec3& color) : color(color) {};
    virtual ~Geometry() = default;
    [[nodiscard]] virtual Intersection intersect(const Ray& ray) const = 0;
};

} // RayTracer
