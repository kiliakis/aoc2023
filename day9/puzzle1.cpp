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
#include <numeric>

using namespace std;

template <typename T>
void print(vector<T> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}


class Solution {
public:
    vector<int> splitLineInNumbers(string &line){
        vector<int> ret;
        int number;
        
        istringstream iss(line);
        while (iss >> number) {
            ret.push_back(number);
        }

        return ret;

    }

    bool calcDiff(vector<int> &v){
        bool all_zero=true;
        // vector<int> diffs(v.size()-1, 0);
        for(size_t i=0; i < v.size()-1; i++){
            v[i] = v[i+1]-v[i];
            all_zero = all_zero & (v[i]==0);
        }
        if(v.size()) v.pop_back();
        return all_zero;
    }


    int getNextNumInSequence(string filename) {
        ifstream infile(filename);
        string line;

        vector<vector<int>> seqs;
        while (getline(infile, line)) {
            auto seq = splitLineInNumbers(line);
            // print(seq);
            seqs.push_back(seq);
        }
        int ans = 0;

        for (auto &seq: seqs){
            bool all_zeros = false;
            int sum_last_elems = seq.back();
            while(!all_zeros){
                all_zeros = calcDiff(seq);
                sum_last_elems += seq.back();
            }
            // cout << "Last elem: " << sum_last_elems << endl;
            ans += sum_last_elems;
        }

        return ans;
    }

};


int main() {
    Solution s;
    cout << "Test 1\n";
    cout << s.getNextNumInSequence("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.getNextNumInSequence("input.txt") << endl;
    return 0;
}

