#include <bits/stdc++.h>

#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define rep(i, a, b) for(int i = a; i < (b); i++)
using namespace std;

bool ans = 0;
int S;

bool solve (vpi v, int h, int w) {
    // cout << h << " " << w << endl;
    // for (pi p : v) {
    //     cout << p.first << " " << p.second << endl;
    // }
    // cout << endl;
    if (v.size() == 1) {
        if (v[0].first == h && v[0].second == w) return 1;
        return 0;
    }

    // try splitting it with v[0]
    if (v[0].first == h) {
        vpi tmp;
        rep(i, 1, v.size()) tmp.push_back(v[i]);
        if (solve(tmp, h, w-v[0].second)) return 1;
        if (solve(tmp, w-v[0].second, h)) return 1;
    }
    if (v[0].second == h) {
        vpi tmp;
        rep(i, 1, v.size()) tmp.push_back(v[i]);
        if (solve(tmp, h, w-v[0].first)) return 1;
        if (solve(tmp, w-v[0].first, h)) return 1;
    }
    // try splitting with with v[0] and v[1]
    if (v.size() < 4) return 0;
    int area1 = v[0].first * v[0].second + v[1].first * v[1].second;
    int area2 = v[2].first * v[2].second + v[3].first * v[3].second;

    // cerr << "AREAS " << area1 << " " << area2 << endl;
    if (area1%h) return 0;
    vpi tmp1, tmp2;
    rep(i, 0, 2) tmp1.push_back(v[i]);
    rep(i, 2, 4) tmp2.push_back(v[i]);
    if ((solve(tmp1, h, area1/h) || solve(tmp1, area1/h, h))
        && (solve(tmp2, h, area2/h) || solve(tmp2, area2/h, h))) {
            return 1;
        }
    return 0;
}


int main() {
    vector<pair<int, int> > v(4);
    int total = 0;
    rep(i, 0, 4) {
        cin >> v[i].first >> v[i].second;
        total += v[i].first * v[i].second;
    }
    S = sqrt(total);
    while (S*S > total) S--;
    while (S*S < total) S++;
    if (S*S != total) {
        cout << 0 << endl;
        return 0;
    }
    cerr << S << endl;
    vector<int> order(4);
    iota(order.begin(), order.end(), 0);    
    do {
        vpi tmp(4);
        rep(i, 0, 4) {
            tmp[i] = v[order[i]];
        }
        if (solve(tmp, S, S)) ans = 1;
    } while (next_permutation(order.begin(), order.end()));
    cout << ans << endl;
}