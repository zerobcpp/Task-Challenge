#pragma once
#ifndef INTERFERENCE_H
#define INTERFERENCE_H
#include "bound_queue.h"
#include "config.h"
#include <atomic>
#include <thread>
#include "frame.h"
class Interference {
    BoundedQueue<Frame>& ibq;
    Config config;
    int delays;
    std::atomic<bool> stopped = false;
    std::thread interference_thread;

    void run();

    public:
        Interference(BoundedQueue<Frame>& queue, const Config& conf, int delay) : ibq(queue), config(conf), delays(delay){};
        Interference(BoundedQueue<Frame>& queue, int delay) : ibq(queue), delays(delay) {};
        void start_delay();
        void stop_delay();


};

#endif