#ifndef SEVENTEEN_HPP
#define SEVENTEEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using ll = long long;

class Seventeen {
public:
    void Run() {
        std::ifstream input_file("inputs/Seventeen.txt");

        if (input_file.is_open()) {
            ll result = ProcessFile(input_file);
            std::cout << "Resulting area: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    [[nodiscard]]
    ll ProcessFile(std::ifstream& file) {
        ll max_area = 0;
        std::string line; 
        std::vector<std::pair<ll, ll>> v;

        while (std::getline(file, line)) {
            size_t comma_pos = line.find(",");
            std::string first_num = line.substr(0, comma_pos);
            std::string second_num = line.substr(comma_pos + 1);
            ll first = std::stoll(first_num);
            ll second = std::stoll(second_num);
            v.push_back({first, second});
        }

        for (ll i = 0; i < v.size(); i++) {
            for (ll j = 0; j < v.size(); j++) {
                if (i == j) { continue; }

                auto p = v[i];
                auto p2 = v[j];
                ll abs_x = std::abs(p.first - p2.first) + 1;
                ll abs_y = std::abs(p.second - p2.second) + 1;
                ll area = abs_x * abs_y;
                max_area = std::max(max_area, area);
            }
        }

        return max_area; 
    }
};

#endif