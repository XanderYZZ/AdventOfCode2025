#ifndef FIFTEEN_HPP
#define FIFTEEN_HPP

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <tuple>

using ull = unsigned long long;

class Fifteen {
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
        struct Point { long long x,y,z; };
        std::vector<Point> pts;
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string tok;
            long long x,y,z;

            if (!std::getline(ss, tok, ',')) continue;

            x = std::stoll(tok);

            if (!std::getline(ss, tok, ',')) continue;

            y = std::stoll(tok);

            if (!std::getline(ss, tok, ',')) continue;

            z = std::stoll(tok);
            pts.push_back({x,y,z});
        }

        const size_t n = pts.size();
        if (n == 0) return 0;

        struct Edge { ull dist; int a, b; };
        std::vector<Edge> edges;
        edges.reserve((n*(n-1))/2);

        for (size_t i=0; i<n; ++i) {
            for (size_t j=i+1; j<n; ++j) {
                long long dx = pts[i].x - pts[j].x;
                long long dy = pts[i].y - pts[j].y;
                long long dz = pts[i].z - pts[j].z;
                ull d = (ull)(dx*dx) + (ull)(dy*dy) + (ull)(dz*dz);
                edges.push_back({d, (int)i, (int)j});
            }
        }

        std::sort(edges.begin(), edges.end(), [](const Edge& A, const Edge& B){
            if (A.dist != B.dist) return A.dist < B.dist;
            if (A.a != B.a) return A.a < B.a;
            return A.b < B.b;
        });

        const size_t to_connect = std::min<size_t>(1000, edges.size());

        UF uf((int)n);
        for (size_t k=0;k<to_connect;++k) {
            uf.unite(edges[k].a, edges[k].b);
        }

        std::vector<ull> comp_count(n, 0);
        for (int i=0;i<(int)n;++i) {
            int r = uf.find(i);
            comp_count[r] += 1;
        }

        std::vector<ull> sizes;
        sizes.reserve(n);
        for (ull c : comp_count) if (c>0) sizes.push_back(c);
        std::sort(sizes.begin(), sizes.end(), std::greater<ull>());

        ull product = 1;
        for (size_t i=0;i<3 && i<sizes.size(); ++i) product *= sizes[i];

        return product;
    }
};

#endif