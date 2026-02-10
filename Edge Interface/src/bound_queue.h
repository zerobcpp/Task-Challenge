#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BoundedQueue {
public:
    BoundedQueue(size_t capacity)    : capacity_(capacity) {}

    bool push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_not_full_.wait(lock, [&]() {
            return shutdown_ || queue_.size() < capacity_;
        });

        if (shutdown_) return false;

        queue_.push(item);
        cv_not_empty_.notify_one();
        return true;
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_not_empty_.wait(lock, [&]() {
            return shutdown_ || !queue_.empty();
        });

        if (queue_.empty()) return false;

        item = queue_.front();
        queue_.pop();
        cv_not_full_.notify_one();
        return true;
    }

    void shutdown() {
        std::lock_guard<std::mutex> lock(mtx_);
        shutdown_ = true;
        cv_not_empty_.notify_all();
        cv_not_full_.notify_all();
    }

private:
    std::queue<T> queue_;
    size_t capacity_;

    bool shutdown_ = false;

    std::mutex mtx_;
    std::condition_variable cv_not_empty_;
    std::condition_variable cv_not_full_;
};
