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

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    char c;
    string s, ans = "";
    cin >> c >> s;
    if (c == 'E') {
        int i = 1;
        int l = (int) s.length();
        int same = 1;
        while (i < l) {
            if (s[i] == s[i - 1]) same++;
            else {
                ans += s[i - 1];
                ans += to_string(same);
                same = 1;
            }
            i++;
        }
        ans += s[i - 1];
        ans += to_string(same);
    } else {
        int i = 0;
        int l = (int) s.length();
        while (i < l) {
            int x = s[i + 1] - '0';
            rep (j, x) ans += s[i];
            i += 2;
        }
    }
    cout << ans << endl;
    return 0;
}
