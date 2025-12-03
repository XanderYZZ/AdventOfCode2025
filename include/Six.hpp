#ifndef SIX_HPP
#define SIX_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread> 
#include <chrono> 

using ll = long long;

class Six {
public:
    void Run() {
        std::ifstream input_file("inputs/Five.txt");

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

        while (std::getline(file, line)) {
            std::string result;
            result.reserve(12);
            int needed = 12; // The amount of digits needed.
            int i = 0;

            while (needed > 0) {
                int remaining = line.size() - i;
                int limit = remaining - needed; // How far ahead I can search through.

                char best_digit = '0';
                int best_index = i;

                for (int j = i; j <= i + limit; j++) {
                    if (line[j] <= best_digit) { continue; }

                    best_digit = line[j];
                    best_index = j;

                    if (best_digit == '9') { break; }
                }

                result.push_back(best_digit);
                i = best_index + 1;
                needed--;
            }

            ll num = std::stoll(result);
            sum += num;

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        return sum;
    }
};

#endif