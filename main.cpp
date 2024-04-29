#include <iostream>
#include <thread>
#include <chrono>

#include "ConfigReader.h"
#include "PngWriter.h"
#include "RayCaster.h"

int main(const int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: RayTracer [config]" << std::endl;
        exit(1);
    }

    auto config = RayTracer::ConfigReader::readConfig(argv[1]);

    auto start = std::chrono::high_resolution_clock::now();

    const auto pic = RayTracer::RayCaster::castRays(config, config.numSamples, std::thread::hardware_concurrency(), config.maxBounces);

    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << std::endl;

    //std::cout << pic.getDebugView() << std::endl;

    RayTracer::PngWriter::writePng(pic, config.outputPath);
}
