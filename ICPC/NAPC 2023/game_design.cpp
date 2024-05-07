#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    string s; cin >> s;
    string t = s;
    string ss = "";
    if (s.size() > 2) {
        int x = s.size()-1;
        bool bad = 0;
        if (s[x-2] == 'L' && s[x-1] == 'R' && s[x] == 'L') bad = 1;
        else if (s[x-2] == 'R' && s[x-1] == 'L' && s[x] == 'R') bad = 1;
        else if (s[x-2] == 'U' && s[x-1] == 'D' && s[x] == 'U') bad = 1;
        else if (s[x-2] == 'D' && s[x-1] == 'U' && s[x] == 'D') bad = 1;
        if (bad) {
            cout << "impossible" << endl;
            return 0;
        }
    }
    ss = "";
    for (int i = 0; i < s.size(); i++) {
        int j = ss.size()-1;
        if (ss.size() < 2) ss += s[i];
        else if (s[i] == 'L' && ss[j] == 'R' && ss[j-1] == 'L') {
            ss.pop_back();
        } else if (s[i] == 'R' && ss[j] == 'L' && ss[j-1] == 'R') {
            ss.pop_back();
        } else if (s[i] == 'U' && ss[j] == 'D' && ss[j-1] == 'U') {
            ss.pop_back();
        } else if (s[i] == 'D' && ss[j] == 'U' && ss[j-1] == 'D') {
            ss.pop_back();
        } else ss += s[i];
    }
    s = ss;
    cerr << s << endl;
    int n = s.size();
    // now just randomly pick lengths of the dir
    vector<pair<int, int> > v;
    int x = 0, y = 0;
    int len = 0;
    for (int i = 0; i < n; i++) {
        len += rng() % ((int)1e5) + 10;
        if (s[i] == 'D') {
            y -= len;
            v.push_back({x, y-1});
        } else if (s[i] == 'U') {
            y += len;
            v.push_back({x, y+1});
        } else if (s[i] == 'L') {
            x -= len;
            v.push_back({x-1, y});
        } else if (s[i] == 'R') {
            x += len;
            v.push_back({x+1, y});
        }
    }
    cout << -x << " " << -y << endl;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << v[i].first-x << " " << v[i].second-y << endl;
    }
}