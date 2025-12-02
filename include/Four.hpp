#ifndef FOUR_HPP
#define FOUR_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <thread> 
#include <chrono> 

using ll = long long;

class Four {
public:
    void Run() {
        std::ifstream input_file("inputs/Three.txt");

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
            ll i = 0;

            while (i < line.size()) {
                if (line[i] == '-') { break; }

                i++;
            }

            std::string start_range = line.substr(0, i);
            std::string end_range = line.substr(i + 1, line.size());
            ll start = std::stoll(start_range);
            ll end = std::stoll(end_range);

            for (ll i = start; i <= end; i++) {
                std::string str = std::to_string(i);
                ll size = str.size();
                bool passes = false;
                
                for (int j = 1; j <= size / 2; j++) {
                    if (size % j != 0) { continue; }
                    
                    std::string p = str.substr(0, j);
                    bool matches = true;

                    for (int block = 1; block < size / j; block++) {
                        int start_index = block * j;
                        std::string chunk = str.substr(start_index, j);

                        if (chunk != p) {
                            matches = false;

                            break;
                        }
                    }

                    if (matches) {
                        passes = true;

                        break;
                    }
                }

                if (!passes) { continue; }

                sum += i;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        return sum;
    }
};

#endif