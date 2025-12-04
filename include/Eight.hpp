#ifndef EIGHT_HPP
#define EIGHT_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

class Eight {
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
        
        while (std::getline(file, line)) {
            grid.emplace_back(line.begin(), line.end());
        }

        const int rows = grid.size();
        
        while (true) {
            std::vector<std::pair<int, int>> to_remove;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < grid[i].size(); j++) {
                    if (grid[i][j] != '@') { continue; }
                    if (!CanTake(grid, i, j)) { continue; }

                    to_remove.emplace_back(i, j);
                }
            }

            if (to_remove.empty()) { break; }

            for (auto &p : to_remove) {
                grid[p.first][p.second] = '.';
            }

            sum += to_remove.size();
        }

        return sum;
    }

    bool CanTake(std::vector<std::vector<char>> &grid, int i, int j) {
        int adjacent = 0;

        for (const auto &dir : directions) {
            int new_i = i + dir[0];
            int new_j = j + dir[1];

            if (new_i < 0 || new_j < 0 || new_i >= grid.size() || new_j >= grid[new_i].size()) { continue; }
            if (grid[new_i][new_j] != '@') { continue; }

            adjacent++;
        }

        return adjacent < 4;
    }

    std::vector<std::vector<int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
    };
};

#endif