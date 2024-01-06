cmake_minimum_required(VERSION 3.27)

set(TARGET_NAME RayTracer)

project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(${TARGET_NAME} main.cpp
        PngWriter.cpp
        PngWriter.h
        Picture.cpp
        Picture.h
        Geometry.h
        Ray.cpp
        Ray.h
        Plane.cpp
        Plane.h
        Rectangle.cpp
        Rectangle.h
        Sphere.cpp
        Sphere.h
        Scene.cpp
        Scene.h
)

if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE /W4)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -favor:AMD64")
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

find_package(glm CONFIG REQUIRED)
find_package(PNG REQUIRED)
target_link_libraries(${TARGET_NAME} PRIVATE glm::glm PNG::PNG)