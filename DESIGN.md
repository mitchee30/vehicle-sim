# Vehicle Signal Simulator — Design

## 1. Goal

Simulate the in-vehicle data path of a modern car: sensors produce readings, the readings travel over a bus, a processing module filters them and raises alerts, and a dashboard displays them in real time. The project demonstrates multithreading, inter-thread communication, Linux networking (SocketCAN / UDP) and test-driven C++17.

## 2. Modules

| Module | Responsibility |
| --- | --- |
| Sensor simulator | One thread per sensor; produces readings at its own rate (speed 10 Hz, RPM 10 Hz, battery temp 1 Hz) |
| Bus layer | Moves readings from sensors to the processor. Phase 1: thread-safe ring buffer. Phase 2: Linux virtual CAN (`vcan0`) |
| Processor | Smooths noisy readings (moving average), checks alert rules, writes a log |
| Output | Sends processed readings over UDP to a separate terminal dashboard program |

```
[Sensor threads] --> [Bus: ring buffer / vcan0] --> [Processor thread] --> UDP --> [Dashboard]
                                                          |
                                                        log file
```

## 3. Data format

```cpp
struct VehicleSignal {
    std::string name;      // "vehicle_speed", "engine_rpm", "battery_temp"
    double value;
    long long timestampMs;
};
```

On CAN, each signal type gets a fixed CAN ID and its value is packed into the 8-byte data field.

## 4. Thread model

- **Producers:** N sensor threads push readings into the bus.
- **Consumer:** one processor thread pops readings and handles them.
- **Synchronization:** the ring buffer is protected by a `std::mutex`; a `std::condition_variable` wakes the consumer when data arrives, so it never busy-waits.
- **Full buffer policy:** drop the oldest reading (fresh data matters more than old data in a vehicle).
- **Shutdown:** an `std::atomic<bool>` flag tells all threads to stop; `main` joins every thread.

## 5. Alert rules (initial)

| Signal | Rule |
| --- | --- |
| battery_temp | Alert if above 60 °C |
| vehicle_speed | Alert if above 200 km/h |
| engine_rpm | Alert if above 6500 RPM |

## 6. Testing

- Unit tests (GoogleTest) for alert rules, filtering and the ring buffer.
- Stress test: run all threads for 10 minutes, verify no crash and no lost or corrupted readings.
- CI: GitHub Actions builds and runs all tests on every push.

## 7. Milestones

| Week | Deliverable |
| --- | --- |
| 1 | CMake skeleton, first unit test, this document |
| 2 | Sensor simulator threads |
| 3 | Ring buffer + producer/consumer; try vcan |
| 4 | Filtering and alert logic with full test coverage |
| 5 | UDP dashboard, GitHub Actions, README with demo |
