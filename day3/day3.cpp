#include <iostream>
#include <fstream>
#include <string>

int findBiggestNumber(std::string string, int length){
	int biggestNumber = 0;
	char current = string[0];
	int index = 1;
	for (int i =0; i<length-1; i++){
		if (string[i]>current){
			current = string[i];
			index = i+1;
		}
	}
	biggestNumber = (current- '0') *10;
	current = string[index];
	for (int i = index; i<length;i++){
		if (string[i]>current) current = string[i];
	}

	biggestNumber += current - '0';
	
	return biggestNumber;
}


int main (int argc, char ** argv){
	std::ifstream file (argv[1]);
	std::string line;
	int sum = 0;	

	while (std::getline(file, line)){
		int size = line.length();
		sum +=findBiggestNumber(line, size);
}

	std::cout << sum << '\n';

	return 0;
}
