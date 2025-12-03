#include <iostream>
#include <fstream>
#include <string>


unsigned long long pow (unsigned long long base, unsigned long long exponent){
	unsigned long long result = 1;
	for (unsigned long long i = 0; i<exponent; i++) result *= base;
	return result;
}

unsigned long long findBiggestNumber(std::string string, unsigned long long length){
	unsigned long long biggestNumber = 0;
	char current = 0;
	unsigned long long index = 0;

	for (unsigned long long i = 12; i; i--){
		current = string[index];
		for (unsigned long long j=index; j <(length-i+1); j++){
			if (string[j]>current){
				current=string[j];
				index = j;
			}
		}
		biggestNumber +=(current-'0') *pow(10, i-1);
		index++;
	}

	return biggestNumber;
}


int main (int argc, char ** argv){
	std::ifstream file (argv[1]);
	std::string line;
	unsigned long long sum = 0;	

	while (std::getline(file, line)){
		unsigned long long size = line.length();
		sum +=findBiggestNumber(line, size);
}

	std::cout  << sum << '\n';

	return 0;
}
