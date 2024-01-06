#include "Rectangle.h"

namespace RayTracer {

    Rectangle::Rectangle() : Plane({0.5, 0.5, 0}, {0, 0, 1}), point1({0, 0, 0}), point2({1, 0, 0}), point3({0, 1, 0}), xAxis({0.5, 0, 0}), yAxis({0, 0.5, 0}) {}

    Rectangle::Rectangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3) :
        point1(point1),
        point2(point2),
        point3(point3),
        xAxis((point2 - point1) * 0.5f),
        yAxis((point3 - point1) * 0.5f)
    {
        origin = point1 + xAxis + yAxis;
        normal = glm::cross(xAxis, yAxis);
    }

    Rectangle::Rectangle(const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3, const glm::vec3& color) :
        Plane(color),
        point1(point1),
        point2(point2),
        point3(point3),
        xAxis((point2 - point1) * 0.5f),
        yAxis((point3 - point1) * 0.5f)
    {
        origin = point1 + xAxis + yAxis;
        normal = glm::cross(xAxis, yAxis);
    }

    Intersection Rectangle::intersect(const Ray& ray) const
    {
        const auto possibleIntersection = Plane::intersect(ray);

        if (!possibleIntersection.exists) return possibleIntersection;

        const auto differenceFromOrigin = possibleIntersection.position - origin;

        const auto xAxisProjection = glm::dot(xAxis, differenceFromOrigin) / glm::dot(xAxis, xAxis) * xAxis;
        const auto yAxisProjection = glm::dot(yAxis, differenceFromOrigin) / glm::dot(yAxis, yAxis) * yAxis;

        return (glm::length(xAxisProjection) <= glm::length(xAxis) && glm::length(yAxisProjection) <= glm::length(yAxis)) ? possibleIntersection : Intersection{false, possibleIntersection.position, possibleIntersection.distance, color};
    }

} // RayTracer