#include <chrono>
#include <thread>

#include "bound_queue.h"
#include "frame.h"
#include "sensor.h"
#include "interference.h"


int main(int argc, char **argv){
    BoundedQueue<Frame> bq(5);
    Sensor sensor(bq, 30);
    Interference interference(bq, 50);
    sensor.start();
    interference.start_delay();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    sensor.stop();
    bq.shutdown();
    interference.stop_delay();

    return 0;
}