#include <iostream>
#include <string>

using namespace std;

std::string replace_spelled_out_digits(std::string &line) {
	constexpr std::string_view words[] = {
		"zero",
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};

	std::string result{};

	for (string::size_type idx = 0; idx < line.size(); idx += 1) {
		if (std::isdigit(line[idx])) {
			result += line[idx];
			continue;
		} 

		for (int32_t digit = 0; digit <= 9; digit += 1) {
			if (line.compare(idx, words[digit].size(), words[digit]) == 0) {
				result += '0' + digit;
			}
		}
	}

	return result;
}

int main() {
	std::string line;
	constexpr std::string_view digits{"0123456789"};

	int32_t total = 0;

	while (getline(cin, line)) {
		line = replace_spelled_out_digits(line);
		const auto first_idx = line.find_first_of(digits);
		const auto last_idx = line.find_last_of(digits);

		const int32_t value = ((line[first_idx] - '0') * 10) + (line[last_idx] - '0');
		total += value;
	}

	cout << "Total = " << total << "\n";
	return 0;
}
