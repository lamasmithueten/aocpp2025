#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool isValid(const std::vector<std::string> &matrix, int x, int y) {
  int count = 0;
  int x_max = matrix.size() - 1;
  int y_max = matrix[y].length() - 1;

  // Check left side
  if (x == 0) {
    // Check top side
    if (y == 0) {
      if (matrix[x + 1][y] == '@')
        count++;
      if (matrix[x + 1][y + 1] == '@')
        count++;
      if (matrix[x][y + 1] == '@')
        count++;
      return (count <= 3);
    }
    // Check bottom side
    if (y == y_max) {
      if (matrix[x][y - 1] == '@')
        count++;
      if (matrix[x + 1][y - 1] == '@')
        count++;
      if (matrix[x + 1][y] == '@')
        count++;
      return (count <= 3);
    }
    if (matrix[x + 1][y - 1] == '@')
      count++;
    if (matrix[x + 1][y] == '@')
      count++;
    if (matrix[x + 1][y + 1] == '@')
      count++;
    if (matrix[x][y - 1] == '@')
      count++;
    if (matrix[x][y + 1] == '@')
      count++;
    return (count <= 3);
  }

  // Check right side
  if (x == x_max) {
    // Check top side
    if (y == 0) {
      if (matrix[x - 1][y] == '@')
        count++;
      if (matrix[x - 1][y + 1] == '@')
        count++;
      if (matrix[x][y + 1] == '@')
        count++;
      return (count <= 3);
    }
    // Check bottom side
    if (y == y_max + 1) {
      if (matrix[x - 1][y] == '@')
        count++;
      if (matrix[x - 1][y - 1] == '@')
        count++;
      if (matrix[x][y - 1] == '@')
        count++;
      return (count <= 3);
    }
    if (matrix[x][y - 1] == '@')
      count++;
    if (matrix[x][y + 1] == '@')
      count++;
    if (matrix[x - 1][y - 1] == '@')
      count++;
    if (matrix[x - 1][y] == '@')
      count++;
    if (matrix[x - 1][y + 1] == '@')
      count++;
    return (count <= 3);
  }

  if (matrix[x - 1][y - 1] == '@')
    count++;
  if (matrix[x - 1][y] == '@')
    count++;
  if (matrix[x - 1][y + 1] == '@')
    count++;
  if (matrix[x][y - 1] == '@')
    count++;
  if (matrix[x][y + 1] == '@')
    count++;
  if (matrix[x + 1][y - 1] == '@')
    count++;
  if (matrix[x + 1][y] == '@')
    count++;
  if (matrix[x + 1][y + 1] == '@')
    count++;

  return (count <= 3);
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::vector<std::string> array;
  int sum = 0;

  while (std::getline(file, line)) {
    array.push_back(line);
  }

  int size = array.size();
  int length = array[0].length();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < length; j++) {
      if (array[i][j] == '@') {
        if (isValid(array, i, j)) {
          sum++;
        }
      }
    }
  }

  std::cout << "Sum: " << sum << '\n';

  return 0;
}
