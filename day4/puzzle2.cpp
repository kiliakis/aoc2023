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
#include <numeric>

using namespace std;


class Solution {
public:


    vector<vector<int>> splitLineInNumbers(string &line){
        auto semi_pos = line.find(':');
        auto sep_pos = line.find('|');
        auto winning_str = line.substr(semi_pos+2, sep_pos-semi_pos-1);
        auto played_str = line.substr(sep_pos+2);
        
        vector<int> winning_nums, played_nums;
        int number;
        
        istringstream iss(winning_str);
        while (iss >> number){
            winning_nums.push_back(number);
        }

        iss = istringstream(played_str);
        while (iss >> number){
            played_nums.push_back(number);
        }

        return {winning_nums, played_nums};

    }

    int sumScratchcards(string filename) {
        ifstream infile(filename);
        string line;
        vector<vector<int>> winning;
        vector<vector<int>> played;
        while (getline(infile, line)) {
            vector<vector<int>> res = splitLineInNumbers(line);
            winning.push_back(res[0]);
            played.push_back(res[1]);
        }

        vector<int> copies(winning.size(), 1);

        for (size_t i=0; i < winning.size(); i++){
            unordered_set<int> win_set(winning[i].begin(), winning[i].end());
            int common = 1;
            for(auto &p: played[i]) {
                if (win_set.count(p)) {
                    if (i+common < copies.size()) {
                        copies[i+common] += copies[i];
                        common++;
                    }
                }
            }
            // if (common) sum += (1<<(common-1));
        }

        return accumulate(copies.begin(), copies.end(), 0);
    }

};


void print(vector<int> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}

int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.sumScratchcards("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.sumScratchcards("input.txt") << endl;
    return 0;
}

