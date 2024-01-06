#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace RayTracer {

struct Intersection
{
    bool exists;
    glm::vec3 position;
    float distance;
};

class Geometry
{
public:
    virtual ~Geometry() = default;
    [[nodiscard]] virtual Intersection intersect(const Ray& ray) const = 0;
};

} // RayTracer
