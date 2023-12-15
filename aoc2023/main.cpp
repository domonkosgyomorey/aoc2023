#include <iostream>
#include <numeric>
#include <string>
#include <fstream>
#include <vector>

std::vector<std::string> read_file(const char* file_path);
int day1_1(std::vector<std::string> input);

int main(int argc, char** argv) {
	std::cout << "Hello, World!" << std::endl;
	std::cout<<day1_1(read_file("day1_1.txt"))<<std::endl;
	return 0;
}

std::vector<std::string> read_file(const char* file_path) {
	
	std::vector<std::string> res;
	std::ifstream file(file_path);
	if (!file) {
		std::cout << "Unable ot open file :" << file_path << std::endl;
		exit(-1);
	}
	std::string str;
	while (std::getline(file, str)) {
		res.push_back(str);
	}
	return res;
}

int day1_1(const std::vector<std::string> input) {
	const char* digits = "0123456789";
	std::size_t sum = 0;
	for(auto line : input){
			int first_digit = (line.at(line.find_first_of(digits)) - '0');
			int last_digit = (line.at(line.find_last_of(digits)) - '0');
			sum += 10*first_digit + last_digit;
	}
	return sum;
}
