#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define vi vector<int>
#define vpi vector<pi>
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (x).size()
using namespace std;

template <class T>
struct RMQ {
    vector<vector<T>> jmp;
    RMQ(const vector<T>& V) : jmp(1, V) {
        for (int pw = 1, k = 1; pw*2 <=sz(V); pw*=2, ++k) {
            jmp.emplace_back(sz(V) - pw*2+1);
            rep(j, 0, sz(jmp[k])) 
                jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
        }
    }
    T query(int a, int b) {
        assert(a < b);
        int dep = 31 - __builtin_clz(b-a);
        return min(jmp[dep][a], jmp[dep][b - (1<<dep)]);
    }
};

struct LCA {
    int T = 0;
    vi time, path, ret;
    RMQ<int> rmq;
    LCA(vector<vi>& C): time(sz(C)), rmq((dfs(C, 0, -1), ret)) {}

    void dfs(vector<vi>& C, int v, int par) {
        time[v] = T++;
        for (int y : C[v]) if (y!= par) {
            path.push_back(v), ret.push_back(time[v]);
            dfs(C, y, v);
        }
    }
    int lca(int a, int b) {
        if (a == b) return a;
        tie(a, b) = minmax(time[a], time[b]);
        return path[rmq.query(a, b)];
    }
};

const int MX = 5e4 + 5;
int par[MX], SZ[MX];
int find(int p) {
    return (p == par[p]?p:par[p] = find(par[p]));
}
bool merge(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    if (SZ[a] < SZ[b]) swap(a, b);
    SZ[a] += SZ[b];
    par[b] = a;
    return 1;
}

bool onpath (LCA& lca, int c, int a, int b) {
    return (lca.lca(c, a) == c && lca.lca(c, b) == b);
}
bool check(LCA& lca, vi path) {
    // process into pairs
    assert(sz(path)%2 == 0);
    vpi paths;
    rep(i, 0, sz(path)/2) {
        int c = lca.lca(path[2*i], path[2*i+1]);
        paths.push_back({path[2*i], c}); // low to hi
        paths.push_back({path[2*i+1], c});
    }
    // now see if anything intersects
    rep(i, 0, sz(paths)) {
        rep(j, 0, sz(paths)) {
            if (i/2 == j/2) continue;
            int c = lca.lca(paths[i].first, paths[j].first);
            if (onpath(lca, c, paths[i].first, paths[i].second) 
                && onpath(lca, c, paths[j].first, paths[j].second)) {
                    return false;
                }
            
        }
    }
    return true;
}
vector<vi> gr(MX);
vpi extra;
signed main() {
    int n, q; cin >> n >> q;
    rep(i, 0, MX) {
        par[i] = i;
        SZ[i] = 1;
    }
    rep(i, 0, n+1) {
        int a, b; cin >> a >> b; a--; b--;
        if (merge(a, b)) {
            gr[a].push_back(b);
            gr[b].push_back(a);
        } else {
            extra.push_back({a, b});
        }
    }
    LCA lca(gr);
    // brute force over all 5*4
    while (q--) {
        // try all subsets
        int u, v; cin >> u >> v; u--; v--;
        set<vi> ans;
        rep(iii, 0, 2) {
            rep(jjj, 0, 2) {
                rep(kkk, 0, 2) {
                    rep(mask, 0, 4) {
                        vi tmp = {u};
                        rep(i, 0, 2) {
                            if (mask&(1<<i)) {
                                tmp.push_back(extra[i].first);
                                tmp.push_back(extra[i].second);
                            }
                        }
                        tmp.push_back(v);
                        if (check(lca, tmp)) {
                            // for (int x : tmp) {
                            //     cerr << x << " ";
                            // } cerr << endl;
                            ans.insert(tmp);
                        }
                    }
                    swap(extra[0], extra[1]);
                }
                swap(extra[1].first, extra[1].second);
            }
            swap(extra[0].first, extra[0].second);
        }
        cout << sz(ans) << '\n';
    }
}