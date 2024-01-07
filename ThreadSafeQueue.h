#pragma once

#include <mutex>
#include <queue>
#include <glm/vec2.hpp>

namespace RayTracer {

struct QueueReturn
{
    bool valid;
    glm::uvec2 pixel;
};

class ThreadSafeQueue {
private:
    std::queue<glm::uvec2> queue;
    std::mutex mutex;

public:
    void push(const glm::uvec2& pixel);
    QueueReturn pop();
    [[nodiscard]] unsigned size() const;
    [[nodiscard]] bool empty() const;
};

} // RayTracer
