# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.002179 | 0.002064 |
| day2  | 0.021330 | 0.033243 |
| day3  | 0.002551 | 0.002004 |
| day4  | 0.002176 | 0.003188 |
| day5  | 0.003803 | 0.002716 |
| day6  | 0.015942 | 0.003768 |

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
