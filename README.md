# Advent of Code 2025

This repository contains my solutions for Advent of Code 2025, written in C++.

## Benchmark Results

| Day   | Part 1 (seconds) | Part 2 (seconds) |
|-------|------------------|------------------|
| day1  | 0.001988 | 0.001892 |
| day2  | 0.020292 | 0.149419 |
| day3  | 0.001647 | 0.001456 |
| day4  | 0.001625 | 0.002944 |
| day5  | 0.002311 | 0.002066 |
| day6  | 0.014213 | 0.003519 |

---
### How to Run the Benchmark
1. Place the benchmark program in the root of this repository.
2. Compile it via the makefile via
   ```bash
    make
   ```
   or with:
   ```bash
   g++ -std=c++17 benchmark.cpp -o benchmark
   ```
3. Run the benchmark:
   ```bash
   ./benchmark
   ```
