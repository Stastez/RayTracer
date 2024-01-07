#include "ThreadSafeQueue.h"

namespace RayTracer {

    void ThreadSafeQueue::push(const glm::uvec2& pixel)
    {
        queue.push(pixel);
    }

    QueueReturn ThreadSafeQueue::pop()
    {
        std::unique_lock<std::mutex> lock(mutex);

        if (queue.empty()) return {false, {}};

        const auto pixel = queue.front();
        queue.pop();

        return {true, pixel};
    }

    /**
     * \brief Returns the size of the queue. Not thread-safe.
     * \return Size of the queue.
     */
    unsigned ThreadSafeQueue::size() const
    {
        return queue.size();
    }

    /**
     * \brief Returns whether the queue is empty. Not thread-safe.
     * \return Is empty or not.
     */
    bool ThreadSafeQueue::empty() const
    {
        return queue.empty();
    }

} // RayTracer