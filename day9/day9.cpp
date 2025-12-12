#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

long int pow(long int base, long int exponent) {
  long int result = 1;
  for (long int i = 0; i < exponent; i++)
    result *= base;
  return result;
}

std::pair<long int, long int>
findGridSize(std::vector<std::pair<long int, long int>> &tiles) {
  std::pair<long int, long int> gridsize = {0, 0};
  for (std::pair<long int, long int> pair : tiles) {
    if (pair.first > gridsize.first)
      gridsize.first = pair.first;
    if (pair.second > gridsize.second)
      gridsize.second = pair.second;
  }
  gridsize.first++;
  gridsize.second++;
  return gridsize;
}

long int rectSize(std::pair<long int, long int> a,
                  std::pair<long int, long int> b) {
  return (std::sqrt(pow((a.first - b.first + 1), 2)) *
          std::sqrt(pow((a.second - b.second + 1), 2)));
}

long int
findBiggestRectSize(std::vector<std::pair<long int, long int>> &tiles) {
  long int biggest = 0;
  for (unsigned long int i = 0; i < tiles.size(); i++) {
    for (unsigned long int j = 0; j < tiles.size(); j++) {
      if (i == j)
        continue;
      long int current = rectSize(tiles[i], tiles[j]);
      if (current > biggest)
        biggest = current;
    }
  }
  return biggest;
}

int main(int argc, char **argv) {
  std::fstream file(argv[1]);
  std::string line;
  std::vector<std::pair<long int, long int>> tiles;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string token;
    std::vector<long int> values;

    while (std::getline(iss, token, ',')) {
      values.push_back(std::stoul(token));
    }

    tiles.emplace_back(values[0], values[1]);
  }

  long int biggestRect = findBiggestRectSize(tiles);
  std::cout << "Biggest: " << biggestRect << '\n';

  return 0;
}
