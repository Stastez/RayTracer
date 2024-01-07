#include "ConfigReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Plane.h"
#include "Rectangle.h"
#include "Sphere.h"

namespace RayTracer {

    Config ConfigReader::readConfig(const std::string& path)
    {
        std::ifstream configStream {path, std::ios::in};
        if (!configStream.is_open())
        {
            std::cout << "Cannot open " << path << "!" << std::endl;
            exit(1);
        }

        Config config;

        std::string line;
        while (getline(configStream, line))
        {
            if (line.empty() || line.front() == '#') continue;

            switch (line.front())
            {
                case 'o':
                    if (!getline(configStream, line)) continue;
                    config.outputPath = line;
                    break;

                case 'x':
                    {
                        if (!getline(configStream, line)) continue;
                        auto resolution = splitString(line);
                        config.resolutionX = static_cast<unsigned>(resolution[0]);
                        config.resolutionY = static_cast<unsigned>(resolution[1]);
                    }
                    break;

                case 'f':
                    {
                        if (!getline(configStream, line)) continue;
                        auto numSamples = splitString(line);
                        config.numSamples = static_cast<unsigned>(numSamples[0]);
                    }
                    break;

                case 'b':
                    {
                        if (!getline(configStream, line)) continue;
                        auto maxBounces = splitString(line);
                        config.maxBounces = static_cast<unsigned>(maxBounces[0]);
                    }
                    break;

                case 'p':
                    {
                        if (!getline(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto origin = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto normal = splitString(line);

                        config.objects.emplace_back(std::make_unique<Plane>(origin, normal, color, metalness[0]));
                    }
                    break;

                case 'r':
                    {
                        if (!getline(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto lowerLeft = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto lowerRight = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto upperLeft = splitString(line);

                        config.objects.emplace_back(
                            std::make_unique<Rectangle>(lowerLeft, lowerRight, upperLeft, color, metalness[0]));
                    }
                    break;

                case 's':
                    {
                        if (!getline(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto center = splitString(line);
                        if (!getline(configStream, line)) continue;
                        auto radius = splitString(line);

                        config.objects.emplace_back(std::make_unique<Sphere>(center, radius[0], color, metalness[0]));
                    }
                    break;

                default:
                    break;
            }
        }

        configStream.close();

        return config;
    }

    glm::vec3 ConfigReader::splitString(const std::string& input)
    {
        std::stringstream stream {input};
        std::vector<float> output;
        std::string segment;

        while (getline(stream, segment, ' '))
        {
            output.emplace_back(std::stof(segment));
        }

        if (output.size() == 3) return glm::vec3{output[0], output[1], output[2]};
        else if (output.size() == 2) return glm::vec3{output[0], output[1], std::numeric_limits<float>::infinity()};
        else return glm::vec3{output[0], std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
    }

} // RayTracer