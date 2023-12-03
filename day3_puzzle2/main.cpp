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

using namespace std;


class Solution {
public:


    vector<int> getNumber(vector<string> &s, int i, int j){
        int start = j;
        while (start >=0 && isdigit(s[i][start])) start--;
        int end = j;
        while(end < s[i].size() && isdigit(s[i][end])) end++;

        return {i * s[0].size() + start+1, i * s[0].size() + end};
    }

    int getGearRatio(vector<string> &s, int i, int j) {
        // Gear can be adjacent to a number in one of eight directions

        unordered_map<int, int> adj_numbers;
        int ans = 1;
        // left
        if (j - 1 >= 0 && isdigit(s[i][j - 1])) {
            vector<int> se = getNumber(s, i, j - 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i].substr(se[0]%s[0].size(), se[1]-se[0]));
            }
        }
        // right
        if (j + 1 < s[i].size() && isdigit(s[i][j + 1])) {
            vector<int> se = getNumber(s, i, j + 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        // up
        if (i - 1 >= 0 && isdigit(s[i - 1][j])) {
            vector<int> se = getNumber(s, i - 1, j);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i-1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        // down
        if (i + 1 < s.size() && isdigit(s[i + 1][j])) {
            vector<int> se = getNumber(s, i + 1, j);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i+1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }

        // up left
        if (j - 1 >= 0 && i - 1 >= 0 && isdigit(s[i - 1][j - 1])) {
            vector<int> se = getNumber(s, i - 1, j - 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i-1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        // up right
        if (j + 1 < s[i].size() && i - 1 >= 0 && isdigit(s[i - 1][j + 1])) {
            vector<int> se = getNumber(s, i - 1, j + 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i-1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        // down left
        if (j - 1 >= 0 && i + 1 < s.size() && isdigit(s[i + 1][j - 1])) {
            vector<int> se = getNumber(s, i + 1, j - 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i+1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        // down right
        if (j + 1 < s[i].size() && i + 1 < s.size() && isdigit(s[i + 1][j + 1])) {
            vector<int> se = getNumber(s, i + 1, j + 1);
            if (adj_numbers.count(se[0]) == 0){
                adj_numbers[se[0]] = se[1];
                ans *= stoi(s[i+1].substr(se[0]%s[0].size(), se[1]-se[0]));        
            }
        }
        if (adj_numbers.size() != 2) return 0;
        cout << "Loc: " << i << "," << j <<  " prod = " << ans << endl;
        return ans;

    }

    int sumGearRatios(string filename) {
        ifstream infile(filename);
        string line;
        vector<string> schem;
        while (getline(infile, line)) {
            schem.push_back(line);
        }

        int sum = 0;

        for (int i = 0; i < schem.size(); i++) {
            for(int j=0; j < schem[i].size(); j++){
                if (schem[i][j] == '*') sum+= getGearRatio(schem, i, j);
            }
        }

        return sum;
    }

};


void print(vector<int> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}

int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.sumGearRatios("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.sumGearRatios("input.txt") << endl;
    return 0;
}

