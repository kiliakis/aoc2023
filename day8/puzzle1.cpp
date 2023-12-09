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

        // for(auto &kv: map) cout << "Source " << kv.first << " left " << kv.second[0] << " right " << kv.second[1] << endl;

        string loc = "AAA";
        int ans = 0;

        while (loc!="ZZZ") {
            if (directions[ans % directions.size()] == 'L'){
                loc = map[loc][0];
            }else{
                loc = map[loc][1];
            }
            ans++;
        }

        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.numSteps("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.numSteps("small_input_2.txt") << endl;

    cout << "Test 3\n";
    cout << s.numSteps("input.txt") << endl;
    return 0;
}

