#include <cstdint>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <string>
#include <utility>
#include <vector>

unsigned long long countAllPathsParallel(std::vector<std::string> &matrix) {
  int rows = matrix.size();
  if (rows == 0)
    return 0;
  int cols = matrix[0].size();

  std::pair<int, int> goal;
  bool found = false;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (matrix[i][j] == 'S') {
        goal = {i, j};
        found = true;
        break;
      }
    }
    if (found)
      break;
  }

  std::vector<unsigned long long> partialSums(cols, 0);

#pragma omp parallel for
  for (int startCol = 0; startCol < cols; ++startCol) {
    std::vector<std::vector<unsigned long long>> dp(
        rows, std::vector<unsigned long long>(cols, 0));

    dp[rows - 1][startCol] = 1;

    for (int i = rows - 2; i >= 0; --i) {
      for (int j = 0; j < cols; ++j) {
        if (i + 1 < rows) {
          char below = matrix[i + 1][j];
          if (below == '^') {
            unsigned long long left = (j - 1 >= 0) ? dp[i + 1][j - 1] : 0;
            unsigned long long right = (j + 1 < cols) ? dp[i + 1][j + 1] : 0;
            dp[i][j] = left + right;
          } else {
            dp[i][j] = dp[i + 1][j];
          }
        }
      }
    }

    partialSums[startCol] = dp[goal.first][goal.second];
  }

  unsigned long long totalPaths = 0;
  for (int i = 0; i < cols; ++i) {
    totalPaths += partialSums[i];
  }

  return totalPaths;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::string> manifold;
  std::vector<std::vector<std::pair<int, int>>> paths;
  std::vector<std::pair<int, int>> path;

  while (std::getline(file, line)) {
    manifold.push_back(line);
  }
  unsigned long long sum = countAllPathsParallel(manifold);
  std::cout << "Sum: " << sum << '\n';

  return 0;
}
