#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <vector>
#include <unordered_map>

#define AOC2023_FN(fn_name) int (fn_name)(std::vector<std::string> input)
#define VEC_OF_STR std::vector<std::string>

VEC_OF_STR split_string(const std::string& s, char delimiter);
VEC_OF_STR read_file(const char* file_path);
std::string ltrim(const std::string& s);
AOC2023_FN(day1_1);
AOC2023_FN(day1_2);
AOC2023_FN(day2_1);
AOC2023_FN(day2_2);

int main(int argc, char** argv) {
	//std::cout << day1_1(read_file("day1_1.txt")) << std::endl;
	//std::cout<<day1_2(read_file("day1_2.txt"))<<std::endl;
	//std::cout << day2_1(read_file("day2_1.txt")) << std::endl;
	std::cout << day2_2(read_file("day2_2.txt")) << std::endl;
	return 0;
}

VEC_OF_STR split_string(const std::string& s, char delimiter) {
	VEC_OF_STR tokens;
	size_t start = 0, end = 0;

	while ((end = s.find(delimiter, start)) != std::string::npos) {
		tokens.push_back(s.substr(start, end - start));
		start = end + 1;
	}

	tokens.push_back(s.substr(start));
	return tokens;
}


VEC_OF_STR read_file(const char* file_path) {
	
	std::fstream file(file_path);

	if (!file.is_open()) {
		std::cerr << "Unable to open file." << file_path << std::endl;
		exit(-1);
	}

	VEC_OF_STR lines;
	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}

	file.close();
	file.clear();
	file.seekg(0, std::ios::beg);
	return lines;
}

std::string ltrim(const std::string& s) {
	size_t start = s.find_first_not_of(" \t\f\v\n\r");

	if (start != std::string::npos) {
		return s.substr(start);
	}

	return "";
}

AOC2023_FN(day1_1) {
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
AOC2023_FN(day1_2) {
	
	VEC_OF_STR transformed_input;
	
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

AOC2023_FN(day2_1) {
	int res = 0;
	int id = 1;
	for (auto line : input) {
		VEC_OF_STR line_spl = split_string(line, ':');
		VEC_OF_STR games = split_string(line_spl[1], ';');
		for (auto game : games) {
			VEC_OF_STR inner_games = split_string(game, ',');
			std::unordered_map<std::string, uint32_t> score;
			score["blue"] = 0;
			score["green"] = 0;
			score["red"] = 0;
			for (auto inner_game : inner_games) {
				inner_game = ltrim(inner_game);
				VEC_OF_STR params = split_string(inner_game, ' ');
				score[params[1]] += std::stoi(params[0]);
			}
			if (score["blue"] > 14 || score["green"] > 13 || score["red"] > 12) {
				goto end_game;
			}
		}
		res += id;
	end_game:
		id++;
	}
	return res;
}

AOC2023_FN(day2_2) {
	int res = 0;
	for (auto line : input) {
		VEC_OF_STR line_spl = split_string(line, ':');
		VEC_OF_STR games = split_string(line_spl[1], ';');
		std::unordered_map<std::string, uint32_t> score;
		score["blue"] = 0;
		score["green"] = 0;
		score["red"] = 0;
		for (auto game : games) {
			VEC_OF_STR inner_games = split_string(game, ',');
			for (auto inner_game : inner_games) {
				inner_game = ltrim(inner_game);
				VEC_OF_STR params = split_string(inner_game, ' ');
				uint32_t num_of_col = std::stoi(params[0]);
				if (score[params[1]] < num_of_col) {
					score[params[1]] = num_of_col;
				}
			}
		}
		res += score["blue"]*score["green"]*score["red"];
	}
	return res;
}