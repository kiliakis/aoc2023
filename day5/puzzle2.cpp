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

void print(vector<int> v) {
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

    long getCorrespondence(long dest, vector<vector<long>> map){
        long ans = dest;
        for (auto &row: map){
            if (dest >= row[1] && dest < row[1] + row[2]){
                ans = row[0] + (dest - row[1]);
                break;
            }
        }
        return ans;
    }

    long getMinLocation(string filename) {
        ifstream infile(filename);
        string line;
        vector<vector<long>> seed_soil;
        vector<vector<long>> soil_fertilizer;
        vector<vector<long>> fertilizer_water;
        vector<vector<long>> water_light;
        vector<vector<long>> light_temperature;
        vector<vector<long>> temperature_humidity;
        vector<vector<long>> humidity_location;


        getline(infile, line);
        vector<long> seeds = splitLineInNumbers(line);

        vector<vector<long>> *current_map;

        while (getline(infile, line)) {
            if (line.find("seed-to") != string::npos){
                current_map = &seed_soil;
            }else if (line.find("soil-to") != string::npos){
                current_map = &soil_fertilizer;
            }else if (line.find("fertilizer-to") != string::npos){
                current_map = &fertilizer_water;
            }else if (line.find("water-to") != string::npos){
                current_map = &water_light;
            }else if (line.find("light-to") != string::npos){
                current_map = &light_temperature;
            }else if (line.find("temperature-to") != string::npos){
                current_map = &temperature_humidity;
            }else if (line.find("humidity-to") != string::npos){
                current_map = &humidity_location;
            }else {
                auto range = getNumbers(line);
                if (range.size()) {
                    // print(range);
                    current_map->push_back(range);                    
                }
            }
        }

        long ans = LONG_MAX;
        for (size_t i = 0; i < seeds.size(); i+=2) {
            for (long seed = seeds[i]; seed < seeds[i]+seeds[i+1]; seed++){
                long corr = seed;
                corr = getCorrespondence(corr, seed_soil);
                corr = getCorrespondence(corr, soil_fertilizer);
                corr = getCorrespondence(corr, fertilizer_water);
                corr = getCorrespondence(corr, water_light);
                corr = getCorrespondence(corr, light_temperature);
                corr = getCorrespondence(corr, temperature_humidity);
                corr = getCorrespondence(corr, humidity_location);
                ans = min(ans, corr);
            }
        }

        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.getMinLocation("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.getMinLocation("input.txt") << endl;
    return 0;
}

