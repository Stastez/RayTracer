#include "Sphere.h"

#include <iostream>

namespace RayTracer {

    Sphere::Sphere() : center({0, 0, 0}), radius(1) {}

    Sphere::Sphere(const glm::vec3& center, const float radius) : center(center), radius(radius) {}

    Intersection Sphere::intersect(const Ray& ray) const
    {
        // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

        const float uoc = glm::dot(ray.getDirection(), ray.getOrigin() - center);
        const float ocLength = glm::length(ray.getOrigin() - center);
        const float delta = (uoc * uoc) - ((ocLength * ocLength) - (radius * radius));

        if (delta < 0) return {false, {}, std::numeric_limits<float>::infinity()};

        const float deltaSqrt = std::sqrt(delta);
        const float d1 = -uoc + deltaSqrt;

        if (delta == 0) return {true, ray.getOrigin() + d1 * ray.getDirection(), d1};

        const float d2 = -uoc - deltaSqrt;

        if (d1 < 0 && d2 < 0) return {false, {}, std::numeric_limits<float>::infinity()};
        else if (d1 < 0) return {true, ray.getOrigin() + d2 * ray.getDirection(), d2};
        else if (d2 < 0) return {true, ray.getOrigin() + d1 * ray.getDirection(), d1};

        return (d1 - d2 <= 0) ? Intersection{true, ray.getOrigin() + d1 * ray.getDirection(), d1} : Intersection{true, ray.getOrigin() + d2 * ray.getDirection(), d2};
    }

} // RayTracer