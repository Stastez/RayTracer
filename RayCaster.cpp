#include "RayCaster.h"
#include "ConfigReader.h"

namespace RayTracer {

    Picture RayCaster::castRays(Config& config, const unsigned numSamples)
    {
        Picture pic {config.resolutionX, config.resolutionY};

        const Scene scene {std::move(config.objects)};

        const auto aspectRatio = static_cast<float>(config.resolutionX) / static_cast<float>(config.resolutionY);
        for (unsigned x = 0; x < config.resolutionX; ++x)
        {
            for (unsigned y = 0; y < config.resolutionY; ++y)
            {
                auto color = glm::vec3{0};

                for (auto i = 0ul; i < numSamples; ++i)
                {
                    auto ray = RayTracer::Ray(glm::vec3(static_cast<float>(x) / static_cast<float>(config.resolutionX) * aspectRatio, static_cast<float>(y) / static_cast<float>(config.resolutionY), 0), glm::vec3(0, 0, 1));
                    ray.deviate(0.01);
                    const auto result = castRay(ray, scene, 100);
                    color += result / static_cast<float>(numSamples);
                }

                pic.setPixel(x, y, color);
            }
        }

        return pic;
    }

    glm::vec3 RayCaster::castRay(const Ray& ray, const Scene& scene, const unsigned maxBounces)
    {
        auto bounces = 0;

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

} // RayTracer