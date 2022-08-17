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
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, ans;
    cin >> n;
    int s[MAX_N] = {};
    vector<int> p;
    for (int i = 2; i < MAX_N; i++) {
        if (s[i] == 0) {
            p.push_back(i);
            for (int j = 2; i * j < MAX_N; j++) {
                s[i * j] = 1;
            }
        }
    }
    //rep(i, p.size()) cout << p.at(i) << " " << endl;
    while (n != 0) {
        n -= 3;
        if (n == 0) n = 4;
        ans = n;
        if (n <= 3) {
            cout << "No such base" << endl;
            cin >> n;
            continue;
        }
        for (int i = 2; i < p.size() && p.at(i) * p.at(i) <= n; i++) {
            if (n % p.at(i) == 0) {
                ans = p.at(i);
                break;
            }
        }
        if (n % 4 == 0) ans = 4;
        if (n % 9 == 0) if (9 < ans) ans = 9;
        if (n % 2 == 0) {
            if (n/2 < ans && n/2 > 3) ans = n/2;
        }
        if (n % 3 == 0)
            if (n/3 < ans && n/3 > 3) ans = n/3;
        if (n % 6 == 0) if (6 < ans) ans = 6;
        cout << ans << endl;
        cin >> n;
    }
    return 0;
}
