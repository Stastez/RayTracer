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
        while (getSanitizedLine(configStream, line))
        {
            if (line.empty() || line.front() == '#') continue;

            switch (line.front())
            {
                case 'o':
                    if (!getSanitizedLine(configStream, line)) continue;

                    config.outputPath = line;
                    break;

                case 'x':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto resolution = splitString(line);

                        if (isInvalid(resolution.x)) {
                            std::cout << "No resolution was given!" << std::endl;
                            exit(1);
                        }

                        config.resolutionX = static_cast<unsigned>(resolution[0]);
                        config.resolutionY = isInvalid(resolution[1]) ? config.resolutionX : static_cast<unsigned>(resolution[1]);
                    }
                    break;

                case 'f':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto numSamples = splitString(line);
                        config.numSamples = isInvalid(numSamples[0]) ? 1 : static_cast<unsigned>(numSamples[0]);
                    }
                    break;

                case 'b':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto maxBounces = splitString(line);
                        config.maxBounces = isInvalid(maxBounces[0]) ? 1 : static_cast<unsigned>(maxBounces[0]);
                    }
                    break;

                case 'p':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto origin = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto normal = splitString(line);

                        config.objects.emplace_back(std::make_unique<Plane>(origin, normal, color, metalness[0]));
                    }
                    break;

                case 'r':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto lowerLeft = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto lowerRight = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto upperLeft = splitString(line);

                        config.objects.emplace_back(std::make_unique<Rectangle>(lowerLeft, lowerRight, upperLeft, color, metalness[0]));
                    }
                    break;

                case 's':
                    {
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto metalness = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto color = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
                        auto center = splitString(line);
                        if (!getSanitizedLine(configStream, line)) continue;
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

        switch (output.size()) {
            case 3:
                return glm::vec3{output[0], output[1], output[2]};
            case 2:
                return glm::vec3{output[0], output[1], std::numeric_limits<float>::infinity()};
            case 1:
                return glm::vec3{output[0], std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
            default:
                return glm::vec3{std::numeric_limits<float>::infinity()};
        }
    }

    bool ConfigReader::isInvalid(const float value) {
        return value == std::numeric_limits<float>::infinity();
    }

    std::ifstream & ConfigReader::getSanitizedLine(std::ifstream &stream, std::string &string) {
        getline(stream, string);
        // Remove all control characters
        string.erase(std::remove_if(string.begin(), string.end(), [](char c) { return std::iscntrl(c); } ), string.end());
        return stream;
    }
} // RayTracer