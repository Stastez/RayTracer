#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

namespace RayTracer {
class Geometry;

struct Intersection
{
    bool exists;
    glm::vec3 position;
    float distance;
    Geometry const * object;
};

class Geometry
{
protected:
    glm::vec3 color = {0.3, 0.3, 0.3};
    float metalness;

public:
    explicit Geometry(const glm::vec3& color, const float metalness) : color(color), metalness(metalness) {};
    virtual ~Geometry() = default;
    [[nodiscard]] virtual Intersection intersect(const Ray& ray) const = 0;
    [[nodiscard]] virtual Ray reflectRay(const Ray& ray, const Intersection& intersection) const = 0;
    [[nodiscard]] glm::vec3 getColor() const { return color; }
    [[nodiscard]] float getMetalness() const { return metalness; }
};

} // RayTracer
