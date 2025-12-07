# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.003062 | 0.002463 |
| day2  | 0.021853 | 0.031705 |
| day3  | 0.002520 | 0.002122 |
| day4  | 0.002980 | 0.004188 |
| day5  | 0.003130 | 0.002630 |
| day6  | 0.016574 | 0.004007 |
| day7  | 0.001518 | 0.001576 |

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
