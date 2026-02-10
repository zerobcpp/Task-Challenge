
#include <chrono>
#include <thread>
#include "config.h"
#include "sensor.h"


void Sensor::start(){
    stopped = false;
    sensor_thread = std::thread(&Sensor::run, this);
}
void Sensor::stop(){
    stopped = true;
    if (sensor_thread.joinable()){
        sensor_thread.join();
    }
}


void Sensor::run(){
    while(!stopped){
        Frame frame = Frame(frame_id++, std::chrono::steady_clock::now());
        sbq.push(frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/interval));
    }
}