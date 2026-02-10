#pragma once
#ifndef SENSOR_H
#define SENSOR_H

#include <thread>
#include "frame.h"
#include "bound_queue.h"
#include "config.h"
#include <atomic>

class Sensor {
    
    BoundedQueue<Frame>& sbq;
    Config config;
    uint64_t frame_id = 0;
    std::atomic<bool> stopped = false;
    std::thread sensor_thread;
    int interval;

    void run();
    public:
        void start();
        void stop();
        Sensor(const Config& cfg, BoundedQueue<Frame>& queue, int delay) : 
            sbq(queue), config(cfg), interval(delay) {};
        Sensor(BoundedQueue<Frame>& queue, int delay) :
            sbq(queue), interval(delay) {};



};

#endif 