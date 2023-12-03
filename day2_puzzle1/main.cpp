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

    // red, green, blue
    vector<int> cube_limits = {12, 13, 14};

    vector<int> get_cube_numbers(string &trial){
        vector<int> ans = {0,0,0};
        string target;
        size_t target_pos;

        target = "red";
        target_pos = trial.find(target);
        if (target_pos != string::npos){
            size_t j = target_pos-2;
            int mult = 1;
            while(isdigit(trial[j])) {
                ans[0] += mult * (trial[j] - '0');
                mult *=10;
                j--;
            }
        }
        // cout << "Red " << ans[0] << '\t'; 

        target = "green";
        target_pos = trial.find(target);
        if (target_pos != string::npos){
            size_t j = target_pos-2;
            int mult = 1;
            while(isdigit(trial[j])) {
                ans[1] += mult * (trial[j] - '0');
                mult *=10;
                j--;
            }
        }

        // cout << "Green " << ans[1] << '\t'; 

        target = "blue";
        target_pos = trial.find(target);
        if (target_pos != string::npos){
            size_t j = target_pos-2;
            int mult = 1;
            while(isdigit(trial[j])) {
                ans[2] += mult * (trial[j] - '0');
                mult *=10;
                j--;
            }
        }
        // cout << "Blue " << ans[2] << '\n'; 

        return ans;
    }

    bool isValidGame(string &game) {
        // first need to divide it in tries
        auto trial_end = game.find(';');
        size_t pos = 0;
        while (trial_end != string::npos) {
            auto trial = game.substr(pos, trial_end - pos);
            auto cube_numbers = get_cube_numbers(trial);
            if (cube_numbers[0] > cube_limits[0]
                    || cube_numbers[1] > cube_limits[1]
                    || cube_numbers[2] > cube_limits[2]) return false;
            pos = trial_end+1;
            trial_end = game.find(';', pos);
        }
        auto trial = game.substr(pos);
        auto cube_numbers = get_cube_numbers(trial);
        if (cube_numbers[0] > cube_limits[0]
                    || cube_numbers[1] > cube_limits[1]
                    || cube_numbers[2] > cube_limits[2]) return false;
        return true;
    }

    int possibleGameSumIDs(string filename) {
        ifstream infile(filename);
        int sum = 0;
        string line;
        while (getline(infile, line)) {
            // Id starts from char 6
            int i = 5;
            while (isdigit(line[i])) i++;
            int id = stoi(line.substr(5, i - 5));
            // cout << "Found id: " << id << endl;

            auto game = line.substr(i + 2);
            if (isValidGame(game)) sum += id;
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
    cout << s.possibleGameSumIDs("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.possibleGameSumIDs("input.txt") << endl;
    return 0;
}

