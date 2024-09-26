//
//  main.cpp
//  ConvexHull
//
//  Created by Lucas Xia on 6/18/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1<<30

using namespace std;

bool comparePoint(vector<int> a, vector<int> b) {
    int diffX_a = a[0];
    int diffY_a = a[1];
    int diffX_b = b[0];
    int diffY_b = b[1];
    if (diffX_b * diffY_a < diffX_a * diffY_b) {
        cout << a[0] << "," << a[1] << " has lesser slope than " << b[0] << "," << b[1] << endl;
        return true;}
    else if (diffX_a * diffY_b < diffX_b * diffY_a) {
        cout << a[0] << "," << a[1] << " has greater slope than " << b[0] << "," << b[1] << endl;
        return false;}
    
    if (diffY_a > diffY_b) {
        cout << a[0] << "," << a[1] << " is above " << b[0] << "," << b[1] << endl;
        return true;}
    return false;
}

vector<vector<int> > outerTrees(vector<vector<int> >& points) {
     int minX = points[0][0];
     int minY = points[0][1];
     for (int i = 0; i < points.size(); i++) {
          if (points[i][0] < minX) {
               minX = points[i][0];
               minY = points[i][1];
          }
     }
     for (int i = 0; i < points.size(); i++) {
          points[i][0] -= minX;
          points[i][1] -= minY;
     }
     sort(points.begin(), points.end(), comparePoint);
     for (int i = 0; i < points.size(); i++) {
          points[i][0] += minX;
          points[i][1] += minY;
     }
     vector<vector<int> > points2;
     vector<int>* temp = new vector<int>[points.size()];
     temp[0].push_back(points[0][0]); temp[0].push_back(points[0][1]);
     points2.push_back(temp[0]);
     temp[1].push_back(points[1][0]); temp[1].push_back(points[1][1]);
     points2.push_back(temp[1]);
     int diffX_a, diffY_a, diffX_b, diffY_b;
     vector<int> a, b, c;
     for (int i = 2; i < points.size(); i++) {
          c = points2[points2.size() - 1];
          a = points[i];
          b = points2[points2.size() - 2];
          diffX_a = a[0] - c[0];
          diffY_a = a[1] - c[1];
          diffX_b = b[0] - c[0];
          diffY_b = b[1] - c[1];
          if (diffX_a * diffY_b - diffY_a * diffX_b >= 0) {
               temp[i].push_back(points[i][0]);
               temp[i].push_back(points[i][1]);
               points2.push_back(temp[i]);
               cout << "addresses: " << (temp + i) << " " << &(points2[points2.size() - 1]) << endl;
          } else {
               points2.pop_back();
               i--;
          }
     }
     delete [] temp;
     return points2;
}

int main(int argc, const char * argv[]) {
    int points1[8][2] = {{3,7},{6,8},{7,8},{11,10},{4,3},{8,5},{7,13},{4,13}};
    vector<vector<int> > points, ans;
    for (int i = 0; i < 8; i++) {
        vector<int> p;
        for (int j = 0; j < 2; j++) {
            p.push_back(points1[i][j]);
        }
        points.push_back(p);
    }
    ans = outerTrees(points);
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < 2; j++) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
