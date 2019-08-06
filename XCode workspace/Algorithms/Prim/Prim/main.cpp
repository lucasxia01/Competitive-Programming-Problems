//
//  main.cpp
//  Prim
//
//  Created by Lucas Xia on 11/30/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

#define INF 1<<20
int prim() {
    int n;
    cin >> n;
    int mat[n][n];
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) mat[i][j] = INF;
    int e;
    cin >> e;
    int x, y, c;
    for (int i = 0; i < e; i++) {
        cin >> x >> y >> c;
        x--; y--;
        mat[x][y] = c;
        mat[y][x] = c;
    }
    int s = 0; // arbitrary root
    int parent[n];
    int cost[n];
    int visited[n];
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
        cost[i] = INF;
        visited[i] = 0;
    }
    visited[s] = 1;
    cost[s] = 0;
    int id = s;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[id][j] < cost[j]) {
                cost[j] = mat[id][j];
                parent[j] = id;
            }
        }
        int minCost = INF;
        int next = id;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && minCost > cost[j]) {
                minCost = cost[j];
                next = j;
            }
        }
        //cout << minCost << endl;
        visited[next] = 1;
        id = next;
    }
    parent[s] = -1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += cost[i];
    }
    return sum;
}
int main(int argc, const char * argv[]) {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cout << prim() << endl;
    }
    return 0;
}
