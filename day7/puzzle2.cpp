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

template <typename T>
void print(vector<T> v) {
    for (auto &i : v) cout << i << " ";
    cout << "\n";
}



class Solution {
public:

    unordered_map<char, char> char_to_char = {
        {'A', 'Z'},
        {'K', 'Y'},
        {'Q', 'X'},
        {'J', '1'},
        {'T', 'U'},
    };

    vector<vector<pair<string, int>>> split_in_categories(vector<pair<string, int>> &hands) {
        vector<vector<pair<string, int>>> ans(7);
        for (auto &hand : hands) {
            unordered_map<char, int> set;
            int jokers = 0;
            for (size_t i=0; i < hand.first.size(); i++) {
                char ch = hand.first[i];
                
                if (ch == 'J') jokers++;
                else if (set.count(ch)) set[ch]++;
                else set[ch] = 1;
                
                if (char_to_char.count(ch)) hand.first[i] = char_to_char[ch];
            }
            if (set.size() <= 1) {
                // five of a kind, with or without jokers
                ans[0].push_back(hand);
            }else if (set.size() == 2 && jokers == 3) {
                // two cards + 3 jokers --> 4 of a kind
                ans[1].push_back(hand);
            } else if (set.size() == 2 && jokers == 2) {
                // 1 pair + 2 jokers --> 4 of a kind
                ans[1].push_back(hand);
            } else if (set.size() == 2 && jokers == 1) {
                // either three of a kind or 2 pairs + the joker will promote one category
                bool three = false;
                for (auto &kv : set) three |= (kv.second == 3);
                if (three) ans[1].push_back(hand);
                else ans[2].push_back(hand);
            } else if (set.size() == 2 && jokers == 0) {
                // either full house or 4 of a kind
                bool four = false;
                for (auto &kv : set) four |= (kv.second == 4);
                if (four) ans[1].push_back(hand);
                else ans[2].push_back(hand);
            } else if (set.size() == 3 && jokers) {
                // one pair + 1 joker --> three of a kind
                // high card + 2 jokers --> three of a kind
                ans[3].push_back(hand);
            } else if (set.size() == 3 && jokers == 0) {
                // either three of a kind or 2 pairs
                bool three = false;
                for (auto &kv : set) three |= (kv.second == 3);
                if (three) ans[3].push_back(hand);
                else ans[4].push_back(hand);
            } else if (set.size() == 4) {
                // high card + joker --> one pair
                // one pair + no joker
                ans[5].push_back(hand);
            }  else if (set.size() == 5) {
                // high card
                ans[6].push_back(hand);
            } else {
                cout << "This is an error: " << hand.first << endl;
            }
        }
        return ans;
    }


    int getTotalWinnings(string filename) {
        ifstream infile(filename);
        string line;
        int ans = 0;

        vector<pair<string, int>> hands;
        // vector<int> bids;
        while (getline(infile, line)) {
            auto space_pos = line.find(' ');
            auto hand = line.substr(0, space_pos);
            auto bid = stoi(line.substr(space_pos + 1));
            hands.push_back({hand, bid});
        }

        // five of a kind
        vector<vector<pair<string, int>>> split_hands = split_in_categories(hands);
        auto comp = [](const pair<string, int>& a, const pair<string, int>& b) {
                            return a.first > b.first;
                        };

        int k = 0;
        for (size_t i = 0; i < split_hands.size(); ++i) {
            // cout << "Category " << split_hands.size()-i << endl;
            // Now I need to sort the hands within each category
            sort(split_hands[i].begin(), split_hands[i].end(), comp);
            for(auto& hand: split_hands[i]) {
                int points = (hands.size()-k) * hand.second;
                ans+=points;
                // cout << hand.first << " points " << points << endl;
                k++;
            }
        }
        return ans;
    }

};




int main() {
    Solution s;


    cout << "Test 1\n";
    cout << s.getTotalWinnings("small_input.txt") << endl;

    cout << "Test 2\n";
    cout << s.getTotalWinnings("input.txt") << endl;
    return 0;
}

