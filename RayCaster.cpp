#include "RayCaster.h"

#include <future>
#include <iostream>

#include "ConfigReader.h"

namespace RayTracer {

    Picture RayCaster::castRays(Config& config, const unsigned numSamples, const unsigned numThreads)
    {
        Picture pic {config.resolutionX, config.resolutionY};

        const Scene scene {std::move(config.objects)};

        for (unsigned x = 0; x < config.resolutionX; ++x)
        {
            for (unsigned y = 0; y < config.resolutionY; y += numThreads)
            {
                std::vector<std::future<void>> threads {numThreads};
                for (auto i = 0u; i < numThreads; ++i)
                {
                    threads[i] = std::async(std::launch::async,calculatePixel, x, y + i, numSamples, std::ref(scene), std::ref(config), std::ref(pic));
                    //calculatePixel(x, y + i, numSamples, scene, config, pic);
                }
                for (const auto& thread : threads) thread.wait();
                //std::cout << pic.getDebugView() << std::endl;
            }
        }

        return pic;
    }

    glm::vec3 RayCaster::castRay(const Ray& ray, const Scene& scene, const unsigned maxBounces)
    {
        auto bounces = 0u;

        auto intersection = scene.intersect(ray);
        auto returnColor = (intersection.exists) ? /*(1 - intersection.distance) * intersection.object->getColor()*/ intersection.object->getColor() : glm::vec3{0};

        while (bounces++ < maxBounces && intersection.exists && intersection.object->getMetalness() > 0 && intersection.distance > 0.01)
        {
            const auto newRay = intersection.object->reflectRay(ray, intersection);
            const float oldMetalness = intersection.object->getMetalness();
            intersection = scene.intersect(newRay);
            returnColor = glm::mix(returnColor, intersection.object->getColor(), oldMetalness);
        }

        //if (!intersection.exists || intersection.object->getMetalness() <= 0 || intersection.distance <= 0.01) return returnColor;

        return returnColor;
    }

    void RayCaster::calculatePixel(const unsigned x, const unsigned y, const unsigned numSamples, const Scene& scene, const Config& config, Picture& pic)
    {
        if (x >= config.resolutionX || y >= config.resolutionY) return;

        const auto aspectRatio = static_cast<float>(config.resolutionX) / static_cast<float>(config.resolutionY);
        auto color = glm::vec3{0};

        for (auto i = 0ul; i < numSamples; ++i)
        {
            auto ray = Ray(glm::vec3(static_cast<float>(x) / static_cast<float>(config.resolutionX) * aspectRatio, static_cast<float>(y) / static_cast<float>(config.resolutionY), 0), glm::vec3(0, 0, 1));
            ray.deviate(1 / static_cast<float>(config.resolutionX));
            const auto result = castRay(ray, scene, 1000);
            color += result / static_cast<float>(numSamples);
        }

        pic.setPixel(x, y, color);
    }


} // RayTracer