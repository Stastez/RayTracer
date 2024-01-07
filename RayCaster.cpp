#include "RayCaster.h"

#include <future>
#include <iostream>

#include "ConfigReader.h"

namespace RayTracer {

    Picture RayCaster::castRays(Config& config, const unsigned numSamples, const unsigned numThreads, const unsigned maxBounces)
    {
        Picture pic {config.resolutionX, config.resolutionY};

        const Scene scene {std::move(config.objects)};

        const auto batchSize = config.resolutionX / numThreads;
        std::vector<std::future<void>> threads {numThreads};

        for (auto i = 0u; i < numThreads - 1; ++i)
        {
            threads[i] = std::async(std::launch::async, calculatePixels, i * batchSize, (i + 1) * batchSize + 1, numSamples, maxBounces, std::ref(scene), std::ref(config), std::ref(pic));
        }
        threads[numThreads - 1] = std::async(std::launch::async, calculatePixels, (numThreads - 1) * batchSize, config.resolutionX, numSamples, maxBounces, std::ref(scene), std::ref(config), std::ref(pic));

        for (const auto& thread : threads) thread.wait();

        return pic;
    }

    glm::vec3 RayCaster::castRay(const Ray& ray, const Scene& scene, const unsigned maxBounces)
    {
        auto bounces = 0u;

        auto intersection = scene.intersect(ray);
        auto returnColor = (intersection.exists) ? intersection.object->getColor() : glm::vec3{0};

        while (bounces++ < maxBounces && intersection.exists && intersection.object->getMetalness() > 0 && intersection.distance > 0.01)
        {
            const auto newRay = intersection.object->reflectRay(ray, intersection);
            const float oldMetalness = intersection.object->getMetalness();
            intersection = scene.intersect(newRay);
            returnColor = glm::mix(returnColor, intersection.object->getColor(), oldMetalness);
        }

        return returnColor;
    }

    void RayCaster::calculatePixels(const unsigned start, const unsigned end, const unsigned numSamples, const unsigned maxBounces, const Scene& scene, const Config& config, Picture& pic)
    {
        const auto aspectRatio = static_cast<float>(config.resolutionX) / static_cast<float>(config.resolutionY);

        for (auto x = start; x < end; ++x)
        {
            if (x % 5 == 0 && start == 0) std::cout << "Completion: " << static_cast<float>(x) / static_cast<float>(end - 1 - start) * 100.f << "%\n";

            for (auto y = 0u; y < config.resolutionY; ++y)
            {
                auto color = glm::vec3{0};

                for (auto sample = 0ul; sample < numSamples; ++sample)
                {
                    auto ray = Ray(glm::vec3(static_cast<float>(x) / static_cast<float>(config.resolutionX) * aspectRatio, static_cast<float>(y) / static_cast<float>(config.resolutionY), 0), glm::vec3(0, 0, 1));
                    ray.deviate(1 / static_cast<float>(config.resolutionX));
                    const auto result = castRay(ray, scene, maxBounces);
                    color += result / static_cast<float>(numSamples);
                }

                pic.setPixel(x, y, color);
            }
        }
    }


} // RayTracer