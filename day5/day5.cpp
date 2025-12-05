#include <fstream>
#include <iostream>
#include <regex>
#include <string>

bool isValid(unsigned long long lower, unsigned long long upper,
             unsigned long long value) {
  if (value >= lower && value <= upper) {
    return true;
  }
  return false;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
  std::vector<unsigned long long> values;
  std::regex regex_ranges("^[0-9]+-[0-9]+$");
  std::regex regex_values("^[0-9]+$");
  int sum = 0;

  while (std::getline(file, line)) {
    if (std::regex_search(line, regex_ranges)) {
      size_t dashPos = line.find('-');
      if (dashPos != std::string::npos) {
        unsigned long long lower = std::stoul(line.substr(0, dashPos));
        unsigned long long upper = std::stoul(line.substr(dashPos + 1));
        ranges.emplace_back(lower, upper);
      }
    } else if (std::regex_search(line, regex_values)) {
      values.push_back(std::stoul(line));
    }
  }

  for (unsigned long long value : values) {
    for (std::pair<unsigned long long, unsigned long long> range : ranges) {
      if (isValid(range.first, range.second, value)) {
        sum++;
        break;
      }
    }
  }

  std::cout << "Sum: " << sum << '\n';

  return 0;
}
