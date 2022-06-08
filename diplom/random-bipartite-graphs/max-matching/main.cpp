#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;
const int N = 20000;

vector<int> g[N];
vector<int> mt;
vector<char> used;

bool try_kuhn (int v) {
    if (used[v])  return false;
    used[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn (mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int get_size_max_matching(int n, int k) {
    mt.assign (k, -1);
    for (int v=0; v<n; ++v) {
        used.assign (n, false);
        try_kuhn (v);
    }
    int count = 0;
    for (int i=0; i<k; ++i) {
        if (mt[i] != -1) {
            //printf("%d %d\n", mt[i], i);
            count += 1;
        }
    }
    return count;
}

void fill_graph(int n, int d) {
    for (int i = 0; i < n; i++) {
        g[i].clear();
    }
    mt.clear();

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 2 * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x = distrib(gen);
            if (x <= d) {
                g[i].push_back(j);
            }
        }
    }
}

int main() {
    int n = 10000;
    int d = 1;
    int q = 1000;
    ofstream f;
    f.open("n=10000,d=05.txt");

    for (int i = 0; i < q; i++) {
        fill_graph(n, d);
        f << get_size_max_matching(n, n) << endl;
    }
    f.close();

}
