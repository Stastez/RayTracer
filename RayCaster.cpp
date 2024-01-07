#include "RayCaster.h"

#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <random>

#include "ConfigReader.h"
#include "ThreadSafeQueue.h"

namespace RayTracer {

    Picture RayCaster::castRays(Config& config, const unsigned numSamples, const unsigned numThreads, const unsigned maxBounces)
    {
        Picture pic {config.resolutionX, config.resolutionY};

        const Scene scene {std::move(config.objects)};

        ThreadSafeQueue queue;
        for (auto x = 0u; x < config.resolutionX; ++x)
        {
            for (auto y = 0u; y < config.resolutionY; ++y)
            {
                queue.push({x, y});
            }
        }

        std::vector<std::future<void>> threads(numThreads + 1);
        for (auto i = 0u; i < numThreads; ++i)
        {
            threads[i] = std::async(std::launch::async, calculatePixels, numSamples, maxBounces, i, std::ref(scene), std::ref(config), std::ref(pic), std::ref(queue));
        }
        threads[numThreads] = std::async(std::launch::async, displayCompletion, std::ref(queue), config.resolutionX * config.resolutionY);

        /*const auto batchSize = config.resolutionX / numThreads;
        std::vector<std::future<void>> threads(numThreads + 1);
        std::vector<float> completion(numThreads);

        for (auto i = 0u; i < numThreads - 1; ++i)
        {
            threads[i] = std::async(std::launch::async, calculatePixels, i * batchSize, (i + 1) * batchSize + 1, numSamples, maxBounces, i, std::ref(scene), std::ref(config), std::ref(pic), std::ref(completion));
        }
        threads[numThreads - 1] = std::async(std::launch::async, calculatePixels, (numThreads - 1) * batchSize, config.resolutionX, numSamples, maxBounces, numThreads - 1, std::ref(scene), std::ref(config), std::ref(pic), std::ref(completion));
        threads[numThreads] = std::async(std::launch::async, displayCompletion, std::ref(completion));*/

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

    void RayCaster::calculatePixels(const unsigned numSamples, const unsigned maxBounces, const unsigned thread, const Scene& scene, const Config& config, Picture& pic, ThreadSafeQueue& queue)
    {
        const auto aspectRatio = static_cast<float>(config.resolutionX) / static_cast<float>(config.resolutionY);
        const std::uniform_real_distribution<float> distribution(0, 1 / static_cast<float>(config.resolutionX));
        std::mt19937 randomEngine{thread};
        auto random = std::bind(distribution, randomEngine);

        auto currentPixel = queue.pop();
        while (currentPixel.valid)
        {
            auto color = glm::vec3{0};

            for (auto sample = 0ul; sample < numSamples; ++sample)
            {
                auto ray = Ray(glm::vec3(static_cast<float>(currentPixel.pixel.x) / static_cast<float>(config.resolutionX) * aspectRatio, static_cast<float>(currentPixel.pixel.y) / static_cast<float>(config.resolutionY), 0), glm::vec3(0, 0, 1));
                ray.deviate(random());
                const auto result = castRay(ray, scene, maxBounces);
                color += result / static_cast<float>(numSamples);
            }

            pic.setPixel(currentPixel.pixel.x, currentPixel.pixel.y, color);

            currentPixel = queue.pop();
        }

        /*for (auto x = start; x < end; ++x)
        {
            if (x % 5 == 0)
            {
                completion[thread] = std::floor(static_cast<float>(x - start) / static_cast<float>(end - 1 - start) * 100.f);
            }

            for (auto y = 0u; y < config.resolutionY; ++y)
            {
                auto color = glm::vec3{0};

                for (auto sample = 0ul; sample < numSamples; ++sample)
                {
                    auto ray = Ray(glm::vec3(static_cast<float>(x) / static_cast<float>(config.resolutionX) * aspectRatio, static_cast<float>(y) / static_cast<float>(config.resolutionY), 0), glm::vec3(0, 0, 1));
                    ray.deviate(random());
                    const auto result = castRay(ray, scene, maxBounces);
                    color += result / static_cast<float>(numSamples);
                }

                pic.setPixel(x, y, color);
            }
        }

        completion[thread] = 100.f;*/
    }

    void RayCaster::displayCompletion(const ThreadSafeQueue& queue, const unsigned pixelCount)
    {
        while (!queue.empty())
        {
            const auto completion = static_cast<float>(pixelCount - queue.size()) / static_cast<float>(pixelCount);
            std::cout << "Completion: " << completion * 100.f << "%\n";
            std::this_thread::sleep_for(std::chrono_literals::operator ""ms(1000));
        }

        std::cout << "Completion: 100%" << std::endl;
    }

} // RayTracer