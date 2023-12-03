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

using namespace std;


class Solution {
public:

    bool hasAsjacentSymbol(vector<string> &s, int i, int j){
        // left
        if (j-1 >= 0 && !isdigit(s[i][j-1]) && !(s[i][j-1] == '.')) return true;
        // right
        if (j+1 < s[i].size() && !isdigit(s[i][j+1]) && !(s[i][j+1] == '.')) return true;
        // up
        if (i-1 >= 0 && !isdigit(s[i-1][j]) && !(s[i-1][j] == '.')) return true;
        // down
        if (i+1 < s.size() && !isdigit(s[i+1][j]) && !(s[i+1][j] == '.')) return true;

        // up left
        if (j-1 >= 0 && i-1 >=0 && !isdigit(s[i-1][j-1]) && !(s[i-1][j-1] == '.')) return true;
        // up right
        if (j+1 < s[i].size() && i-1 >=0 && !isdigit(s[i-1][j+1]) && !(s[i-1][j+1] == '.')) return true;
        // down left
        if (j-1 >=0 && i+1 < s.size() && !isdigit(s[i+1][j-1]) && !(s[i+1][j-1] == '.')) return true;
        // down right
        if (j+1 < s[i].size() && i+1 < s.size() && !isdigit(s[i+1][j+1]) && !(s[i+1][j+1] == '.')) return true;


        return false;
    }

    int sumPartNumbers(string filename) {
        ifstream infile(filename);
        string line;
        vector<string> schem;
        while (getline(infile, line)) {
            schem.push_back(line);
        }
        int sum = 0;
        for(int i=0; i < schem.size(); i++){
            int j = 0;
            while(j < schem[i].size()){
                int end = j;
                bool has_symbol = false;
                int num = 0;
                while(end < schem[i].size() && isdigit(schem[i][end])){
                    num = 10*num + (schem[i][end] - '0');
                    has_symbol |= hasAsjacentSymbol(schem, i, end);
                    end++;
                }
                if (end > j && has_symbol) {
                    // cout << "found part " << num << endl;
                    sum += num;
                }
                j = end+1;
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
    cout << s.sumPartNumbers("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.sumPartNumbers("input.txt") << endl;
    return 0;
}

