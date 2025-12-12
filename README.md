# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.002358 | 0.002047 |
| day2  | 0.020425 | 0.029585 |
| day3  | 0.001471 | 0.001492 |
| day4  | 0.001678 | 0.003092 |
| day5  | 0.002940 | 0.002680 |
| day6  | 0.016760 | 0.003583 |
| day7  | 0.002082 | 0.002229 |
| day8  | 0.058793 | 0.013204 |
| day9  | 0.002835 | 0.017310 |

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
