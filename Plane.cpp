#include "Plane.h"

namespace RayTracer {

    Plane::Plane() : Plane({0, 0, 0}, {0, 0, 1}){}

    Plane::Plane(const glm::vec3& color, const float metalness) : Plane({0, 0, 0}, {0, 0, 1}, color, metalness) {}

    Plane::Plane(const glm::vec3& origin, const glm::vec3& normal) : Plane(origin, normal, {0.3, 0.3, 0.3}, 0) {}

    Plane::Plane(const glm::vec3& origin, const glm::vec3& normal, const glm::vec3& color, const float metalness) : Geometry(color, metalness), origin(origin), normal(glm::normalize(normal)) {}

    Intersection Plane::intersect(const Ray& ray) const
    {
        const auto directionNormalDot = glm::dot(ray.getDirection(), normal);
        const auto originDifferenceNormalDot = glm::dot(origin - ray.getOrigin(), normal);
        if (directionNormalDot == 0)
        {
            if (originDifferenceNormalDot == 0) return {true, ray.getOrigin(), 0, this};

            return {false, glm::vec3(), std::numeric_limits<float>::infinity(), this};
        }

        const auto rayCoefficient = originDifferenceNormalDot / directionNormalDot;
        if (rayCoefficient < 0) return {false, glm::vec3(), std::numeric_limits<float>::infinity(), this};

        return {true, ray.getOrigin() + rayCoefficient * ray.getDirection(), rayCoefficient, this};
    }

    Ray Plane::reflectRay(const Ray& ray, const Intersection& intersection) const
    {
        const auto thisNormal = glm::normalize(glm::dot(normal, ray.getDirection()) * normal);
        return {intersection.position, glm::reflect(ray.getDirection(), thisNormal)};
    }

} // RayTracer