#pragma once

#include <memory>
#include <vector>
#include <string>

#include "ConfigReader.h"
#include "ConfigReader.h"
#include "Geometry.h"

namespace RayTracer {

struct Config
{
    std::string outputPath;
    unsigned resolutionX, resolutionY;
    unsigned maxBounces, numSamples;
    std::vector<std::unique_ptr<Geometry>> objects;
};

class ConfigReader {
private:
    static glm::vec3 splitString(const std::string& input);
    static bool isInvalid(float value);
    static std::ifstream & getSanitizedLine(std::ifstream& stream, std::string& string);

public:
    static Config readConfig(const std::string& path);
};

} // RayTracer
