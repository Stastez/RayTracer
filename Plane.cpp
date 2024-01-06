#include "Plane.h"

namespace RayTracer {

    Plane::Plane() : origin(glm::vec3()), normal(glm::vec3(0, 0, 1)) {}

    Plane::Plane(const glm::vec3& origin, const glm::vec3& normal) : origin(origin), normal(glm::normalize(normal)) {}

    Intersection Plane::intersect(const Ray& ray)
    {
        const auto directionNormalDot = glm::dot(ray.getDirection(), normal);
        const auto originDifferenceNormalDot = glm::dot(origin - ray.getOrigin(), normal);
        if (directionNormalDot == 0)
        {
            if (originDifferenceNormalDot == 0) return {true, ray.getOrigin()};

            return {false, glm::vec3()};
        }

        const auto rayCoefficient = originDifferenceNormalDot / directionNormalDot;
        if (rayCoefficient < 0) return {false, glm::vec3()};

        return {true, ray.getOrigin() + rayCoefficient * ray.getDirection()};
    }


} // RayTracer