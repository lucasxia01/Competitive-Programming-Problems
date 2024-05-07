#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = a; i < b; i++)
#define pi pair<int, int>
#define nl '\n'
#define vi vector<int>
#define vpi vector<pi>
#define pb push_back
#define sz(x) x.size()
#define all(x) x.begin(),x.end()
using namespace std;

bool find(int j, vector<vi>& g, vi& btoa, vi& vis) {
    if (btoa[j] == -1) return 1;
    vis[j] = 1; int di = btoa[j];
    for (int e : g[di])
        if (!vis[e] && find(e, g, btoa, vis)) {
            btoa[e] = di;
            return 1;
        }
    return 0;
}

int dfsMatching(vector<vi>& g, vi& btoa) {
    vi vis;
    rep(i, 0, sz(g)) {
        vis.assign(sz(btoa), 0);
        for (int j : g[i])
            if (find(j, g, btoa, vis)) {
                btoa[j] = i;
                break;
            }
    }
    return sz(btoa) - (int) count(all(btoa), -1);
}

int n, m;
string grid[1000];
int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};

int main() {
    cin >> n >> m;
    rep(i, 0, n) cin >> grid[i];
    // if more than 1000, quit
    int cnt = 0;
    rep(i, 0, n) rep(j, 0, m) {
        if (grid[i][j] == '.') cnt++;
    }
    if (cnt > 2000) {
        cout << 1000000 << nl;
        return 0;
    }
    // now find the matching
    assert(cnt%2 == 0);
    cnt = cnt/2;
    vector<vi> g(cnt);
    int c = 0;
    int label[n][m];
    rep(i, 0, n) rep(j, 0, m) {
        if (grid[i][j] == '#') continue;
        if ((i+j)%2) {
            label[i][j] = c++;
        }
    }

    c = 0;
    rep(i, 0, n) rep(j, 0, m) {
        if (grid[i][j] == '#' || (i+j)%2) continue;
        rep(d, 0, 4) {
            int nx = i+dx[d], ny = j+dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || grid[nx][ny] == '#') continue;
            g[c].pb(label[nx][ny]);
        }
        c++;
    }
    assert(c == cnt);
    vi btoa(cnt, -1);
    assert(dfsMatching(g, btoa) == c);

    // rep(i, 0, cnt) {
    //     cerr << btoa[i] << nl;
    // }
    int ans = 0;
    rep(i, 0, cnt) {
        // try removing this dude
        // bfs from it and go sicko mode
        queue<int> lq, rq;
        bool lvis[cnt]; memset(lvis, 0, sizeof lvis);
        bool rvis[cnt]; memset(rvis, 0, sizeof rvis);

        lq.push(i);
        // try reaching everything on right
        while (!lq.empty()) {
            while (!lq.empty()) {
                int left = lq.front(); lq.pop();
                if (lvis[left]) continue;
                lvis[left] = 1;
                for (auto r : g[left]) {
                    rq.push(r);
                }
            }

            while (!rq.empty()) {
                int right = rq.front(); rq.pop();
                if (rvis[right]) continue;
                rvis[right] = 1;
                lq.push(btoa[right]);
            }
        }
        rep(i, 0, cnt) ans += (rvis[i]==0);
    }
    // cout << ans << nl;
    ans += (cnt)*(cnt-1);
    cout << min(1000000, ans) << nl;
}