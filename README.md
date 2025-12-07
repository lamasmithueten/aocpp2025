# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.001992 | 0.001937 |
| day2  | 0.020940 | 0.029813 |
| day3  | 0.001814 | 0.002012 |
| day4  | 0.001841 | 0.003794 |
| day5  | 0.002627 | 0.002634 |
| day6  | 0.016005 | 0.003414 |
| day7  | 0.001599 | 0.001641 |

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
