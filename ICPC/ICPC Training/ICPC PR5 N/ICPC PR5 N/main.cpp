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
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

bool check(string s) {
    rep(i, s.length()) if (s[i] != s[s.length() - 1 - i]) return false;
    return true;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int ans = 0;
    rep(i, s.length()) {
        for (int j = 2; i + j < s.length(); j += 2) {
            if (check(s.substr(i, j))) ans = 1;
        }
    }
    if (ans) cout << "Or not." << endl;
    else cout << "Odd." << endl;
    return 0;
}
