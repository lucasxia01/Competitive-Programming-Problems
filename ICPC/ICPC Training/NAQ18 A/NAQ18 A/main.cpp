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
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int a[n][5][5];
    int f[3001] = {};
    
    rep(i, n) rep(j, 5) rep(k, 5) cin >> a[i][j][k];
    rep(i, n) rep(x, 5) rep(y, 5) f[a[i][x][y]]++;
    int ans1 = 101, ans2 = 101;
    rep(i, 3001)
        if (f[i] < 2) continue;
        else {
            vector<pair<int, pair<int, int>>> m;
            rep(j, n) rep(x, 5) rep(y, 5) if (i == a[j][x][y]) m.push_back(mp(j, mp(x, y)));
            int f1[3001] = {};
            rep(k, m.size()) rep(j, k) {
                memset(f1, 0, sizeof(f1));
                rep(y, 5) if (a[m.at(j).f][m.at(j).s.f][y] != a[m.at(j).f][m.at(j).s.f][m.at(j).s.s]) f1[a[m.at(j).f][m.at(j).s.f][y]]++;
                rep(y, 5) if (a[m.at(k).f][m.at(k).s.f][y] != a[m.at(k).f][m.at(k).s.f][m.at(k).s.s]) f1[a[m.at(k).f][m.at(k).s.f][y]]++;
                bool ok = true;
                rep(y, n) if (y != m.at(j).f && y != m.at(k).f) rep(z, 5) {
                    int prod = 1;
                    rep(w, 5) prod *= f1[a[y][z][w]];
                    if (prod != 0) ok = false;
                }
                if (ok) {
                    if (m.at(j).f < ans1) {
                        ans1 = m.at(j).f;
                        ans2 = m.at(k).f;
                    } else if (m.at(j).f == ans1 && m.at(k).f < ans2) ans2 = m.at(k).f;
                }
            }
        }
    if (ans1 == 101 && ans2 == 101) cout << "no ties" << endl;
    else cout << ans1 + 1 << " " << ans2 + 1 << endl;
    return 0;
}
