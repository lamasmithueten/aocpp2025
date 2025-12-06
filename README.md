# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (ms) | Part 2 (ms) |
|-------|------------------|------------------|
| day1  | 0.002337 | 0.002064 |
| day2  | 0.020660 | 0.153500 |
| day3  | 0.001969 | 0.001499 |
| day4  | 0.002170 | 0.002999 |
| day5  | 0.002646 | 0.002123 |
| day6  | 0.014324 | 0.003505 |

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
