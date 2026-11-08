#include "alert.h"

bool isBatteryOverheat(double tempC) {
    return tempC > kBatteryOverheatC;
}

bool isOverSpeeding(double speedKmh) {
    return speedKmh > kSpeedLimit;
}

bool shouldAlert(const VehicleSignal& signal) {
    if (signal.name == "battery_temp") {
        return isBatteryOverheat(signal.value);
    }

    if(signal.name == "vehicle_speed") {
        return isOverSpeeding(signal.value);
    }
    return false;
}
