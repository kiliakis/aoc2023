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

using namespace std;

template <typename T>
void print(vector<T> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}


class Solution {
public:

    int numSteps(string filename) {
        ifstream infile(filename);
        string line;

        unordered_map<string, vector<string>> map;
        getline(infile, line);
        string directions = line;
        // empty line
        getline(infile, line);
        while (getline(infile, line)) {
            auto space_pos = line.find('=');
            auto comma_pos = line.find(',');
            auto source = line.substr(0, space_pos-1); 
            auto left = line.substr(space_pos+3,comma_pos-space_pos-3);
            auto right = line.substr(comma_pos+2, line.size()-comma_pos-3);
            map[source] = {left, right};
        }

        vector<string> locs;
        for (auto &kv: map){
            if (kv.first.back() == 'A'){
                locs.push_back(kv.first);
            }
        }

        // for(auto &kv: map) cout << "Source " << kv.first << " left " << kv.second[0] << " right " << kv.second[1] << endl;

        // string loc = "AAA";
        int ans = 0;
        bool all_end=false;
        while (all_end == false){
            all_end=true;
            for(size_t i=0; i < locs.size(); i++){
                if (directions[ans % directions.size()] == 'L'){
                    locs[i] = map[locs[i]][0];
                }else{
                    locs[i] = map[locs[i]][1];
                }
                all_end &= (locs[i].back() == 'Z'); 
            }
            ans++;
        }

        return ans;
    }

};

int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.numSteps("small_input_3.txt") << endl;

    cout << "Test 3\n";
    cout << s.numSteps("input.txt") << endl;
    return 0;
}

