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
void print(vector<T> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}


class Solution {
public:

    void expand_universe(vector<string> &m){
        // first the rows
        size_t i = 0;
        while(i< m.size()){
            if(m[i].find('#')==string::npos){
                // no galaxy
                m.insert(m.begin() + i, m[i]);
                i++;
            }
            i++;
        }
        // then the columns
        size_t j = 0;
        while(j<m[0].size()){
            bool has_galaxy=false;
            for(i=0; i < m.size() && has_galaxy==false; i++){
                has_galaxy = (m[i][j]=='#');
            }
            if(!has_galaxy){
                for(i=0; i < m.size(); i++) {
                    m[i].insert(m[i].begin()+j, '.');
                }
                j++;
            }
            j++;
        }
    }

    vector<vector<int>> discover_galaxies(vector<string> &m){
        vector<vector<int>> ret;
        for (int i = 0; i < m.size(); ++i)
            for (int j = 0; j < m[0].size(); ++j)
                if(m[i][j] == '#') ret.push_back({i,j});
        return ret;
    }

    int solve(string filename) {
        ifstream infile(filename);
        string line;

        vector<string> map;
        while (getline(infile, line)) {
            map.push_back(line);
        }

        expand_universe(map);

        // now discover the locations of all galaxies
        vector<vector<int>> glx_locs = discover_galaxies(map);

        long ans = 0;
        for (size_t i = 0; i < glx_locs.size(); ++i) {
            for (size_t j = i+1; j < glx_locs.size(); ++j) {
                ans += abs(glx_locs[j][0] - glx_locs[i][0]) + abs(glx_locs[j][1] - glx_locs[i][1]);
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

