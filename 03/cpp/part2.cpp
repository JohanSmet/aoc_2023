#include <iostream>
#include <string>
#include <charconv>
#include <vector>
#include <unordered_map>

using namespace std;

inline int32_t make_map_index(int32_t x, int32_t y) {
	return (y * 10000) + x;
}

bool is_potential_gear(vector<string> const& schematic, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t &gear_index) {

	for (int32_t y = y1; y <= y2; y += 1) {
		if (y < 0 || y >= schematic.size()) {
			continue;
		}

		for (int32_t x = x1; x <= x2; x += 1) {
			if (x < 0 || x >= schematic[y].size()) {
				continue;
			}

			if (schematic[y][x] == '*') {
				gear_index = make_map_index(x, y);
				return true;
			}
		}
	}

	return false;
}

int main() {
	vector<string>	schematic;

	// read schematic
	string			line;
	while (getline(cin, line)) {
		schematic.push_back(line);
	}

	// process schematic
	constexpr string_view digits{"0123456789"};
	unordered_map<int32_t, std::vector<int32_t>> gears;

	for (int32_t li = 0; li < schematic.size(); ++li) {
		string::size_type string_pos = 0;

		for (auto ni = schematic[li].find_first_of(digits, string_pos); ni != string::npos; ni = schematic[li].find_first_of(digits, string_pos)) {
			auto nj = schematic[li].find_first_not_of(digits, ni);
			if (nj == string::npos) {
				nj = schematic[li].size();
			}
			string_pos = nj;

			int32_t number = 0;
			std::from_chars(schematic[li].c_str() + ni, schematic[li].c_str() + nj, number);

			int32_t gear_index = 0;

			if (is_potential_gear(schematic, ni - 1, li - 1, nj, li + 1, gear_index)) {
				gears[gear_index].push_back(number);
			}
		}
	}

	// accumulate gear ratios
	int32_t total{0};
	for (auto [gear_index, numbers]: gears) {
		if (numbers.size() == 2) {
			total += (numbers[0] * numbers[1]);
		}
	}

	std::cout << "Total = " << total << "\n";
	return 0;
}
