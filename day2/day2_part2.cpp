#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

unsigned int countDigits(unsigned long long number) {
  if (number == 0)
    return 1;
  return static_cast<unsigned int>(log10(number)) + 1;
}

std::vector<unsigned long long> getDivisors(unsigned long long number) {
  std::vector<unsigned long long> divisors;

  for (unsigned long long i = 1; i <= std::sqrt(number); ++i) {
    if (number % i == 0) {
      divisors.push_back(i);
      if (i != number / i) {
        divisors.push_back(number / i);
      }
    }
  }

  std::sort(divisors.begin(), divisors.end());

  divisors.pop_back();
  return divisors;
}

bool areFractionsEqual(unsigned long long number, unsigned int fractionSize,
                       unsigned int length) {
  std::string input = std::to_string(number);
  int numFractions = length / fractionSize;
  std::string firstFraction = input.substr(0, fractionSize);

  for (unsigned int i = 1; i < numFractions; i++) {
    std::string currentFraction = input.substr(i * fractionSize, fractionSize);
    if (currentFraction != firstFraction) {
      return false;
    }
  }
  return true;
}

int main(int argc, char **argv) {

  std::ifstream file(argv[1]);
  std::string line;
  std::getline(file, line);
  std::vector<unsigned long long> invalidIds;
  std::vector<unsigned long long> divisors;

  std::vector<std::pair<unsigned long long, unsigned long long>> ranges;
  std::istringstream iss(line);
  unsigned long long sum = 0;

  while (std::getline(iss, line, ',')) {
    size_t dashPos = line.find('-');
    if (dashPos != std::string::npos) {
      unsigned long long lower = std::stoull(line.substr(0, dashPos));
      unsigned long long upper = std::stoull(line.substr(dashPos + 1));
      ranges.emplace_back(lower, upper);
    }
  }
  for (const auto &r : ranges) {
    for (unsigned long long i = r.first; i <= r.second; i++) {
      unsigned int length = countDigits(i);
      divisors = getDivisors(length);

      for (auto j : divisors) {
        if (areFractionsEqual(i, j, length)) {
          invalidIds.push_back(i);
          break;
        }
      }
    }
  }

  std::cout << "Sum: "
            << std::accumulate(invalidIds.begin(), invalidIds.end(), 0ULL)
            << '\n';

  return 0;
}
