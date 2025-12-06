#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int countColumns(const std::string& str, const std::regex& pattern){
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), pattern);
    auto words_end = std::sregex_iterator();
	
	int columns = std::distance(words_begin, words_end);

    return columns;
}

std::vector<int> calculateWidths(std::ifstream& file, int columns, const std::regex& pattern){
	std::vector <int> widths(columns, 0);
	std::string line;
	while (std::getline(file,line))	{
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
		auto words_end = std::sregex_iterator();
		int count = 0;
		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
				std::smatch match = *i;
				std::string matched_str = match.str();
				int size = matched_str.length();
				if(size > widths[count]){
					widths[count] = size;
				}
				count++;
		}
		
	}

	file.clear();
	file.seekg(0);
	return widths;
}

std::vector <std::vector<std::string>> transpose(const std::vector <std::vector <std::string>> matrix){
    if (matrix.empty()) return {};

    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    std::vector <std::vector<std::string>> transposed(cols, std::vector<std::string>(rows));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}


std::vector<std::vector<unsigned long long>> convert(const std::vector <std::vector<std::string>>& matrix, std::vector<int> widths){
	std::vector<std::vector<std::string>> convertedMatrix;
	std::vector<std::vector<unsigned long long>> numberMatrix;
	int count=0;
	
	for (std::vector<std::string> line: matrix){
/*		for (std::string lol: line){
			std::cout << lol << ' ';
		}
		std::cout << '\n';*/
		
		int size_vector = line.size();
		int max_string_size = widths[count++];
		std::vector<std::string> newLine;
		for (int i = 0; i<max_string_size; i++){
			std::string newString (size_vector, ' ');
			newLine.push_back(newString);
		}
		std::cout << "Size_vector: " << size_vector << " max_string_size: " << max_string_size<< '\n';
		for (int i = 0; i< max_string_size; i++){
			for (int j = 0; j < size_vector; j++){
				newLine[i][j]=line[j][i];
			}
		}
		convertedMatrix.push_back(newLine);
	}
	
	for (std::vector<std::string> i: convertedMatrix){
		for (std::string j: i){
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
	
	for (std::vector<std::string> i: convertedMatrix){
		std::vector <unsigned long long> numberVector;
		for (std::string j: i){
			numberVector.push_back(std::stoull(j));
		}
		numberMatrix.push_back(numberVector);
	}



	return numberMatrix;
}

unsigned long long result (std::vector<unsigned long long> line, std::string operation){
	unsigned long long result = 0;
	size_t size = line.size();
	if (operation[0] == '+'){
		for (size_t i = 0; i<size; i++){
			result += line[i];
		}
	} else if (operation[0] == '*'){
		result = line[0];
		for (size_t i =1; i < size; i++){
			result *=line[i];
		}
	}
	return result;
}

int main(int argc, char **argv){
	std::ifstream file(argv[1]);
	std::string line;
	std::vector <std::vector<std::string>> values;
	std::vector <std::vector<unsigned long long>> convertedValues;
	std::vector <std::string> operations;
	std::regex pattern("[+*]");
	std::regex numPattern("[0-9]+");
	unsigned long long sum=0;

	std::getline(file, line);
	int columns=countColumns(line, numPattern);

	file.clear();
	file.seekg(0);
	std::vector <int> widths = calculateWidths(file, columns, numPattern);
	
	
	while(std::getline(file, line)){
		auto words_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
		auto words_end = std::sregex_iterator();
		std::vector <std::string> numberLine;
		if (words_begin == words_end) {
			int count = 0;
			int size = line.size();
			for (int i = 0; i<size; i++){
				std::string ln (widths[count], ' ');
				for (int j = 0; j<widths[count]; j++){
					ln[j] = line[i+j];
				}
				numberLine.push_back(ln);
				i+=widths[count];
				count++;
			}
			values.push_back(numberLine);
			
		} else {
	            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			std::string matched_str = match.str();
			operations.push_back(matched_str);
			}
		}
	}
	values=transpose(values);
	

	for (std::vector i: values){
		for (std::string j: i){
			std::cout << j <<' ';
		}
		std::cout << '\n';
	}
	for (std::string i: operations){
		std::cout << i << ' ';
	}
	std::cout << '\n';

	std::cout << "Columns: " << columns << '\n';
	for (int i: widths){
		std::cout << "Width: " << i << '\n';
	}
	convertedValues = convert(values, widths);
	size_t size= convertedValues.size();
	for (size_t i=0; i<size; i++){
		sum += result(convertedValues[i], operations[i]);
	}

	std::cout << "Sum: " << sum << '\n';
	
	return 0;
}
