#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <thread>
#include <queue>

#define AOC2023_FN(fn_name) size_t (fn_name)(std::vector<std::string> input)
#define AOC2023_SFN(fn_name) int64_t (fn_name)(std::vector<std::string> input)
#define VEC_OF_STR std::vector<std::string>
#define PAIR std::pair<size_t, size_t>
#define VEC_OF_PAIR std::vector<PAIR>

#pragma region UtilsDefinition

VEC_OF_STR split_string(const std::string& s, char delimiter);
VEC_OF_STR read_file(const char* file_path);
std::string ltrim(const std::string& s);
std::string trim(std::string& str, const char* spec_char_set);
size_t convert_digits_to_number(const std::string& s);
VEC_OF_STR split_numbers(const std::string& input);
size_t string_to_number(std::string num);

#pragma endregion

#pragma region FunctionDefinitions

AOC2023_FN(day1_1);
AOC2023_FN(day1_2);

AOC2023_FN(day2_1);
AOC2023_FN(day2_2);

AOC2023_FN(day3_1);

AOC2023_FN(day4_1);
AOC2023_FN(day4_2);

AOC2023_FN(day5_1);
AOC2023_FN(day5_2);

AOC2023_FN(day6_1);
AOC2023_FN(day6_2);

AOC2023_FN(day7_1);

AOC2023_FN(day8_1);
AOC2023_FN(day8_2);

AOC2023_FN(day9_1);
AOC2023_SFN(day9_2);

AOC2023_FN(day10_1);
AOC2023_FN(day10_2);

AOC2023_FN(day11_1);
AOC2023_FN(day11_2);

#pragma endregion

int main(int argc, char** argv) {
	//std::cout << day1_1(read_file("day1_1.txt")) << std::endl;
	//std::cout<<day1_2(read_file("day1_2.txt"))<<std::endl;
	//std::cout << day2_1(read_file("day2_1.txt")) << std::endl;
	//std::cout << day2_2(read_file("day2_2.txt")) << std::endl;
	//std::cout << day3_1(read_file("day3_1.txt")) << std::endl;
	//std::cout << day4_1(read_file("day4_1.txt")) << std::endl;
	//std::cout << day4_2(read_file("day4_2.txt")) << std::endl;
	//std::cout << day5_1(read_file("day5_1.txt")) << std::endl;
	//std::cout << day5_2(read_file("day5_2.txt")) << std::endl;
	//std::cout << day6_1(read_file("day6_1.txt")) << std::endl;
	//std::cout << day6_2(read_file("day6_2.txt")) << std::endl;
	//std::cout << day7_1(read_file("day7_1.txt")) << std::endl;
	//std::cout << day8_1(read_file("day8_1.txt")) << std::endl;
	//std::cout << day8_2(read_file("day8_2.txt")) << std::endl;
	//std::cout << day9_1(read_file("day9_1.txt")) << std::endl;
	//std::cout << day9_2(read_file("day9_2.txt")) << std::endl;
	std::cout << day10_1(read_file("day10_1.txt")) << std::endl;
	//std::cout << day11_1(read_file("day11_1.txt")) << std::endl;
	return 0;
}

#pragma region Utils

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

std::string trim(std::string& str ,const char* spec_char_set) {
	std::string cs = " \t\r\n";
	cs.append(spec_char_set);
	size_t start = str.find_first_not_of(cs);
	if (start == std::string::npos) {
		return "";
	}

	size_t end = str.find_last_not_of(cs);
	return str.substr(start, end - start + 1);
}

size_t convert_digits_to_number(const std::string& s) {
	size_t num = 0;
	for (auto c : s) {
		if (isdigit(c)) {
			num = num * 10 + (c - '0');
		}
	}
	return num;
}

VEC_OF_STR split_numbers(const std::string& input) {
	VEC_OF_STR numbers;
	std::stringstream ss(input);
	std::string token;

	while (ss >> token) {
		bool isNumber = true;
		
		if (!(token.empty() || std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1])))) {
			isNumber = false;
		}

		if (isNumber) {
			numbers.push_back(token);
		}
	}

	return numbers;
}

size_t string_to_number(std::string num) {
	size_t i = 0;
	size_t res = 0;
	bool neg = false;
	if (num[i] == '-') {
		neg = true;
		i++;
	}
	while (isdigit(num[i])) {
		res = res * 10 + (num[i] - '0');
		i++;
	}
	return res*(neg?-1:1);
}

#pragma endregion

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

#pragma endregion

#pragma region Day5

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

	Mapping(size_t src, size_t range) : src(src), range(range) {}

} Mapping;

size_t day5_1_mapping_from_ranges(const std::vector<Mapping> &mappings, size_t value) {
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

std::vector<Mapping> merge_ranges(std::vector<Mapping> ranges) {
	std::vector<Mapping> merged_ranges;

	if (ranges.empty()) {
		return merged_ranges;
	}

	std::vector<Mapping> sorted_ranges = ranges;
	std::sort(sorted_ranges.begin(), sorted_ranges.end(), [](const Mapping& a, const Mapping& b) {
		return a.src < b.src;
		});

	Mapping currentRange = sorted_ranges[0];
	for (size_t i = 1; i < sorted_ranges.size(); ++i) {
		if (currentRange.src + currentRange.range >= sorted_ranges[i].src) {
			currentRange.range = std::max(currentRange.src + currentRange.range, sorted_ranges[i].src + sorted_ranges[i].range) - currentRange.src;
		}
		else {
			merged_ranges.push_back(currentRange);
			currentRange = sorted_ranges[i];
		}
	}

	merged_ranges.push_back(currentRange);

	return merged_ranges;
}

// TODO: We need extreme optimization to run it
AOC2023_FN(day5_2) {
	// start, range
	// example =>  seeds: 87 13
	
	VEC_OF_STR ranges = split_numbers(input[0]);
	std::vector<Mapping> num_ranges;
	for (int i = 0; i < ranges.size(); i+=2) {
		Mapping mapping(string_to_number(ranges[i]), string_to_number(ranges[i + 1]));
		num_ranges.push_back(mapping);
	}

	num_ranges = merge_ranges(num_ranges);

	std::ostringstream seeds;
	for (size_t i = 0; i < num_ranges.size(); i++) {
		for(size_t j = 0; j < num_ranges[i].range; j++)
			seeds << (std::to_string(num_ranges[i].src + j) + " ");
	}
	input[0] = seeds.str();
	return day5_1(input);
}

#pragma endregion

#pragma region Day6

AOC2023_FN(day6_1) {
	size_t result = 1;

	auto str_times = split_numbers(input[0]);
	auto str_record_dists = split_numbers(input[1]);
	for (int i = 0; i < str_times.size(); i++) {
		size_t time_cap = string_to_number(str_times[i]);
		size_t record_distance = string_to_number(str_record_dists[i]);

		size_t possible_states = 0;
		for (int j = 0; j < time_cap; j++) {
			possible_states += (j * (time_cap-j) > record_distance);
		}
		result *= possible_states;
	}
	return result;
}

AOC2023_FN(day6_2) {
	size_t time_cap = convert_digits_to_number(input[0]);
	size_t record_distance = convert_digits_to_number(input[1]);

	size_t possible_states_count = 0;

	for (int i = 0; i < time_cap; i++)
		possible_states_count += (i * (time_cap - i) > record_distance);

	return possible_states_count;
}

#pragma endregion

#pragma region Day7

AOC2023_FN(day7_1) {
	size_t result = 0;

	const uint32_t hand_type_len = 7;
	std::vector<std::pair<std::string, size_t>> type_of_hand_and_bid[hand_type_len];
	static std::string strength_order = "AKQJT98765432";
	size_t hand_count = input.size();

	for (auto line : input) {
		std::unordered_map<char, size_t> card_count;
		VEC_OF_STR splitted_input = split_string(line, ' ');
		std::string hand = splitted_input[0];
		size_t bid = string_to_number(splitted_input[1]);
		
		for (auto c : hand) {
			if (card_count.contains(c)) {
				card_count[c]++;
			} else {
				card_count[c] = 1;
			}
		}

		bool five = false, four = false, three = false;
		size_t pair_cntr = 0;
		for (auto pair : card_count) {
			switch (pair.second) {
			case 5:
				five = true;
				break;
			case 4:
				four = true;
				break;
			case 3:
				three = true;
				break;
			case 2:
				pair_cntr++;
				break;
			default:
				break;
			}
		}
		if (five) {
			type_of_hand_and_bid[0].push_back(std::make_pair(hand, bid));
		}
		else if (four) {
			type_of_hand_and_bid[1].push_back(std::make_pair(hand, bid));
		}
		else if (three && pair_cntr > 0) {
			type_of_hand_and_bid[2].push_back(std::make_pair(hand, bid));
		}
		else if (three) {
			type_of_hand_and_bid[3].push_back(std::make_pair(hand, bid));
		}
		else if (pair_cntr > 1) {
			type_of_hand_and_bid[4].push_back(std::make_pair(hand, bid));
		}
		else if (pair_cntr > 0) {
			type_of_hand_and_bid[5].push_back(std::make_pair(hand, bid));
		}
		else {
			type_of_hand_and_bid[6].push_back(std::make_pair(hand, bid));
		}
	}

	for (size_t i = 0; i < hand_type_len; i++) {
		std::sort(type_of_hand_and_bid[i].begin(), type_of_hand_and_bid[i].end(), [](std::pair<std::string, size_t>& a, std::pair<std::string, size_t>& b) {
			for (int j = 0; j < a.first.length() && j < b.first.length(); j++) {
				if (a.first[j] != b.first[j]) {
					return strength_order.find(a.first[j]) < strength_order.find(b.first[j]);
				}
			}
			return a.first.length() < b.first.length();
		});
		for (auto bid : type_of_hand_and_bid[i]) {
			result += (hand_count * bid.second);
			hand_count--;
		}
	}

	return result;
}

#pragma endregion


#pragma region Day8

AOC2023_FN(day8_1) {
	std::string instruction = input[0];

	const char L = 0;
	const char R = 1;

	// Lookup table
	std::unordered_map<std::string, size_t> mapping;
	std::vector<std::pair<std::string, std::string>> left_right_for_each_row;

	// i=2 ===> skip the instructions and the empty line
	for (int i = 2; i < input.size(); i++) {
		std::string line = input[i];
		VEC_OF_STR part = split_string(line, '=');
		mapping[trim(part[0], "")] = i - 2;	// cause the padding
		VEC_OF_STR params = split_string(trim(part[1], "()"), ',');
		left_right_for_each_row.push_back(std::make_pair(params[0], trim(params[1], "")));
	}
	/**/
	std::string cursor = "AAA";
	size_t counter = 0;
	while (cursor != "ZZZ") {
		for (auto c : instruction) {
			if (c == 'L') {
				cursor = left_right_for_each_row[mapping[cursor]].first;
			}
			else {
				cursor = left_right_for_each_row[mapping[cursor]].second;
			}
			counter++;
			if (cursor == "ZZZ") {
				break;
			}
		}
	}
	return counter;
}

// TODO: So Slow
AOC2023_FN(day8_2) {
	std::string instruction = input[0];

	const char L = 0;
	const char R = 1;

	// Lookup table
	std::unordered_map<std::string, size_t> mapping;
	std::vector<std::pair<std::string, std::string>> left_right_for_each_row;

	VEC_OF_STR starts;

	// i=2 ===> skip the instructions and the empty line
	for (int i = 2; i < input.size(); i++) {
		std::string line = input[i];
		VEC_OF_STR part = split_string(line, '=');
		part[0] = trim(part[0], "");
		mapping[part[0]] = i - 2;	// cause the padding
		if (part[0][2] == 'A') {
			starts.push_back(part[0]);
		}
		VEC_OF_STR params = split_string(trim(part[1], "()"), ',');
		left_right_for_each_row.push_back(std::make_pair(params[0], trim(params[1], "")));
	}
	size_t counter = 0;
	while (true) {
		for (auto c : instruction) {
			if (c == 'L') {
				for (int i = 0; i < starts.size(); i++) {
					starts[i] = left_right_for_each_row[mapping[starts[i]]].first;
				}
			}
			else {
				for (int i = 0; i < starts.size(); i++) {
					starts[i] = left_right_for_each_row[mapping[starts[i]]].second;
				}
			}
			counter++;
			bool exit = true;
			for (int i = 0; i < starts.size(); i++) {
				if (starts[i][2] != 'Z') {
					exit = false;
					break;
				}
			}
			if (exit) {
				return counter;
			}
		}
		if (!(counter % 100000)) {
			std::cout << counter << std::endl;
		}
	}
	return counter;
}

#pragma endregion

#pragma region Day9

AOC2023_FN(day9_1) {
	int64_t result = 0;
	for (auto line : input) {
		VEC_OF_STR str_nums = split_numbers(line);
		std::vector<std::vector<int64_t>> rows;
		std::vector<int64_t> vec;
		for (auto sn : str_nums) {
			vec.push_back(string_to_number(sn));
		}
		rows.push_back(vec);
		while (true) {
			std::vector<int64_t> previous = rows[rows.size() - 1];
			std::vector<int64_t> new_vec;

			for (size_t i = 0; i < previous.size()-1; i++) {
				new_vec.push_back(previous[i + 1] - previous[i]);
			}

			rows.push_back(new_vec);

			bool exit = true;
			for (auto n : rows[rows.size() - 1]) {
				if (n != 0) {
					exit = false;
					break;
				}
			}
			if (exit) {
				break;
			}
		}
		// We know the last row is full zero, so we put one more zero there
		rows[rows.size() - 1].push_back(0);

		for (size_t i = rows.size() - 1; i >= 1; i--) {
			// without & , c++ just copy the data from the right-side
			std::vector<int64_t>& row = rows[i];
			std::vector<int64_t>& prev_row = rows[i-1];
			prev_row.push_back(row[row.size() - 1] + prev_row[prev_row.size() - 1]);
		}
		result += rows[0][rows[0].size() - 1];
	}
	return result;
}

// The return value signed
//      |
//      V
AOC2023_SFN(day9_2) {
	int64_t result = 0;
	for (auto line : input) {
		VEC_OF_STR str_nums = split_numbers(line);
		std::vector<std::vector<int64_t>> rows;
		std::vector<int64_t> vec;
		for (auto sn : str_nums) {
			vec.push_back(string_to_number(sn));
		}
		rows.push_back(vec);
		while (true) {
			std::vector<int64_t> previous = rows[rows.size() - 1];
			std::vector<int64_t> new_vec;

			for (size_t i = 0; i < previous.size() - 1; i++) {
				new_vec.push_back(previous[i + 1] - previous[i]);
			}

			rows.push_back(new_vec);

			bool exit = true;
			for (auto n : rows[rows.size() - 1]) {
				if (n != 0) {
					exit = false;
					break;
				}
			}
			if (exit) {
				break;
			}
		}
		// We know the last row is full zero, so we put one more zero there
		rows[rows.size() - 1].push_back(0);

		for (size_t i = rows.size() - 1; i >= 1; i--) {
			// without & , c++ just copy the data from the right-side
			std::vector<int64_t>& row = rows[i];
			std::vector<int64_t>& prev_row = rows[i - 1];
			prev_row.insert(prev_row.begin(), prev_row[0] - row[0]);
		}
		result += rows[0][0];
	}
	return result;
}

#pragma endregion

#pragma region Day10

struct Graph {
	std::unordered_map<size_t, std::vector<size_t>> adjacency_list;

	void addEdge(size_t u, size_t v) {
		adjacency_list[u].push_back(v);
	}

	std::unordered_map<size_t, size_t> BFS(size_t start) {
		std::unordered_map<size_t, size_t> distances;
		std::queue<size_t> q;
		std::vector<size_t> f;

		q.push(start);
		distances[start] = 0;

		while (!q.empty()) {
			size_t current = q.front();
			q.pop();

			for (size_t neighbor : adjacency_list[current]) {
				bool found = false;
				for (int i = 0; i < f.size(); i++) {
					if (f[i] == neighbor) {
						found = true;
						break;
					}
				}
				if (!found) {
					q.push(neighbor);
					distances[neighbor] = distances[current] + 1;
					f.push_back(neighbor);
				}
			}
		}

		return distances;
	}
};


AOC2023_FN(day10_1) {

	size_t start = {0};

	Graph graph;

	for (size_t i = 0; i < input.size(); i++) {
		std::string& line = input.at(i);
		for (size_t j = 0; j < line.size(); j++) {
			size_t idx = i * line.length()+j;
			switch (line[j]) {
			case 'S':
				start = idx;
				graph.addEdge(idx, idx - input.size());
				graph.addEdge(idx, idx + input.size());
				graph.addEdge(idx, idx - 1);
				graph.addEdge(idx, idx + 1);
				break;
			case '|':
				graph.addEdge(idx, idx-input.size());
				graph.addEdge(idx, idx+input.size());
				break;
			case '-':
				graph.addEdge(idx, idx-1);
				graph.addEdge(idx, idx+1);
				break;
			case 'L':
				graph.addEdge(idx, idx+1);
				graph.addEdge(idx, idx-input.size());
				break;
			case 'J':
				graph.addEdge(idx, idx-1);
				graph.addEdge(idx, idx - input.size());
				break;
			case '7':
				graph.addEdge(idx, idx - 1);
				graph.addEdge(idx, idx + input.size());
				break;
				break;
			case 'F':
				graph.addEdge(idx, idx + 1);
				graph.addEdge(idx, idx + input.size());
				break;
			default:
				break;
			}
		}
	}

	std::unordered_map<size_t, size_t> result = graph.BFS(start);
	size_t max_dist = 0;
	for (auto pair : result) {
		if (graph.adjacency_list[pair.first].size() != 2) {
			continue;
		}
		// We know, each node must have just 2 neighbour
		size_t neigh1_dist = result[graph.adjacency_list[pair.first][0]];
		size_t neigh2_dist = result[graph.adjacency_list[pair.first][1]];
		if (neigh1_dist <= pair.second && neigh2_dist <= pair.second) {
			max_dist = pair.second;
		}
	}
	return max_dist;
}

#pragma endregion

#pragma region Day11

AOC2023_FN(day11_1) {
	std::vector<char> empty_col;
	
	VEC_OF_STR expanded_univierse;

	size_t num_of_galaxy = 0;
	std::unordered_map<size_t, PAIR> galaxy_lookup;
	
	for (size_t i = 0; i < input[0].length(); i++) {
		empty_col.push_back(1);
	}
	for (size_t i = 0; i < input.size(); i++) {
		std::string line = input[i];
		size_t j = 0;
		bool good = false;
		for (; j < line.length(); j++) {
			empty_col[j] *= (line[j] == '.');
			if (line[j] != '.') {
				good = true;
			}
		}
		expanded_univierse.push_back(line);
		if (!good) {
			expanded_univierse.push_back(line);
		}
	}
	for (int j = empty_col.size()-1; j >= 0; j--) {
		for (size_t i = 0; i < expanded_univierse.size(); i++) {
			std::string& line = expanded_univierse[i];
			if (empty_col[j]) {
				line.insert(j, ".");
			}
		}
	}
	
	for (int i = 0; i < expanded_univierse.size(); i++) {
		for (int j = 0; j < expanded_univierse[i].size(); j++) {
			if (expanded_univierse[i][j] == '#') {
				galaxy_lookup[num_of_galaxy++] = std::make_pair(i, j);
			}
		}
	}

	int k = 1;
	for (auto l : expanded_univierse) {
		for (auto c : l) {
			std::cout << c;
		}
		std::cout << std::endl;
	}

	size_t res = 0;
	for (int i = 0; i < num_of_galaxy-1; i++) {
		for (int j = i+1; j < num_of_galaxy; j++) {
			PAIR f = galaxy_lookup[i];
			PAIR s = galaxy_lookup[j];
			res += (llabs(f.first - s.first) + llabs(f.second - s.second));
			
		}
	}
	return res;
}

#pragma endregion
