#include "Sphere.h"

namespace RayTracer {

    Sphere::Sphere() : Sphere({0, 0, 0}, 1) {}

    Sphere::Sphere(const glm::vec3& center, const float radius) : Sphere(center, radius, {0.3, 0.3, 0.3}, 0) {}

    Sphere::Sphere(const glm::vec3& center, const float radius, const glm::vec3& color, const float metalness) : Geometry(color, metalness), center(center), radius(radius) {}

    Intersection Sphere::intersect(const Ray& ray) const
    {
        // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

        const float uoc = glm::dot(ray.getDirection(), ray.getOrigin() - center);
        const float ocLength = glm::length(ray.getOrigin() - center);
        const float delta = (uoc * uoc) - ((ocLength * ocLength) - (radius * radius));

        if (delta < 0) return {false, {}, std::numeric_limits<float>::infinity(), this};

        const float deltaSqrt = std::sqrt(delta);
        const float d1 = -uoc + deltaSqrt;

        if (delta == 0) return {true, ray.getOrigin() + d1 * ray.getDirection(), d1, this};

        const float d2 = -uoc - deltaSqrt;

        if (d1 < 0 && d2 < 0) return {false, {}, std::numeric_limits<float>::infinity(), this};
        else if (d1 < 0) return {true, ray.getOrigin() + d2 * ray.getDirection(), d2, this};
        else if (d2 < 0) return {true, ray.getOrigin() + d1 * ray.getDirection(), d1, this};

        return (d1 - d2 <= 0) ? Intersection{true, ray.getOrigin() + d1 * ray.getDirection(), d1, this} : Intersection{true, ray.getOrigin() + d2 * ray.getDirection(), d2, this};
    }

    Ray Sphere::reflectRay(const Ray& ray, const Intersection& intersection) const
    {
        return {intersection.position, glm::reflect(ray.getDirection(), glm::normalize(intersection.position - center))};
    }

} // RayTracer