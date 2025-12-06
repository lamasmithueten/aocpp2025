#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::vector<unsigned long long>>
transpose(const std::vector<std::vector<unsigned long long>> &input) {
  if (input.empty()) {
    return {};
  }

  size_t cols = input[0].size();
  for (const auto &row : input) {
    if (row.size() != cols) {
      throw std::invalid_argument(
          "All rows must have the same number of columns.");
    }
  }

  std::vector<std::vector<unsigned long long>> transposed(
      cols, std::vector<unsigned long long>(input.size()));

  for (size_t i = 0; i < input.size(); ++i) {
    for (size_t j = 0; j < input[i].size(); ++j) {
      transposed[j][i] = input[i][j];
    }
  }

  return transposed;
}

unsigned long long result(std::vector<unsigned long long> line,
                          std::string operation) {
  unsigned long long result = 0;
  size_t size = line.size();
  if (operation[0] == '+') {
    for (size_t i = 0; i < size; i++) {
      result += line[i];
    }
  } else if (operation[0] == '*') {
    result = line[0];
    for (size_t i = 1; i < size; i++) {
      result *= line[i];
    }
  }
  return result;
}

int main(int argc, char **argv) {
  std::ifstream file(argv[1]);
  std::string line;
  std::regex pattern(R"((\d+\.?\d*)|([+*]))");
  std::vector<std::vector<unsigned long long>> values;
  std::vector<std::string> operations;
  unsigned long long sum = 0;

  while (std::getline(file, line)) {
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto words_end = std::sregex_iterator();
    std::vector<unsigned long long> numberMatches;

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
      std::smatch match = *i;
      std::string matched_str = match.str();

      if (std::regex_match(matched_str, std::regex(R"(\d+\.?\d*)"))) {
        numberMatches.push_back(std::stoull(matched_str));
      } else {
        operations.push_back(matched_str);
      }
    }
    if (!numberMatches.empty()) {
      values.push_back(numberMatches);
    }
  }
  values = transpose(values);

  size_t size = values.size();
  for (size_t i = 0; i < size; i++) {
    sum += result(values[i], operations[i]);
  }

  std::cout << "Sum: " << sum << '\n';

  return 0;
}
