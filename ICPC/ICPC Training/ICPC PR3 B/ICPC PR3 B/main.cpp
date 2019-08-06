#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <cstdlib>
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
int ai (string s) {
    int l = (int) s.length();
    int power = 1;
    int ans = 0;
    rep(i, l) {
        ans += power * (s[l - i - 1] - '0');
        power *= 10;
    }
    return ans;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, j;
    string k;
    cin >> n;
    int count = 0;
    rep(i, n) {
        cin >> k;
        if (k != "mumble") {
            j = ai(k);
            //cout << j << endl;
            if (i + 1 != j) count = 1;
        }
    }
    
    if (count == 0) cout << "makes sense" << endl;
    else cout << "something is fishy" << endl;
    return 0;
}
