#include "Scene.h"

namespace RayTracer {

    Intersection Scene::intersect(const Ray& ray) const
    {
        if (objects.empty()) return {false, {}, std::numeric_limits<float>::infinity()};

        auto closestIntersection = Intersection{false, {}, std::numeric_limits<float>::infinity()};

        for (const auto& object : objects)
        {
            const auto newIntersection = object->intersect(ray);

            if (newIntersection.distance < closestIntersection.distance) closestIntersection = newIntersection;
        }

        return closestIntersection;
    }

    void Scene::addObject(Geometry* const object)
    {
        objects.emplace_back(object);
    }

    void Scene::addObjects(const std::initializer_list<Geometry*>& objects)
    {
        Scene::objects.insert(Scene::objects.end(), objects);
    }

} // RayTracer