#pragma once

#include <memory>

#include "Geometry.h"

#include <vector>

namespace RayTracer {

class Scene {
private:
    std::vector<std::unique_ptr<Geometry>> objects;

public:
    Scene();
    explicit Scene(std::vector<std::unique_ptr<Geometry>>&& objects);
    [[nodiscard]] Intersection intersect(const Ray& ray) const;
    void addObject(Geometry* object);
    void addObjects(std::vector<std::unique_ptr<Geometry>>&& objects);
    void setObjects(std::vector<std::unique_ptr<Geometry>>&& objects);
};

} // RayTracer
