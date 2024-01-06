#pragma once

#include "ConfigReader.h"
#include "ConfigReader.h"
#include "ConfigReader.h"
#include "Picture.h"
#include "Scene.h"

namespace RayTracer {

class RayCaster {
private:
    [[nodiscard]] static glm::vec3 castRay(const Ray& ray, const Scene& scene, unsigned maxBounces);
    static void calculatePixel(unsigned x, unsigned y, unsigned numSamples, const Scene& scene, const Config& config, Picture& pic);
public:
    [[nodiscard]] static Picture castRays(Config& config, unsigned numSamples, unsigned numThreads);
};

} // RayTracer
