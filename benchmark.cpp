#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

std::vector<std::string> get_day_folders() {
  std::vector<std::string> day_folders;
  for (const auto &entry : fs::directory_iterator(".")) {
    if (entry.is_directory() &&
        entry.path().filename().string().substr(0, 3) == "day") {
      day_folders.push_back(entry.path().filename().string());
    }
  }
  return day_folders;
}

double benchmark_program(const std::string &day_folder,
                         const std::string &part) {
  std::string binary_path = day_folder + "/" + part;
  std::string input_path = day_folder + "/input.txt";
  std::string command = binary_path + " " + input_path;

  auto start = std::chrono::high_resolution_clock::now();
  int ret = system(command.c_str());
  auto end = std::chrono::high_resolution_clock::now();

  if (ret != 0) {
    std::cerr << "Error running " << binary_path << std::endl;
    return -1.0;
  }

  std::chrono::duration<double> elapsed = end - start;
  return elapsed.count();
}

void build_day(const std::string &day_folder) {
  std::string command = "cd " + day_folder + " && make";
  int ret = system(command.c_str());
  if (ret != 0) {
    std::cerr << "Error building " << day_folder << std::endl;
  }
}

void write_readme(const std::vector<std::string> &day_folders,
                  const std::vector<std::pair<double, double>> &results) {
  std::ofstream readme("README.md");
  readme << "# Advent of Code 2025\n\n";
  readme << "This repository contains my solutions for Advent of Code 2025, "
            "written in C++.\n\n";
  readme << "## Benchmark Results\n\n";
  readme << "| Day   | Part 1 (seconds) | Part 2 (seconds) |\n";
  readme << "|-------|------------------|------------------|\n";

  for (size_t i = 0; i < day_folders.size(); ++i) {
    readme << "| " << day_folders[i] << "  | "
           << (results[i].first >= 0 ? std::to_string(results[i].first)
                                     : "Error")
           << " | "
           << (results[i].second >= 0 ? std::to_string(results[i].second)
                                      : "Error")
           << " |\n";
  }

  readme << "\n---\n";
  readme << "### How to Run the Benchmark\n";
  readme << "1. Place the benchmark program in the root of this repository.\n";
  readme << "2. Compile it via the makefile via\n";
  readme << "   ```bash\n ";
  readme << "   make\n";
  readme << "   ```\n";
  readme << "   or with:\n";
  readme << "   ```bash\n";
  readme << "   g++ -std=c++17 benchmark.cpp -o benchmark\n";
  readme << "   ```\n";
  readme << "3. Run the benchmark:\n";
  readme << "   ```bash\n";
  readme << "   ./benchmark\n";
  readme << "   ```\n";
  readme.close();
}

int main() {
  std::vector<std::string> day_folders = get_day_folders();
  std::vector<std::pair<double, double>> results;

  for (const auto &day_folder : day_folders) {
    build_day(day_folder);

    double part1_time = benchmark_program(day_folder, "part1");
    double part2_time = benchmark_program(day_folder, "part2");

    results.emplace_back(part1_time, part2_time);
  }

  write_readme(day_folders, results);

  return 0;
}
