#pragma once

#include <array>
#include <png.h>
#include <string>
#include <vector>
#include <glm/vec3.hpp>

namespace RayTracer {

class Picture {
private:
    std::vector<png_byte> data;
    const unsigned resolutionX, resolutionY;

    [[nodiscard]] unsigned calculateIndex(unsigned x, unsigned y) const;

public:
    Picture(unsigned resolutionX, unsigned resolutionY);

    void setPixel(unsigned x, unsigned y, const std::array<png_byte, 3>& color);
    void setPixel(unsigned x, unsigned y, const glm::vec3& color);
    void setPixel(unsigned index, const glm::vec3& color);
    [[nodiscard]] std::array<png_byte, 3> getPixel(unsigned x, unsigned y) const;
    [[nodiscard]] const std::vector<png_byte>& getData() const;
    [[nodiscard]] unsigned getResolutionX() const;
    [[nodiscard]] unsigned getResolutionY() const;
    [[nodiscard]] std::string getDebugView() const;
};

} // RayTracer