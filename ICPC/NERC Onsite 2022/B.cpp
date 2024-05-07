#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = a; i < b; i++)
#define pi pair<int, int>
#define nl '\n'
#define vi vector<int>
#define vpi vector<pi>
#define pb push_back
using namespace std;

const int MX = 1000;
int a[105][MX];
int ans[MX];
int n, k;
pi curRange[105];

void solve(int par) {
    if (curRange[0].second - curRange[0].first == 1) {
        ans[a[0][curRange[0].first]] = par;
        return;
    }

    // find the ceo
    set<int> cnt[MX];
    rep(i, 0, k) {
        rep(j, curRange[i].first, curRange[i].second) {
            cnt[a[i][j]].insert(j-curRange[i].first);
        }
    }
    int ceo = -1;
    int maybe = -1;
    // now look for things that are low cnt
    rep(j, curRange[0].first, curRange[0].second) {
        int SZ = cnt[a[0][j]].size();
        if (SZ > 2) continue;
        else if (SZ == 1) {
            ceo = a[0][j];
        } else {
            maybe = a[0][j];
        }
    }
    if (ceo == -1) ceo = maybe;
    cerr << par << nl;
    cerr << curRange[0].first << " " << curRange[0].second << nl;
    assert(ceo != -1);
    // now recurse
    ans[ceo] = par;
    pi tmp[105]; int pos[105];
    rep(i, 0, k) {
        tmp[i] = curRange[i];
        rep(j, curRange[i].first, curRange[i].second) {
            if (a[i][j] == ceo) {
                // break
                pos[i] = j;
                break;
            }
        }
    }
    // now assign left and right correctly
    int val = a[0][curRange[0].first];
    bool left[k];
    rep(i, 0, k) {
        left[i] = 0;
        rep(j, curRange[i].first, pos[i]) {
            if (a[i][j] == val) left[i] = 1;
        }
        if (left[i]) curRange[i].second = pos[i];
        else curRange[i].first = pos[i]+1;
    }
    solve(ceo);
    rep(i, 0, k) {
        if (left[i]) {
            curRange[i].first = pos[i]+1;
            curRange[i].second = tmp[i].second;
        } else {
            curRange[i].first = tmp[i].first;
            curRange[i].second = pos[i];
        }
    }
    solve(ceo);
}

int main() {
    cin >> n >> k;
    int x;
    rep(i, 0, k) rep(j, 0, n) {
        cin >> x; x--;
        a[i][j] = x;
    }
    rep(i, 0, k) curRange[i] = {0, n};
    solve(-2);

    rep(i, 0, n) cout << ans[i]+1 << " "; cout << nl;
}