//
//  main.cpp
//  LeetCode 218
//
//  Created by Lucas Xia on 2/21/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    // create vector of pairs
    // mark each pair with index
    int n = buildings.size();
    vector<pair<pair<int, int>, int>> points;
    for (int i = 0; i < n; i++) {
        points.push_back(make_pair(make_pair(buildings.at(i).at(0), buildings.at(i).at(2)), i));
        points.push_back(make_pair(make_pair(buildings.at(i).at(1), buildings.at(i).at(2)), i));
    }
    // sort the vector by x positions
    sort(points.begin(), points.end());
    // make frequency array of the indices
    int freq[10000] = {};
    set<pair<int, int>> maxY;
    // iterate through the vector
    // keep track of the max y value with the index in a sorted vector
    // at each position add to the max y value vector or find a new max
    int curMax = 0, prevMax = 0, prevUpd = -1, id, f, curX = 0;
    vector<pair<int, int>> ans;
    for (int i = 0; i < 2 * n; i++) {
        curX = points.at(i).first.first;
        while (i < 2 * n && curX == points.at(i).first.first) {
            id = points.at(i).second;
            f = freq[id];
            if (f == 0) { // new building
                maxY.insert(make_pair(points.at(i).first.second, id));
            } else if (f == 1) { // building goes away
                maxY.erase(make_pair(points.at(i).first.second, id));
            }
            freq[id]++;
            i++;
        }
        i--;
        if (maxY.size() == 0) curMax = 0;
        else if (curMax != (maxY.rbegin())->first) curMax = (maxY.rbegin())->first;
        else continue;
        ans.push_back(make_pair(points.at(i).first.first, curMax));
    }
    return ans;
}

int main() {
    int n, x;
    cin >> n;
    vector<vector<int>> buildings;
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> x;
            temp.push_back(x);
        }
        buildings.push_back(temp);
        temp.clear();
    }
    vector<pair<int, int>> ans = getSkyline(buildings);
    for (int i = 0; i < ans.size(); i++) {
        cout << "[" << ans.at(i).first << ", " << ans.at(i).second << "], ";
    }
    return 0;
}
