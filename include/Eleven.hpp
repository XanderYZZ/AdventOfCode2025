#ifndef ELEVEN_HPP
#define ELEVEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

using ll = long long;

class Eleven {
public:
    void Run() {
        std::ifstream input_file("inputs/Eleven.txt");

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
        std::vector<std::vector<ll>> vec;
        std::vector<char> ops;

        while (std::getline(file, line)) {
            ll i = 0;
            std::string curr = "";

            for (char c : line) {
                if (c == '*' || c == '+') {
                    ops.emplace_back(c);

                    continue;
                }

                if (c == ' ') {
                    if (curr != "") {
                        HandleNum(vec, curr, i);
                        curr = "";
                        i++;
                    }
                } else {
                    curr += c;
                }
            }

            if (curr != "") {
                HandleNum(vec, curr, i);
            }
        }

        for (int i = 0; i < ops.size(); i++) {
            auto nums = vec[i];
            ll op_result = nums[0];

            for (int j = 1; j < nums.size(); j++) {
                if (ops[i] == '*') {
                    op_result *= nums[j];
                } else {
                    op_result += nums[j];
                }
            }

            sum += op_result;
        }

        return sum;
    }

    void HandleNum(std::vector<std::vector<ll>> &vec, std::string &curr, ll i) {
        if (curr == "") { return; }

        std::size_t pos;
        ll num = std::stoll(curr, &pos);

        if (pos != curr.length()) { return; }

        if (vec.size() <= i) {
            std::vector<ll> new_vec = {num};
            vec.push_back(new_vec);
        } else {
            vec[i].emplace_back(num);
        }
    }
};

#endif