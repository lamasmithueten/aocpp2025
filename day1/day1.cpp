#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {

  std::ifstream inputFile(argv[1]);
  std::string line;
  std::vector<char> direction;
  std::vector<int> amount;
  int passwd = 0;
  int dial = 50;
  while (std::getline(inputFile, line)) {
    direction.push_back(line[0]);
    amount.push_back(std::stoi(line.substr(1)));
  }
  int size = direction.size();
  for (int i = 0; i < size; i++) {
    if (direction[i] == 'L') {
      dial = (dial - amount[i] + 100) % 100;
    } else {
      dial = (dial + amount[i]) % 100;
    }
    if (!dial)
      passwd++;
    //		std::cout << dial << '\n';
  }
  std::cout << "Password: " << passwd << '\n';

  return 0;
}
