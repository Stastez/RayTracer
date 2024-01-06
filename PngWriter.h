#pragma once

#include "Picture.h"

#include <string>

namespace RayTracer {

class PngWriter {
public:
    static void writePng(const Picture& picture, const std::string& path);
};

} // RayTracer