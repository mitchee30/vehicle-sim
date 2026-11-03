#pragma once
#include "vehicle_signal.h"

// Battery is considered overheated strictly above this temperature (Celsius)
constexpr double kBatteryOverheatC = 60.0;

// Returns true if the given battery temperature is above the limit
bool isBatteryOverheat(double tempC);

// Returns true if this signal should raise an alert
bool shouldAlert(const VehicleSignal& signal);
