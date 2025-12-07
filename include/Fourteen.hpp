#ifndef FOURTEEN_HPP
#define FOURTEEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <queue>

using ll = unsigned long long;

class Fourteen {
public:
    void Run() {
        std::ifstream input_file("inputs/Thirteen.txt");

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
        std::vector<std::vector<char>> grid;
        std::string line;

        while (std::getline(file, line)) {
            grid.emplace_back(line.begin(), line.end());
        }

        int rows = grid.size();
        int cols = grid[0].size();
        std::vector<std::vector<ll>> dp(rows, std::vector<ll>(cols, 0));
        int start_col = -1;

        for (int c = 0; c < cols; c++) {
            if (grid[0][c] == 'S') {
                start_col = c;

                break;
            }
        }

        dp[0][start_col] = 1;

        for (int r = 0; r < rows - 1; r++) {
            for (int c = 0; c < cols; c++) {
                if (dp[r][c] == 0) continue;

                char below = grid[r + 1][c];

                if (below == '^') {
                    if (c - 1 >= 0) dp[r + 1][c - 1] += dp[r][c];
                    if (c + 1 < cols) dp[r + 1][c + 1] += dp[r][c];
                } else {
                    dp[r + 1][c] += dp[r][c];
                }
            }
        }

        int last_row = rows - 1;
        if (last_row % 2 == 1) {
            last_row--;
        }

        ll total = 0;
        for (int c = 0; c < cols; c++) {
            total += dp[rows - 1][c];
        }

        return total;
    }
};

#endif