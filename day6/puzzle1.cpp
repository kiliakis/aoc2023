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

    vector<int> getNumbers(string &line){
        vector<int> ans;
        int number;
        
        istringstream iss(line);
        while (iss >> number){
            ans.push_back(number);
        }

        return ans;
    }

    vector<int> splitLineInNumbers(string &line){
        auto semi_pos = line.find(':');
        auto seeds_str = line.substr(semi_pos+2);
        return getNumbers(seeds_str);
    }

    int left_bound(int time, int dist){
        int i = 1;
        while (i < time && i * (time-i) <= dist) i++;
        return i;
    }

    int right_bound(int time, int dist){
        int i = time-1;
        while (i>0 && i * (time-i) <= dist) i--;
        return i;
    }


    int getWinCombs(string filename) {
        ifstream infile(filename);
        string line;
        int ans=1;

        getline(infile, line);
        vector<int> times = splitLineInNumbers(line);
        
        getline(infile, line);
        vector<int> dists = splitLineInNumbers(line);

        print(times);
        print(dists);

        for (int i = 0; i < times.size(); ++i) {
            int left = left_bound(times[i], dists[i]);
            int right = right_bound(times[i], dists[i]);
            ans *= (right-left+1);
        }

        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.getWinCombs("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.getWinCombs("input.txt") << endl;
    return 0;
}

