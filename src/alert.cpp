#include "alert.h"

bool isBatteryOverheat(double tempC) {
    return tempC > kBatteryOverheatC;
}

bool shouldAlert(const VehicleSignal& signal) {
    if (signal.name == "battery_temp") {
        return isBatteryOverheat(signal.value);
    }
    return false;  // other signals have no alert rule yet
}
