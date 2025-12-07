#include <vector>
#include <string>
#include <iostream>
#include <fstream>

unsigned long long countAllPaths(std::vector<std::string>& matrix) {
    int rows = matrix.size();
    if (rows == 0) return 0;
    int cols = matrix[0].size();

    std::pair<int, int> start;
    bool found = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] == 'S') {
                start = {i, j};
                found = true;
                break;
            }
        }
        if (found) break;
    }

    std::vector<std::vector<unsigned long long>> dp(rows, std::vector<unsigned long long>(cols, 0));

    for (int j = 0; j < cols; ++j) {
        dp[rows - 1][j] = 1;
    }

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

    return dp[start.first][start.second];
}




int main(int argc, char **argv){
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::string> manifold;
  std::vector <std::vector<std::pair<int, int>>> paths;
  std::vector <std::pair<int, int>> path;
  
  while(std::getline(file, line)){
    manifold.push_back(line);
  }
  unsigned long long sum = countAllPaths(manifold);
  std::cout << "Sum: " << sum << '\n';
  
  return 0;
}
