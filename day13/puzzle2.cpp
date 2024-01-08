#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <unordered_set>
#include <climits>
#include <stack>

using namespace std;

template <typename T>
void print(unordered_set<T> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}


class Solution {
public:

    vector<vector<int>> discover_galaxies(vector<string> &m) {
        vector<vector<int>> ret;
        for (int i = 0; i < m.size(); ++i)
            for (int j = 0; j < m[0].size(); ++j)
                if (m[i][j] == '#') ret.push_back({i, j});
        return ret;
    }

    vector<unordered_set<int>> discover_empty_row_cols(vector<string> &m) {
        vector<unordered_set<int>> ret(2);
        for (int i = 0; i < m.size(); ++i)
            if (m[i].find('#') == string::npos) ret[0].insert(i);
        for (int j = 0; j < m[0].size(); ++j) {
            bool has_galaxy = false;
            for (int i = 0; i < m.size() && !has_galaxy; i++)
                has_galaxy = (m[i][j] == '#');
            if (!has_galaxy) ret[1].insert(j);
        }
        return ret;
    }

    long min_dist(int si, int sj, int ei, int ej,
                  unordered_set<int> &erows, unordered_set<int> &ecols,
                  int multiplier) {
        if (ei < si) swap(si, ei);
        if (ej < sj) swap(sj, ej);

        long ret = 0;

        for (int i = si; i < ei; i++) {
            if (erows.count(i)) ret += multiplier;
            else ret += 1;
        }

        for (int j = sj; j < ej; j++) {
            if (ecols.count(j)) ret += multiplier;
            else ret += 1;
        }

        return ret;
    }

    long solve(string filename) {
        ifstream infile(filename);
        string line;

        vector<string> map;
        while (getline(infile, line)) {
            map.push_back(line);
        }
        auto empty_sets = discover_empty_row_cols(map);
        // cout << "Empty rows: \n"; print(empty_sets[0]);
        // cout << "Empty cols: \n"; print(empty_sets[1]);

        // now discover the locations of all galaxies
        vector<vector<int>> glx_locs = discover_galaxies(map);

        long ans = 0;
        for (size_t i = 0; i < glx_locs.size(); ++i) {
            for (size_t j = i + 1; j < glx_locs.size(); ++j) {
                ans += min_dist(glx_locs[i][0], glx_locs[i][1],
                                glx_locs[j][0], glx_locs[j][1],
                                empty_sets[0], empty_sets[1],
                                1000000);
            }
        }
        // cout << "expanded universe: \n";
        // for (int i = 0; i < rows; ++i) {
        //     cout << map[i] << endl;
        // }


        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.solve("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.solve("input.txt") << endl;
    return 0;
}

