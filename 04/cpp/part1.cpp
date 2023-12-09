#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

constexpr int32_t WINNERS = 0;
constexpr int32_t DRAWN = 1;

std::vector<std::vector<int32_t>> parse_string(std::string s) {
	std::vector<std::vector<int>> result(1);
	std::stringstream ss(s);
	std::string token;

	ss >> token;	// Card
	ss >> token;	// <number>:

	while (ss >> token) {
		if (token == "|") {
			result.emplace_back();
		} else {
			result.back().push_back(std::stoi(token));
		}
	}

	return result;
}

int main() {
	string	line;
	
	int total = 0;

	while (getline(cin, line)) {
		auto numbers = parse_string(line);

		int32_t matches = 0;
		for (auto winner : numbers[WINNERS]) {
			matches += std::count(numbers[DRAWN].begin(), numbers[DRAWN].end(), winner);
		}

		if (matches > 0) {
			total += 1 << (matches - 1);
		}
		
	}

	std::cout << "Total = " << total << "\n";
	return 0;
}
