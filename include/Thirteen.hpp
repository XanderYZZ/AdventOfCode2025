#ifndef THIRTEEN_HPP
#define THIRTEEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <queue>

using ll = long long;

class Thirteen {
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
        ll sum = 0;
        std::string line;
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<char>> grid;

        while (std::getline(file, line)) {
            std::vector<char> inner;

            for (const char &c : line) {
                inner.emplace_back(c);
            }

            grid.push_back(inner);
        }

        for (int i = 0; i < grid[0].size(); i++) {
            if (grid[0][i] != 'S') { continue; }

            q.push({1, i});

            break;
        }

        std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            int r = front.first;
            int c = front.second;
            
            if (r + 1 >= grid.size()) { continue; }
            if (c < 0 || c >= grid[r].size() || c >= grid[r + 1].size()) { continue; }
            if (grid[r + 1][c] == '^') {
                sum++;
                grid[r + 1][c] = '.';

                if (!visited[r + 1][c - 1]) {
                    visited[r + 1][c - 1] = true;
                    q.push({r + 1, c - 1});
                }

                if (!visited[r + 1][c + 1]) {
                    visited[r + 1][c + 1] = true;
                    q.push({r + 1, c + 1});
                }
            } else {
                if (!visited[r + 1][c]) {
                    visited[r + 1][c] = true;
                    q.push({r + 1, c});
                }
            }
        }

        return sum;
    }
};

#endif