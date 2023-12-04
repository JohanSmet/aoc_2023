#include <iostream>
#include <string>
#include <charconv>

using namespace std;

std::string_view next_token(std::string_view line, std::string::size_type &start_at) {
	auto sub_begin = start_at;
	auto sub_end = line.find_first_of(" :,;", sub_begin);
	if (sub_end == std::string::npos) {
		start_at = line.size();
		return line.substr(sub_begin);
	}

	if (sub_begin != sub_end) {
		start_at = sub_end;
		return line.substr(sub_begin, sub_end - sub_begin);
	} else {
		start_at = sub_end + 1;
		auto result =  line.substr(sub_begin, sub_end - sub_begin + 1);
		if (result == " " || result == ":" || result == ",") {
			return next_token(line, start_at);
		} else {
			return result;
		}

	}
}

int32_t next_token_as_integer(std::string_view line, std::string::size_type &start_at) {
	auto token = next_token(line, start_at);
	int32_t i = 0;
	std::from_chars(token.data(), token.data() + token.size(), i);
	return i;
}


int main() {
	std::string line;

	int32_t total = 0;

	while (getline(std::cin, line)) {
		std::string::size_type line_pos{0};
		int32_t game_number{0};
		int32_t count{0};
		int32_t max_r{0}, max_g{0}, max_b{0};

		for (auto token = next_token(line, line_pos); !token.empty(); token = next_token(line, line_pos)) {
			if (token == "Game") {
				game_number = next_token_as_integer(line, line_pos);
			} else if (token == ";") {
			} else if (token == "red") {
				max_r = std::max(max_r, count);
			} else if (token == "green") {
				max_g = std::max(max_g, count);
			} else if (token == "blue") {
				max_b = std::max(max_b, count);
			} else {
				std::from_chars(token.data(), token.data() + token.size(), count);
			}
				
		}

		if (max_r <= 12 && max_g <= 13 && max_b <= 14) {
			total += game_number;
		}
	}

	std::cout << "Total = " << total << "\n";
	return 0;
}
