#pragma once

#include <glm/glm.hpp>

namespace RayTracer {

class Ray {
private:
    glm::vec3 origin;
    glm::vec3 direction;
    static void deviateVec(glm::vec3& vec, float magnitude);

public:
    Ray();
    Ray(const glm::vec3& origin, const glm::vec3& direction);
    [[nodiscard]] glm::vec3 getOrigin() const;
    [[nodiscard]] glm::vec3 getDirection() const;
    void deviate(float magnitude);
    void deviateOrigin(float magnitude);
    void deviateDirection(float magnitude);
};

} // RayTracer
