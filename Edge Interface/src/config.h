#ifndef CONFIG_H
#define CONFIG_H

struct Config {
    int sensorfps;
    int size;
    int frequency_of_delay;
    bool has_crash_interference;
    //bool has_lidar_interference;
};

#endif