#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define f first
#define s second
#define mp make_pair
#define pb push_back
#define MAX_N 100011
#define INF (1<<29) + 123


using namespace std;
int n, s;
pair<int, int> m[MAX_N];
map<int, vector<int>> l;

void solve(int i, int x, int y, int t, int r) {
    int mid = (t + r)/2;
    if (x == mid || y == mid) return;
    if (x < mid && y < mid) { l.at(i).pb(1); solve(i, x, y, t, mid);}
    else if (x < mid && y > mid) { l.at(i).pb(2); solve(i, x, y, t, mid);}
    else if (x > mid && y > mid) l.at(i).pb(3);
    else if (x > mid && y < mid) l.at(i).pb(4);
    
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    rep(i, n) cin >> m[i].f >> m[i].s;
    rep(i, n) {
        vector<int> a;
        l.insert(pair<int, vector<int>>(i, a));
        solve(i, m[i].f, m[i].s, 0, s);
    }
    rep(i, n) {
        rep(j, l.at(i).size()) {
            cout << l.at(i).at(j) << " ";
        }
        cout << endl;
    }
    return 0;
}
