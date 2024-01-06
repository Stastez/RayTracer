#include "Rectangle.h"

namespace RayTracer {

    Rectangle::Rectangle() : size(glm::vec2()), xAxis(glm::vec3(1, 0 ,0)), yAxis(glm::cross(xAxis, normal)) {}

    Rectangle::Rectangle(const glm::vec3& origin, const glm::vec3& xAxis, const glm::vec3& yAxis, const glm::vec2& size) : Plane(origin, glm::cross(xAxis, yAxis)), size(size), xAxis(glm::normalize(xAxis)), yAxis(glm::normalize(yAxis)) {}

    Intersection Rectangle::intersect(const Ray& ray)
    {
        const auto possibleIntersection = Plane::intersect(ray);

        if (!possibleIntersection.exists) return possibleIntersection;

        const auto difference = glm::abs(possibleIntersection.position - origin);
        const auto movement = possibleIntersection.position - origin;
        const auto xAxisComponent = glm::abs(glm::dot(xAxis, movement));
        const auto yAxisComponent = glm::abs(glm::dot(yAxis, movement));

        return (xAxisComponent < size.x / 2 && yAxisComponent < size.y / 2) ? possibleIntersection : Intersection{false, possibleIntersection.position};
    }


} // RayTracer