#pragma once

#include "ConfigReader.h"
#include "Picture.h"
#include "Scene.h"

namespace RayTracer {

class RayCaster {
private:
    [[nodiscard]] static glm::vec3 castRay(const Ray& ray, const Scene& scene, unsigned maxBounces);
    static void calculatePixels(unsigned start, unsigned end, unsigned numSamples, unsigned maxBounces, unsigned thread, const Scene& scene, const Config& config, Picture& pic, std::vector<float>& completion);
    static void displayCompletion(std::vector<float>& completion);
public:
    [[nodiscard]] static Picture castRays(Config& config, unsigned numSamples, unsigned numThreads, unsigned maxBounces);
};

} // RayTracer
