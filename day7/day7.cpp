#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int splitBeam(unsigned long int x, unsigned long int y,
              std::vector<std::string> &manifold) {
  if (x == 0) {
    manifold[x + 1][y + 1] = '|';
  } else if (x == manifold[x].length()) {
    manifold[x + 1][y - 1] = '|';
  } else {
    manifold[x + 1][y - 1] = '|';
    manifold[x + 1][y + 1] = '|';
  }
  return 1;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::string> manifold;
  int splits = 0;

  while (std::getline(file, line)) {
    manifold.push_back(line);
  }

  unsigned long int size = manifold.size() - 1;
  unsigned long int width = manifold[0].length();
  for (unsigned long int i = 0; i < size; i++) {
    for (unsigned long int j = 0; j < width; j++) {
      if (manifold[i][j] == 'S') {
        manifold[i + 1][j] = '|';
        break;
      }
    }
    break;
  }
  for (unsigned long int i = 0; i < size; i++) {
    for (unsigned long int j = 0; j < width; j++) {
      if (manifold[i][j] == '|') {
        if (manifold[i + 1][j] == '^') {
          splits += splitBeam(i, j, manifold);
        } else {
          manifold[i + 1][j] = '|';
        }
      }
    }
  }

  std::cout << "Splits: " << splits << '\n';

  return 0;
}
