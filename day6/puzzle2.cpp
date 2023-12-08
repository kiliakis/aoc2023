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

    vector<long> getNumbers(string &line){
        vector<long> ans;
        long number;
        
        istringstream iss(line);
        while (iss >> number){
            ans.push_back(number);
        }

        return ans;
    }

    vector<long> splitLineInNumbers(string &line){
        auto semi_pos = line.find(':');
        auto seeds_str = line.substr(semi_pos+2);
        return getNumbers(seeds_str);
    }

    long left_bound(long time, long dist){
        long i = 1;
        while (i < time && i * (time-i) <= dist) i++;
        return i;
    }

    long right_bound(long time, long dist){
        long i = time-1;
        while (i>0 && i * (time-i) <= dist) i--;
        return i;
    }

    long merge_numbers(vector<long>& nums){
        string result;
        for (long num: nums)
            result += to_string(num);
        return stol(result);
    }


    long getWinCombs(string filename) {
        ifstream infile(filename);
        string line;
        long ans=1;

        getline(infile, line);
        vector<long> times = splitLineInNumbers(line);
        
        getline(infile, line);
        vector<long> dists = splitLineInNumbers(line);

        long time = merge_numbers(times);
        long dist = merge_numbers(dists);

        cout << "Time: " << time << endl;
        cout << "Dist: " << dist << endl;

        long left = left_bound(time, dist);
        long right = right_bound(time, dist);
        ans *= (right-left+1);

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

