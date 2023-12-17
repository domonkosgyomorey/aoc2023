#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <sstream>
#include <cctype>

#define AOC2023_FN(fn_name) size_t (fn_name)(std::vector<std::string> input)
#define VEC_OF_STR std::vector<std::string>

VEC_OF_STR split_string(const std::string& s, char delimiter);
VEC_OF_STR read_file(const char* file_path);
std::string ltrim(const std::string& s);
VEC_OF_STR split_numbers(const std::string& input);

AOC2023_FN(day1_1);
AOC2023_FN(day1_2);
AOC2023_FN(day2_1);
AOC2023_FN(day2_2);
AOC2023_FN(day3_1);
AOC2023_FN(day4_1);
AOC2023_FN(day4_2);
AOC2023_FN(day5_1);

int main(int argc, char** argv) {
	//std::cout << day1_1(read_file("day1_1.txt")) << std::endl;
	//std::cout<<day1_2(read_file("day1_2.txt"))<<std::endl;
	//std::cout << day2_1(read_file("day2_1.txt")) << std::endl;
	//std::cout << day2_2(read_file("day2_2.txt")) << std::endl;
	// TODO: correct some miss calculations std::cout << day3_1(read_file("day3_1.txt")) << std::endl;
	//std::cout << day4_1(read_file("day4_1.txt")) << std::endl;
	//std::cout << day4_2(read_file("day4_2.txt")) << std::endl;
	std::cout << day5_1(read_file("day5_1.txt")) << std::endl;
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

VEC_OF_STR split_numbers(const std::string& input) {
	VEC_OF_STR numbers;
	std::stringstream ss(input);
	std::string token;

	while (ss >> token) {
		bool isNumber = true;

		// Ellenõrzés, hogy a token csak számokat tartalmaz-e
		for (char c : token) {
			if (!std::isdigit(c)) {
				isNumber = false;
				break;
			}
		}

		if (isNumber) {
			numbers.push_back(token);
		}
	}

	return numbers;
}

#pragma region Day1

AOC2023_FN(day1_1) {
	const char* digits = "0123456789";
	size_t sum = 0;
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

#pragma endregion

#pragma region Day2

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

#pragma endregion

#pragma region Day3
// TODO: Something is not okay in logicly yet
AOC2023_FN(day3_1) {
	const size_t width = input[0].length();
	const size_t height = input.size();
	uint32_t res = 0;

	std::vector<uint32_t> symbol_pos;
	const char* symbols = " !\"#$%&\'()*+,-/:;<=>?[\\]^_`{|}~";
	const uint16_t symbols_count = 32;

	std::unordered_map<uint32_t, uint32_t> pos_num;

	int32_t i = 0;
	for (auto line : input) {
		for (uint32_t c = 0; c < line.length(); c++) {
			uint32_t l = 0;
			while (l < symbols_count && line[c] != symbols[l++]);
			if (l < symbols_count) {
				symbol_pos.push_back(i);
			}
			i++;
		}
	}
	
	i = 0;
	for (auto line : input) {
		for (uint32_t c = 0; c < line.length(); c++) {
			if (isdigit(line[c])) {
				uint32_t num = 0;
				uint32_t cnt = 0;
				while (c < line.length() && isdigit(line[c])) {
					num = num * 10 + (line[c] - '0');
					c++;
					i++;
					cnt++;
				}
				for (uint32_t m = 0; m < cnt; m++) {
					int v = i - m - 1;
					pos_num[v] = num;
				}
			}
			i++;
		}
	}

	
	for (auto sym_p : symbol_pos) {
		size_t x = sym_p % width;
		size_t y = sym_p / height;
		std::unordered_set<uint32_t> nums;
		for (int32_t j = -1; j < 2; j++) {
			for (int32_t k = -1; k < 2; k++) {
				size_t m = (y + j) * width + x + k;
				nums.insert(pos_num[(unsigned int)m]);
			}
		}
		for (auto num : nums) {
			res += num;
		}
	}
	return res;
}

#pragma endregion

#pragma region Day4
uint32_t day4_1_score_counter(uint32_t prev_score) {
	if (prev_score == 0) {
		return 1;
	}
	else {
		return 2 * prev_score;
	}
}

AOC2023_FN(day4_1) {
	std::unordered_map<std::string, bool> map;

	int total_result = 0;
	int inner_score;
	
	VEC_OF_STR card;
	VEC_OF_STR nums;
	VEC_OF_STR winning_nums;
	VEC_OF_STR our_nums;

	for (auto line : input) {
		map.clear();
		inner_score = 0;
		
		card = split_string(line, ':');
		nums = split_string(card[1], '|');
		winning_nums = split_numbers(nums[0]);
		our_nums = split_numbers(nums[1]);
		
		for (auto n : winning_nums) {
			if(std::stoi(n))
			map[n] = true;
		}
		
		for (auto n : our_nums) {
			if (map[n]) {
				inner_score = day4_1_score_counter(inner_score);
			}
		}
		total_result += inner_score;
	}
	return total_result;
}

AOC2023_FN(day4_2) {
	std::unordered_map<std::string, bool> map;

	// Map for store the number of each card
	std::unordered_map<int, int> dups;

	int number_of_win_number;

	VEC_OF_STR card;
	VEC_OF_STR nums;
	VEC_OF_STR winning_nums;
	VEC_OF_STR our_nums;

	// Init each of the cards number to 1
	for (int i = 0; i < input.size(); i++) {
		dups[i] = 1;
	}

	for (int i = 0; i < input.size(); i++) {
		auto line = input[i];
		map.clear();
		number_of_win_number = 0;

		card = split_string(line, ':');
		nums = split_string(card[1], '|');
		winning_nums = split_numbers(nums[0]);
		our_nums = split_numbers(nums[1]);
		for (auto n : winning_nums) {
			if (std::stoi(n))
				map[n] = true;
		}

		for (auto n : our_nums) {
			if (map[n]) {
				number_of_win_number++;
			}
		}

		// Add the dups[i] amount of card to the "number_of_win_number" next card
		for (int j = 0; j < number_of_win_number && j+i+1 < input.size(); j++) {
			dups[j + i + 1] += dups[i];
		}
	}

	int result = 0;
	for (int i = 0; i < input.size(); i++) {
		result += dups[i];
	}
	return result;
}

#pragma endregion Day4

#pragma region Day5

size_t string_to_number(std::string num) {
	size_t i = 0;
	size_t res = 0;
	while (isdigit(num[i])) {
		res = res * 10 + (num[i] - '0');
		i++;
	}
	return res;
}

typedef struct Mapping {
	size_t src;
	size_t dst;
	size_t range;

	Mapping(std::string line) {
		VEC_OF_STR nums = split_numbers(line);
		dst = string_to_number(nums[0]);
		src = string_to_number(nums[1]);
		range = string_to_number(nums[2]);
	}

} Mapping;

int day5_1_mapping_from_ranges(const std::vector<Mapping> &mappings, long value) {
	for (auto mapping : mappings) {
		if (mapping.src <= value && value < mapping.src + mapping.range) {
			return value + (mapping.dst - mapping.src);
		}
	}
	return value;
}

AOC2023_FN(day5_1) {

	// seed -> soil -> fertilizer -> water -> light -> temperature -> humidity -> location
	const size_t mapping_process_len = 7;
	std::vector<Mapping> mappings[mapping_process_len];

	// dst src range
	const size_t convert_param_len = 3;

	std::vector<size_t> seeds;
	// seeds: 50, 12, ...
	for (auto seed : split_numbers(input[0])) {
		seeds.push_back(string_to_number(seed));
	}

	// Converting state id
	size_t process_id = 0;
	for (size_t i = 3; i < input.size(); i++) {
		auto line = input[i];
		if (line.empty()) {
			process_id++;
			// To skip the empty line, and the next convert label
			i += 2;
			if (i >= input.size()) {
				std::cout << "The input format assumption was wrong" << std::endl;
				exit(-1);
			}
			line = input[i];
		}

		Mapping mapping(line);
		mappings[process_id].push_back(mapping);
	}

	size_t min_location = -1;
	for (auto seed : seeds) {
		// Feedforward the seed
		for (auto convert_state : mappings) {
			seed = day5_1_mapping_from_ranges(convert_state, seed);
		}
		// Store the minimum location value
		if (seed < min_location || min_location == -1) {
			min_location = seed;
		}
	}
	return min_location;
}

#pragma endregion