#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace RayTracer {

struct Intersection
{
    bool exists;
    glm::vec3 position;
};

class Geometry
{
public:
    virtual ~Geometry() = default;
    virtual Intersection intersect(const Ray& ray) = 0;
};

} // RayTracer
