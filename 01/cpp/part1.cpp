#include <iostream>
#include <string>

using namespace std;

int main() {
	std::string line;
	constexpr std::string_view digits{"0123456789"};

	int32_t total = 0;

	while (getline(cin, line)) {
		const auto first_idx = line.find_first_of(digits);
		const auto last_idx = line.find_last_of(digits);

		const int32_t value = ((line[first_idx] - '0') * 10) + (line[last_idx] - '0');
		total += value;
	}

	cout << "Total = " << total << "\n";
	return 0;
}
