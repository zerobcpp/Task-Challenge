
#include "interference.h"
#include <chrono>
#include <iostream>

void Interference::start_delay(){
    stopped = false;
    interference_thread = std::thread(&Interference::run, this);
}

void Interference::stop_delay(){
    stopped = true;
    if (interference_thread.joinable()){
        interference_thread.join();
    }
}

void Interference::run(){
    while(!stopped){
        Frame frame;
        if(!ibq.pop(frame)){
            break;
        }   
        std::this_thread::sleep_for(std::chrono::milliseconds(delays));
        auto ping = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - frame.timestamp).count();
        std::cout<<"Interference Delay for Frame " << frame.id << ": " << ping << " ms"<<std::endl;

    }
}