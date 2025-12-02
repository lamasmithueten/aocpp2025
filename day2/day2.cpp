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

int main(int argc, char **argv) {

  std::ifstream file(argv[1]);
  std::string line;
  std::getline(file, line);
  std::vector<unsigned long long> invalidIds;

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

    unsigned int lowerBound = countDigits(r.first);
    unsigned int upperBound = countDigits(r.second);
    if (lowerBound % 2 && upperBound % 2)
      if (lowerBound == upperBound) {
        continue;
      }

    for (unsigned long long i = r.first; i <= r.second; i++) {
      unsigned int length = countDigits(i);
      if (length % 2) {
        continue;
      }

      unsigned long long lower, upper;
      unsigned long long divisor =
          static_cast<unsigned long long>(pow(10, length / 2));

      upper = i / divisor;
      lower = i % divisor;

      if ((upper - lower) == 0 && i >= r.first) {
        invalidIds.push_back(i);
      }
    }
  }

  std::cout << "Sum: "
            << std::accumulate(invalidIds.begin(), invalidIds.end(), 0ULL)
            << '\n';

  return 0;
}
