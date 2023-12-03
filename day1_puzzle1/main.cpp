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

    int extract_number(string &line){
        int ret = 0;
        for (int i =0; i < line.size(); i++){
            if (isdigit(line[i])){ 
                ret += 10 * (line[i] - '0');
                break;
            }
        }
        for (int i =line.size()-1; i >=0; i--){
            if (isdigit(line[i])){ 
                ret += (line[i]-'0');
                break;
            }
        }
        return ret;
    }

    int sumCalibrationValues(string filename) {
        ifstream infile(filename);
        int sum = 0;
        string line;
        while (getline(infile, line)) {
            int num = extract_number(line);
            sum += num;
        }
        return sum;
    }
};


void print(vector<int> v){
    for(auto &i: v) cout << i << " ";
        cout << "\n";
}

int main(){
    Solution s;

    cout << "Test 1\n";
    cout << s.sumCalibrationValues("input.txt") << endl;

    return 0;
}

