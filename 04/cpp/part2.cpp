#include <algorithm>
#include <iostream>
#include <numeric>
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
	
	std::vector<int32_t> matches;
	std::vector<int32_t> count;

	// parsing
	while (getline(cin, line)) {
		auto numbers = parse_string(line);

		int32_t match = 0;
		for (auto winner : numbers[WINNERS]) {
			match += std::count(numbers[DRAWN].begin(), numbers[DRAWN].end(), winner);
		}
	
		matches.push_back(match);
		count.push_back(1);
	}
	
	// counting copies
	for (int32_t card = 0; card < matches.size(); card += 1) {
		for (int32_t idx = 1; idx <= matches[card]; ++idx) {
			count[card + idx] += count[card];
		}
	}

	int32_t total = std::accumulate(std::begin(count), std::end(count), 0);
	std::cout << "Total = " << total << "\n";
	return 0;
}
