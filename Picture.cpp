#include "Picture.h"

#include <string>

namespace RayTracer {

    Picture::Picture(const unsigned resolutionX, const unsigned resolutionY) : data(std::vector<png_byte>(resolutionX * resolutionY * 3)), resolutionX(resolutionX), resolutionY(resolutionY) {}

    unsigned Picture::calculateIndex(const unsigned x, const unsigned y) const
    {
        // libPNG uses bottom-left origin, we use top-left origin
        return (x + (resolutionY - 1u - y) * resolutionX) * 3u;
    }


    void Picture::setPixel(const unsigned x, const unsigned y, const std::array<png_byte, 3>& color)
    {
        const unsigned index = calculateIndex(x, y);
        for (unsigned i = 0; i < 3; ++i)
            data[index + i] = color[i];
    }

    void Picture::setPixel(const unsigned x, const unsigned y, const glm::vec3& color)
    {
        const unsigned index = calculateIndex(x, y);
        for (int i = 0; i < 3; ++i)
            data[index + i] = static_cast<png_byte>(color[i] * 255);
    }

    std::array<png_byte, 3> Picture::getPixel(const unsigned x, const unsigned y) const
    {
        const unsigned index = calculateIndex(x, y);
        return {data[index], data[index + 1], data[index + 2]};
    }

    const std::vector<png_byte>& Picture::getData() const
    {
        return data;
    }

    unsigned Picture::getResolutionX() const
    {
        return resolutionX;
    }

    unsigned Picture::getResolutionY() const
    {
        return resolutionY;
    }

    std::string Picture::getDebugView() const
    {
        auto output = std::string();
        auto pixel = std::array<png_byte, 3>{0, 0, 0};

        for (unsigned y = 0; y < resolutionY; ++y)
        {
            for (unsigned x = 0; x < resolutionX; ++x)
            {
                pixel = getPixel(x, y);
                output.append(std::to_string(pixel[0] + pixel[1] + pixel[2]) + "\t");
            }
            output.append("\n");
        }

        return output;
    }


} // RayTracer