#include "Scene.h"

#include <utility>

namespace RayTracer {

    Scene::Scene() : Geometry({std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()}) {};

    Scene::Scene(std::vector<std::unique_ptr<Geometry>>&& objects) : Geometry({std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()}), objects(std::move(objects)) {}

    Intersection Scene::intersect(const Ray& ray) const
    {
        if (objects.empty()) return {false, {}, std::numeric_limits<float>::infinity(), color};

        auto closestIntersection = Intersection{false, {}, std::numeric_limits<float>::infinity(), color};

        for (const auto& object : objects)
        {
            const auto newIntersection = object->intersect(ray);

            if (newIntersection.exists && newIntersection.distance < closestIntersection.distance) closestIntersection = newIntersection;
        }

        return closestIntersection;
    }

    void Scene::addObject(Geometry* const object)
    {
        objects.emplace_back(object);
    }

    void Scene::addObjects(std::vector<std::unique_ptr<Geometry>>&& objects)
    {
        Scene::objects.insert(Scene::objects.end(), std::make_move_iterator(objects.begin()), std::make_move_iterator(objects.end()));
    }

    void Scene::setObjects(std::vector<std::unique_ptr<Geometry>>&& objects)
    {
        Scene::objects = std::move(objects);
    }

} // RayTracer