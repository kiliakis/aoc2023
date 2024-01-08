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

    vector<int> splitStringToInt(const string& str) {
        vector<int> result;
        stringstream ss(str);
        string token;

        while (getline(ss, token, ',')) {
            result.push_back(stoi(token));
        }

        return result;
    }

    long num_valid(string seq, int si, vector<int> &nums, int ni){
        // discard front .s
        while(si < seq.size() && seq[si] == '.') si++;

        // check if empty
        if(si==seq.size() && ni==nums.size()) return 1;
        if(si==seq.size() && ni!=nums.size()) return 0;
        if(si!=seq.size() && ni==nums.size()) return 0;

        if (seq[si] == '#'){
            // this means it has to match the nums[ni]
            int num_hash=0;
            for (; si < seq.size() && seq[si]=='#'; ++si) num_hash++;

            if (num_hash != nums[ni]) return 0;
            else return num_valid(seq, si, nums, ni+1);
        }else if(seq[si] == '?'){
            // this means I have to make a choice
            seq[si] = '.';
            auto valid_dot = num_valid(seq, si, nums, ni);
            seq[si] = '#';
            auto valid_hash = num_valid(seq, si, nums, ni);
            return valid_dot + valid_hash;
        }

    }

    long solve(string filename) {
        ifstream infile(filename);
        string line;

        vector<string> seqs_l;
        vector<vector<int>> nums_l;
        while (getline(infile, line)) {
            auto space_pos = line.find(' ');
            auto temp = line.substr(0, space_pos);
            seqs_l.push_back(temp);
            auto nums = splitStringToInt(line.substr(space_pos+1));
            nums_l.push_back(nums);
        }

        long ans = 0;

        for (int i = 0; i < seqs_l.size(); ++i) {
            auto seq = seqs_l[i];
            auto nums = nums_l[i];
            auto temp = num_valid(seq, 0, nums, 0); 
            cout << i << " Number of combs: " << temp << endl;
            ans += temp;

        }

        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.solve("small_input_2.txt") << endl;

    cout << "Test 2\n";
    cout << s.solve("small_input.txt") << endl;

    // cout << "Test 3\n";
    // cout << s.solve("input.txt") << endl;
    return 0;
}

