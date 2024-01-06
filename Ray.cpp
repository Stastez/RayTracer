#include "Ray.h"

namespace RayTracer {

    Ray::Ray() : origin({0, 0, 0}), direction({0, 0, 1}) {}

    Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(glm::normalize(direction)) {}

    void Ray::deviateVec(glm::vec3& vec, float magnitude)
    {
        const auto deviation = glm::vec3{randomFloat(magnitude), randomFloat(magnitude), randomFloat(magnitude)};
        vec += deviation;
    }

    void Ray::deviate(const float magnitude)
    {
        deviateDirection(magnitude);
        deviateOrigin(magnitude);
    }

    void Ray::deviateDirection(float magnitude)
    {
        deviateVec(direction, magnitude);
    }

    void Ray::deviateOrigin(float magnitude)
    {
        deviateVec(origin, magnitude);
    }

    glm::vec3 Ray::getDirection() const
    {
        return direction;
    }

    glm::vec3 Ray::getOrigin() const
    {
        return origin;
    }

    float Ray::randomFloat(const float max)
    {
        return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
    }

} // RayTracer