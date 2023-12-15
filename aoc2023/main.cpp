#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

std::vector<std::string> read_file(const char* file_path);
int day1_1(std::vector<std::string> input);
int day1_2(const std::vector<std::string> input);

int main(int argc, char** argv) {
	std::cout << day1_1(read_file("day1_1.txt")) << std::endl;
	std::cout<<day1_2(read_file("day1_2.txt"))<<std::endl;
	return 0;
}

std::vector<std::string> read_file(const char* file_path) {
	
	std::fstream file(file_path);

	if (!file.is_open()) {
		std::cerr << "Unable to open file." << file_path << std::endl;
		exit(-1);
	}

	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	file.close();
	file.clear();
	file.seekg(0, std::ios::beg);
	return lines;
}

int day1_1(const std::vector<std::string> input) {
	const char* digits = "0123456789";
	std::size_t sum = 0;
	for(auto line : input){
		uint16_t first_digit = (line[line.find_first_of(digits)] - '0');
		uint16_t last_digit = (line[line.find_last_of(digits)] - '0');
			sum += 10*first_digit + last_digit;
	}
	return sum;
}


// TODO: Something is wrong somewhere in my logic
int day1_2(const std::vector<std::string> input) {
	
	std::vector<std::string> transformed_input;
	
	std::unordered_map<std::string, uint16_t> word_to_digit;
	// +1, cause word_to_digit["wrong_str"] == 0
	word_to_digit["zero"] = 1;
	word_to_digit["one"] = 2;
	word_to_digit["two"] = 3;
	word_to_digit["three"] = 4;
	word_to_digit["four"] = 5;
	word_to_digit["five"] = 6;
	word_to_digit["six"] = 7;
	word_to_digit["seven"] = 8;
	word_to_digit["eight"] = 9;
	word_to_digit["nine"] = 10;

	const uint16_t MIN_WORD_LEN = 3;
	const uint16_t MAX_WORD_LEN = 6;

	// For each row
	for (auto line : input) {
		std::string l;

		// For each char
		for (std::size_t i = 0; i < line.length(); i++) {
			if (isdigit(line[i])) {
				l.append(std::to_string(line[i]));
				continue;
			}
			// check the substring from i to j
			for (int j = MIN_WORD_LEN; j < MAX_WORD_LEN && i + j - 1 < line.length(); j++) {
				auto val = word_to_digit[line.substr(i, j)];
				if (val > 0) {
					// cause the mapping
					val -= 1;

					// put the transformed numbers 
					l.append(std::to_string(val));
					break;
				}
			}
		}
		if(!l.empty())
			transformed_input.push_back(l);
	}

	return day1_1(transformed_input);
}