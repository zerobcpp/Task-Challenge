#pragma once
#ifndef FRAME_H
#define FRAME_H

#include <chrono>

struct Frame {
    uint64_t id;
    std::chrono::steady_clock::time_point timestamp;
    
    Frame(){
        timestamp = std::chrono::steady_clock::now();
    }
    Frame(uint64_t frame_id){
        id = frame_id;
        timestamp = std::chrono::steady_clock::now();
    }
    Frame(uint64_t frame_id, std::chrono::steady_clock::time_point time):
        id(frame_id), timestamp(time) {};
};




#endif  