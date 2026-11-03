#pragma once
#include <string>

// One reading from one sensor, e.g. battery temperature = 65.0 at t = 1200 ms
struct VehicleSignal {
    std::string name;        // signal name, e.g. "battery_temp"
    double value;            // reading
    long long timestampMs;   // when it was produced, in milliseconds
};
