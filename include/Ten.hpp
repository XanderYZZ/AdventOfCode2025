#ifndef TEN_HPP
#define TEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

using ll = long long;

class Ten {
public:
    void Run() {
        std::ifstream input_file("inputs/Nine.txt");

        if (input_file.is_open()) {
            std::cout << "Opened!\n";
            ll result = ProcessFile(input_file);
            std::cout << "Resulting sum: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    [[nodiscard]]
    ll ProcessFile(std::ifstream& file) {
        ll sum = 0;
        std::string line;
        std::vector<std::pair<ll, ll>> ranges;

        while (std::getline(file, line)) {
            if (line.size() <= 0) { continue; }

            size_t dash_pos = line.find("-");
            bool has_dash = dash_pos != std::string::npos;

            if (!has_dash) { break; }

            std::string first_num = line.substr(0, dash_pos);
            std::string second_num = line.substr(dash_pos + 1);
            ll first = std::stoll(first_num);
            ll second = std::stoll(second_num);
            ranges.push_back({first, second});
        }

        std::vector<std::pair<ll, ll>> merged;
        std::sort(ranges.begin(), ranges.end(), [&](const auto &a, const auto &b) {
            return a.first < b.first;
        });

        merged.push_back(ranges[0]);

        for (int i = 1; i < ranges.size(); i++) {
            const auto &curr = ranges[i];
            auto &last = merged.back();

            if (curr.first > last.second + 1) {
                merged.push_back(curr);
            } else {
                last.second = std::max(last.second, curr.second);
            }
        }

        for (const auto &vec : merged) {
            sum += ((vec.second - vec.first) + 1);
        }

        return sum;
    }
};

#endif