# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.001983 | 0.002197 |
| day2  | 0.021374 | 0.064440 |
| day3  | 0.001863 | 0.002097 |
| day4  | 0.002008 | 0.004213 |
| day5  | 0.002711 | 0.002376 |
| day6  | 0.016395 | 0.003407 |
| day7  | 0.002027 | 0.002162 |
| day8  | 0.056055 | 0.013442 |

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
