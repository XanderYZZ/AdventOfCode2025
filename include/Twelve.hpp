#ifndef TWELVE_HPP
#define TWELVE_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

using ll = long long;

class Twelve {
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
        std::vector<char> ops;
        std::vector<std::vector<char>> chars;

        while (std::getline(file, line)) {
            ll c_num = 0;

            for (char c : line) {
                if (c == '*' || c == '+') {
                    ops.emplace_back(c);

                    continue;
                }

                if (chars.size() <= c_num) {
                    chars.push_back({c});
                } else {
                    chars[c_num].emplace_back(c);
                }

                c_num++;
            }
        }

        ll curr = 0;
        std::size_t op_index = 0;
    
        for (int i = 0; i < chars.size(); i++) {
            std::string comb = "";
            bool all_spaces = true;

            for (const char &c : chars[i]) {
                if (!std::isdigit(c)) { continue; }

                comb += c;
                all_spaces = false;
            }

            if (!all_spaces) {
                ll num = std::stoll(comb);

                if (curr == 0) {
                    curr = num;
                } else {
                    if (ops[op_index] == '+') {
                        curr += num;
                    } else {
                        curr *= num;
                    }
                }
            } else {
                sum += curr;
                op_index++;
                curr = 0;
            }
        }

        if (curr != 0) {
            sum += curr;
        }

        return sum;
    }
};

#endif