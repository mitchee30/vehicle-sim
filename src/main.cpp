#include <iostream>
#include <vector>
#include "alert.h"

int main() {
    std::vector<VehicleSignal> signals = {
        {"battery_temp", 45.0, 0},
        {"vehicle_speed", 80.0, 100},
        {"battery_temp", 65.0, 200},
    };

    for (const VehicleSignal& s : signals) {
        std::cout << "[" << s.timestampMs << " ms] " << s.name << " = " << s.value;
        if (shouldAlert(s)) {
            std::cout << "  <-- ALERT";
        }
        std::cout << std::endl;
    }
    return 0;
}
