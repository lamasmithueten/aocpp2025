# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.002019 | 0.001888 |
| day2  | 0.020622 | 0.153543 |
| day3  | 0.001702 | 0.002218 |
| day4  | 0.002065 | 0.003720 |
| day5  | 0.002368 | 0.002122 |
| day6  | 0.016629 | 0.003307 |

---
### How to Run the Benchmark
1. Place the benchmark program in the root of this repository.
2. Compile it via the makefile automatically
   ```bash
    make
   ```
   or manually with:
   ```bash
   g++ -std=c++17 benchmark.cpp -o benchmark
   ```
3. Run the benchmark:
   ```bash
   ./benchmark
   ```
