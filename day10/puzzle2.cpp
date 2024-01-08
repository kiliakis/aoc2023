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

    bool isin(vector<string> &m, int i, int j, string dir){
        int rows = m.size();
        int cols = m[0].size();
        if (i>=rows || i<0 || j>=cols || j<0) return false;
        if (dir == "up"){
            return m[i][j] == '|' || m[i][j] == 'F' || m[i][j] == '7' || m[i][j] == 'S';
        }else if (dir == "down"){
            return m[i][j] == '|' || m[i][j] == 'L' || m[i][j] == 'J' || m[i][j] == 'S';
        }else if (dir == "right"){
            return m[i][j] == '-' || m[i][j] == 'J' || m[i][j] == '7' || m[i][j] == 'S';
        }else if (dir == "left"){
            return m[i][j] == '-' || m[i][j] == 'F' || m[i][j] == 'L' || m[i][j] == 'S';
        }
        return false;
    }

    int stepsToAnimal(string filename) {
        ifstream infile(filename);
        string line;

        vector<string> map;
        int si=-1;
        int sj=-1;
        while (getline(infile, line)) {
            map.push_back(line);
            for (size_t j = 0; j < line.size() && (si==-1); j++) {
                if (line[j] == 'S') {
                    si = map.size()-1;
                    sj = j;
                }
            }
        }
        int rows = map.size();
        int cols = map[0].size();
        // cout << "Starting pos " << si << ", " << sj << endl;

        /*
        I will start a dfs from the starting pos, following the pipes
        I will keep track of the locs that have been discovered, and the steps
        it took to discover them. When I find the starting pos again, I will now the 
        length of the loop. The max distance is ceil(loop_length/2)
        */

        stack<vector<int>> s;
        s.push({si, sj, 0});

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        while (s.size()){
            auto top = s.top(); s.pop();
            int i = top[0];
            int j = top[1];
            int steps = top[2];

            if (i >=rows || i<0 || j>=cols || j<0) continue;
            if (visited[i][j]) continue;
            
            visited[i][j] = true;
            // cout << "Just visited: " << i << ", " << j << endl;

            if (map[i][j] == 'S') {
                if (steps>3) return static_cast<int>((steps+1)/2);
                else visited[i][j] = false;
            }
            if (map[i][j] == '.'){
                continue;
            }
            if (map[i][j] == '-' || map[i][j] == 'S') { // left right
                if (isin(map, i, j-1, "left")) s.push({i, j-1, steps+1});
                if (isin(map, i, j+1, "right")) s.push({i, j+1, steps+1});
            }
            if (map[i][j] == '|' || map[i][j] == 'S') { // up down
                if (isin(map, i-1, j, "up")) s.push({i-1, j, steps+1});
                if (isin(map, i+1, j, "down")) s.push({i+1, j, steps+1});
            }
            if (map[i][j] == '7' || map[i][j] == 'S') { // left down
                if (isin(map, i, j-1, "left")) s.push({i, j-1, steps+1});
                if (isin(map, i+1, j, "down")) s.push({i+1, j, steps+1});
            }
            if (map[i][j] == 'J' || map[i][j] == 'S') { // up left
                if (isin(map, i-1, j, "up")) s.push({i-1, j, steps+1});
                if (isin(map, i, j-1, "left")) s.push({i, j-1, steps+1});
            }
            if (map[i][j] == 'L' || map[i][j] == 'S') { // up right
                if (isin(map, i-1, j, "up")) s.push({i-1, j, steps+1});
                if (isin(map, i, j+1, "right")) s.push({i, j+1, steps+1});                
            }
            if (map[i][j] == 'F' || map[i][j] == 'S') { // down right
                if (isin(map, i+1, j, "down")) s.push({i+1, j, steps+1});
                if (isin(map, i, j+1, "right")) s.push({i, j+1, steps+1});
            }

        }


        return -1;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.stepsToAnimal("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.stepsToAnimal("small_input_2.txt") << endl;

    cout << "Test 3\n";
    cout << s.stepsToAnimal("input.txt") << endl;
    return 0;
}

