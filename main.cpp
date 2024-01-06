#include <iostream>

#include "ConfigReader.h"
#include "Picture.h"
#include "Plane.h"
#include "PngWriter.h"
#include "Scene.h"

int main()
{
    auto [outputPath, resolutionX, resolutionY, objects] = RayTracer::ConfigReader::readConfig("/media/stastez/SN850X/code/raytracer/config.cfg");

    const auto scene = RayTracer::Scene(std::move(objects));

    auto ray = RayTracer::Ray();

    auto pic = RayTracer::Picture(resolutionX, resolutionY);

    const auto aspectRatio = static_cast<float>(resolutionX) / static_cast<float>(resolutionY);

    for (unsigned x = 0; x < resolutionX; ++x)
    {
        for (unsigned y = 0; y < resolutionY; ++y)
        {
            ray = RayTracer::Ray(glm::vec3(static_cast<float>(x) / static_cast<float>(resolutionX) * aspectRatio, static_cast<float>(y) / static_cast<float>(resolutionY), 0), glm::vec3(0, 0, 1));
            const auto [exists, position, distance, color] = scene.intersect(ray);
            if (exists) pic.setPixel(x, y, (1 - distance) * color);
            else pic.setPixel(x, y, std::array<png_byte, 3>{0, 0, 0});
        }
    }

    //std::cout << pic.getDebugView() << std::endl;

    RayTracer::PngWriter::writePng(pic, outputPath);
}
