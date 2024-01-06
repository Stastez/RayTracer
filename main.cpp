#include <iostream>

#include "Picture.h"
#include "Plane.h"
#include "PngWriter.h"
#include "Rectangle.h"

int main()
{
    constexpr unsigned resX = 200;
    constexpr unsigned resY = 200;

    auto plane = RayTracer::Rectangle({10, 10, 0}, {190, 10, 1}, {10, 190, 1});

    auto ray = RayTracer::Ray();

    auto pic = RayTracer::Picture(resX, resY);

    for (unsigned x = 0; x < resX; ++x)
    {
        for (unsigned y = 0; y < resY; ++y)
        {

            if (x > 9 && y > 9)
            {
                int a = 50;
                a /= 10;
            }

            ray = RayTracer::Ray(glm::vec3(x, y, 0), glm::vec3(0, 0, 1));
            auto intersection = plane.intersect(ray);
            if (intersection.exists) pic.setPixel(x, y, glm::vec3(0, 0, intersection.position.z));
            else pic.setPixel(x, y, std::array<png_byte, 3>{0, 0, 0});
            //pic.setPixel(x, y, glm::vec3(0.5));
            //pic.setPixel(x, y, {static_cast<unsigned char>(x), static_cast<unsigned char>(y), 0});
            //pic.setPixel(x, y, {255, 255, 255});
        }
    }

    std::cout << pic.getDebugView() << std::endl;

    RayTracer::PngWriter::writePng(pic, "/media/stastez/SN850X/code/raytracer/test.png");
}
