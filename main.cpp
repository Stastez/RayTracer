#include <iostream>

#include "ConfigReader.h"
#include "Picture.h"
#include "Plane.h"
#include "PngWriter.h"
#include "RayCaster.h"
#include "Scene.h"

int main(const int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: RayTracer [config]" << std::endl;
        exit(1);
    }

    auto config = RayTracer::ConfigReader::readConfig(argv[1]);

    const auto pic = RayTracer::RayCaster::castRays(config, 16);

    //std::cout << pic.getDebugView() << std::endl;

    RayTracer::PngWriter::writePng(pic, config.outputPath);
}
