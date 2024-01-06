#pragma once

#include "ConfigReader.h"
#include "ConfigReader.h"
#include "ConfigReader.h"
#include "Picture.h"
#include "Scene.h"

namespace RayTracer {

class RayCaster {
private:
    [[nodiscard]] static glm::vec3 castRay(const Ray& ray, const Scene& scene, const unsigned maxBounces);
public:
    [[nodiscard]] static Picture castRays(Config& config, const unsigned numSamples);
};

} // RayTracer
