#pragma once

#include "ConfigReader.h"
#include "Picture.h"
#include "Scene.h"
#include "ThreadSafeQueue.h"

namespace RayTracer {

class RayCaster {
private:
    [[nodiscard]] static glm::vec3 castRay(const Ray& ray, const Scene& scene, unsigned maxBounces);
    static void calculatePixels(unsigned numSamples, unsigned maxBounces, unsigned thread, const Scene& scene, const Config& config, Picture& pic, ThreadSafeQueue& queue);
    static void displayCompletion(const ThreadSafeQueue& queue, unsigned pixelCount);
public:
    [[nodiscard]] static Picture castRays(Config& config, unsigned numSamples, unsigned numThreads, unsigned maxBounces);
};

} // RayTracer
