#include "PngWriter.h"
#include <cstdio>
#include <iostream>

namespace RayTracer {

    void PngWriter::writePng(const Picture& picture, const std::string& path)
    {
        const auto png = fopen(path.c_str(), "wb");
        if (!png)
        {
            std::cout << "Could not open " << path << "!" << std::endl;
            exit(1);
        }

        auto pngStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!pngStruct)
        {
            std::cout << "Could not create PNG write struct!" << std::endl;
            exit(1);
        }
        auto pngInfo = png_create_info_struct(pngStruct);
        if (!pngInfo)
        {
            png_destroy_write_struct(&pngStruct, nullptr);
            std::cout << "Could not create PNG info struct!" << std::endl;
            exit(1);
        }

        try
        {
            png_init_io(pngStruct, png);
            png_set_IHDR(pngStruct, pngInfo, picture.getResolutionX(), picture.getResolutionY(), 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
            png_write_info(pngStruct, pngInfo);

            auto pictureData = picture.getData();

            auto offsetVector = std::vector<png_byte *>();
            offsetVector.reserve(picture.getResolutionY());
            for (auto i = 0ul; i < pictureData.size(); i += picture.getResolutionX() * 3)
                offsetVector.emplace_back(&pictureData[i]);

            png_write_image(pngStruct, offsetVector.data());
            png_write_end(pngStruct, pngInfo);
        }
        catch (std::exception& e)
        {
            png_destroy_write_struct(&pngStruct, &pngInfo);
            fclose(png);
            std::cout << "Could not write PNG!" << std::endl;
            exit(1);
        }

        png_destroy_write_struct(&pngStruct, &pngInfo);
        fclose(png);
    }


} // RayTracer