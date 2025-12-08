#ifndef SIXTEEN_HPP
#define SIXTEEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <tuple>

using ull = unsigned long long;

class Sixteen {
public:
    void Run() {
        std::ifstream input_file("inputs/Fifteen.txt");

        if (input_file.is_open()) {
            ull result = ProcessFile(input_file);
            std::cout << "Resulting product: " << result << "\n";
        } else {
            std::cout << "Failed to open file.\n";
        }
    }

private:
    struct UF {
        std::vector<int> parent;
        std::vector<int> size;

        UF(int n): parent(n), size(n,1) {
            for (int i=0;i<n;++i) parent[i]=i;
        }

        int find(int x) {
            if (parent[x]==x) return x;
            return parent[x]=find(parent[x]);
        }

        bool unite(int a, int b) {
            a=find(a); 
            b=find(b);

            if (a==b) return false;
            if (size[a]<size[b]) std::swap(a,b);

            parent[b]=a;
            size[a]+=size[b];

            return true;
        }
    };

    [[nodiscard]]
    ull ProcessFile(std::ifstream& file) {
        struct Point { ull x, y, z; };

        std::vector<Point> pts;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            char comma;
            Point p;
            ss >> p.x >> comma >> p.y >> comma >> p.z;
            pts.push_back(p);
        }

        const int n = (int)pts.size();

        struct UF {
            std::vector<int> parent, size;
            int components;

            UF(int n) : parent(n), size(n,1), components(n) {
                for (int i = 0; i < n; ++i) parent[i] = i;
            }

            int find(int x) {
                if (parent[x] != x)
                    parent[x] = find(parent[x]);
                return parent[x];
            }

            bool unite(int a, int b) {
                a = find(a);
                b = find(b);
                if (a == b) return false;
                if (size[a] < size[b]) std::swap(a, b);
                parent[b] = a;
                size[a] += size[b];
                components--;
                return true;
            }
        };

        struct Edge {
            ull dist;
            int a, b;
        };

        std::vector<Edge> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ull dx = pts[i].x - pts[j].x;
                ull dy = pts[i].y - pts[j].y;
                ull dz = pts[i].z - pts[j].z;
                ull d = dx*dx + dy*dy + dz*dz;
                edges.push_back({d, i, j});
            }
        }

        std::sort(edges.begin(), edges.end(),
            [](const Edge& A, const Edge& B) {
                return A.dist < B.dist;
            });

        UF uf(n);

        for (const auto& e : edges) {
            if (uf.unite(e.a, e.b)) {
                if (uf.components == 1) {
                    return pts[e.a].x * pts[e.b].x;
                }
            }
        }

        return 0; 
    }
};

#endif