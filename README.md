# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.001969 | 0.002564 |
| day2  | 0.019874 | 0.147915 |
| day3  | 0.001597 | 0.001466 |
| day4  | 0.001636 | 0.002947 |
| day5  | 0.002302 | 0.002069 |
| day6  | 0.014740 | 0.003303 |

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
