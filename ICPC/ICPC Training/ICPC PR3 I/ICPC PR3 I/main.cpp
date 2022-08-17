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

int result[1001];

bool gt(string a, string b) {
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) return false;
    rep(i, a.length()) {
        if (a[i] > b[i]) return true;
        if (a[i] < b[i]) return false;
    }
    return true;
}
bool comp(pair<string, string> s, pair<string, string> t) {
    string a = s.f;
    string b = t.f;
    if (a.length() > b.length()) return true;
    if (a.length() < b.length()) return false;
    rep(i, a.length()) {
        if (a[i] > b[i]) return true;
        if (a[i] < b[i]) return false;
    }
    return true;
}

string subs(string a, string b) {
    if (a.length() != b.length()) {
        rep(i, a.length() - b.length()) {
            b = "0" + b;
        }
    }
    rep(i, a.length()) {
        result[i] = a[i] - b[i];
    }
    string ans = a;
    for (int i = (int) a.length() - 1; i >= 0; i--) {
        if (result[i] < 0) {
            result[i] += 10;
            result[i - 1]--;
        }
        ans[i] = ((char) (result[i]) + '0');
    }
    int i = 0;
    while (ans[i] == '0') i++;
    int l = (int) ans.length();
    ans = ans.substr(i, l - i);
    if (ans.length() == 0) ans = "0";
    return ans;
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    string s, a, b;
    cin >> n >> s;
    pair<string, string> bets[n];
    int count = 0;
    rep(i, n) {
        cin >> a >> b;
        bets[i] = mp(b, a);
        //cout << bets[i].f << " " << bets[i].s << endl;
    }
    int mark[1011] = {};
    //cout << subs("123451", "109999") << endl;
    sort(bets, bets + n, comp);
    for (int i = 0; i < n; i++) {
        //cout << bets[i].f << " " << bets[i].s << endl;
        if (gt(s, bets[i].f)) {
            s = subs(s, bets[i].f);
            mark[i] = 1;
            count++;
            //cout << s << endl;
        }
    }
    //cout << s << endl;
    if (s != "0") count = 0;
    cout << count << endl;
    rep(i, n) if (mark[i] && count > 0) cout << bets[i].s << endl;
    return 0;
}
