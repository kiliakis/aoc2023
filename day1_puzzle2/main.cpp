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
    unordered_map<string, int> word_digits = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    int extract_number(string &line){
        int ret = 0;
        for (int i =0; i < line.size(); i++){
            if (isdigit(line[i])){ 
                ret += 10 * (line[i] - '0');
                break;
            }else if (i+3<= line.size() && word_digits.count(line.substr(i, 3))){
                ret += 10 * (word_digits[line.substr(i, 3)]);
                break;
            }else if (i+4<= line.size() && word_digits.count(line.substr(i, 4))){
                ret += 10 * (word_digits[line.substr(i, 4)]);
                break;
            }else if (i+5<= line.size() && word_digits.count(line.substr(i, 5))){
                ret += 10 * (word_digits[line.substr(i, 5)]);
                break;
            }
        }
        // cout << "First digit: " << ret << "\t";
        for (int i =line.size()-1; i >=0; i--){
            if (isdigit(line[i])){
                ret += (line[i] - '0');
                break;
            }else if (i-2>= 0 && word_digits.count(line.substr(i-2, 3))){
                ret += word_digits[line.substr(i-2, 3)];
                break;
            }else if (i-3>=0 && word_digits.count(line.substr(i-3, 4))){
                ret += word_digits[line.substr(i-3, 4)];
                break;
            }else if (i-4>=0 && word_digits.count(line.substr(i-4, 5))){
                ret += word_digits[line.substr(i-4, 5)];
                break;
            }
        }
        // cout << "Second digit: " << ret << "\n";

        return ret;
    }

    int sumCalibrationValues(string filename) {
        ifstream infile(filename);
        int sum = 0;
        string line;
        while (getline(infile, line)) {
            int num = extract_number(line);
            // cout << "Found number: " << num << endl;
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
    
    cout << "Test 2\n";
    cout << s.sumCalibrationValues("small_input.txt") << endl;
    return 0;
}

