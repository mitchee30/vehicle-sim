# Vehicle Signal Simulator

A C++17 simulation of an in-vehicle signal pipeline: sensors → bus → processing & alerts → dashboard. See [DESIGN.md](DESIGN.md) for the architecture.

## Build and run

Requires Linux, a C++17 compiler and CMake 3.14+.

```bash
cmake -S . -B build
cmake --build build
./build/vehicle_sim
```

## Run tests

```bash
ctest --test-dir build
```
