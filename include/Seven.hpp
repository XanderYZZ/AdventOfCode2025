#ifndef SEVEN_HPP
#define SEVEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

class Seven {
public:
    void Run() {
        std::ifstream input_file("inputs/Seven.txt");

        if (input_file.is_open()) {
            std::cout << "Opened!\n";
            int result = ProcessFile(input_file);
            std::cout << "Resulting sum: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    [[nodiscard]]
    int ProcessFile(std::ifstream& file) {
        int sum = 0;
        std::string line;
        std::vector<std::vector<char>> grid;
        std::vector<std::vector<int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
        };

        while (std::getline(file, line)) {
            std::vector<char> inner;

            for (const char &c : line) {
                inner.emplace_back(c);
            }

            grid.push_back(inner);
        }

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] != '@') { continue; }

                int adjacent = 0;

                for (const auto &dir : directions) {
                    int new_i = i + dir[0];
                    int new_j = j + dir[1];

                    if (new_i < 0 || new_j < 0 || new_i >= grid.size() || new_j >= grid[new_i].size()) { continue; }
                    if (grid[new_i][new_j] != '@') { continue; }

                    adjacent++;
                }

                if (adjacent >= 4) { continue; }

                sum++;
            }
        }

        return sum;
    }
};

#endif