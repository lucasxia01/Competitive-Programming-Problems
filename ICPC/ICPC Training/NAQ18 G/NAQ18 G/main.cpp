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
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

int ans[MAX_N][2];

void solve() {
    int pos = 1;
    int i = 0;
    if (ans[i][0] == 0) {
        rep(j, ans[i][1] + 1) {
            cout << ans[i][1] - j + pos << endl;
        }
        pos += ans[i][1] + 1;
    } else {
        rep(j, ans[i][1]) {
            cout << pos + j << endl;
        }
        if (ans[i + 1][1]) cout << ans[i][1] + pos + ans[i + 1][1] << endl;
        else cout << pos + ans[i][1] << endl;
        pos = ans[i][1] + pos - 1 + ans[i + 1][1];
    }
    //cout << "hi " << i << pos << ans[0][0] << endl;
    i++;
    while (ans[i][1]) {
        if (ans[i][0]) {
            rep(j, ans[i][1] - 1) {
                cout << pos + j << endl;
            }
            if (ans[i + 1][1]) cout << ans[i][1] + pos - 1 + ans[i + 1][1] << endl;
            else cout << pos + ans[i][1] - 1 << endl;
            pos = ans[i][1] + pos - 2 + ans[i + 1][1];
        } else {
            rep(j, ans[i][1]) {
                cout << pos - j << endl;
            }
            pos += 2;
        }
        //cout << "hi " << i << pos << endl;
        i++;
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s;
    
    cin >> n >> s;
    int i = 1;
    int j = 0;
    int l = (int) s.length();
    int same = 1;
    while (i < l) {
        if (s[i] == s[i - 1]) same++;
        else {
            s[i - 1] == 'L' ? ans[j][0] = 0 : ans[j][0] = 1;
            ans[j][1] = same;
            same = 1;
            j++;
        }
        i++;
    }
    s[i - 1] == 'L' ? ans[j][0] = 0 : ans[j][0] = 1;
    ans[j][1] = same;
//    rep (k, 20) {
//        cout << ans[k][0] << ans[k][1] << endl;
//    }
    solve();
    return 0;
}
