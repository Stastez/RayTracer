#include "Ray.h"

namespace RayTracer {

    Ray::Ray() : origin({0, 0, 0}), direction({0, 0, 1}) {}

    Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(glm::normalize(direction)) {}

    glm::vec3 Ray::getDirection() const
    {
        return direction;
    }

    glm::vec3 Ray::getOrigin() const
    {
        return origin;
    }


} // RayTracer