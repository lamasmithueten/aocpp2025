#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::vector<std::pair<unsigned long long, unsigned long long>> mergeRanges(
    std::vector<std::pair<unsigned long long, unsigned long long>> &ranges,
    std::pair<unsigned long long, unsigned long long> input) {
  ranges.push_back(input);

  std::sort(ranges.begin(), ranges.end());

  std::vector<std::pair<unsigned long long, unsigned long long>> merged;
  merged.push_back(ranges[0]);

  size_t size = ranges.size();
  for (size_t i = 1; i < size; ++i) {
    std::pair<unsigned long long, unsigned long long> &last = merged.back();
    const std::pair<unsigned long long, unsigned long long> &current =
        ranges[i];

    if (current.first <= last.second) {
      last.second = std::max(last.second, current.second);
    } else {
      merged.push_back(current);
    }
  }

  return merged;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
  std::vector<std::pair<unsigned long long, unsigned long long>> validRanges;
  std::regex regex_ranges("^[0-9]+-[0-9]+$");
  unsigned long long sum = 0;

  while (std::getline(file, line)) {
    if (std::regex_search(line, regex_ranges)) {
      size_t dashPos = line.find('-');
      if (dashPos != std::string::npos) {
        unsigned long long lower = std::stoul(line.substr(0, dashPos));
        unsigned long long upper = std::stoul(line.substr(dashPos + 1));
        ranges.emplace_back(lower, upper);
      }
    }
  }

  for (std::pair<unsigned long long, unsigned long long> range : ranges) {
    validRanges = mergeRanges(validRanges, range);
  }
  for (std::pair<unsigned long long, unsigned long long> range : validRanges) {
    sum += (range.second - range.first + 1);
  }

  std::cout << "Sum: " << sum << '\n';

  return 0;
}
