#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MX = 2e5+5;
int p[MX], s[MX];

int find(int i) {
    return (i==p[i]?i:p[i]=find(p[i]));
}

void merge(int a, int b) {
    // cerr << a << " " << b << endl;
    a = find(a), b = find(b);
    if (a == b) return;
    if (s[a] < s[b]) swap(a, b);
    p[b] = a;
    s[a] += s[b];
}

int main() {
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        p[i] = i;
        s[i] = 1;
    }
    set<pi> edges;
    set<pi> dead;
    for (int i = 0; i< m; i++) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        edges.insert({u, v});
    }
    vector<pair<int, pi > > V;
    for (int i = 0; i < q; i++) {
        int t, u, v; cin >> t >> u >> v;
        if (u > v) swap(u, v);
        V.push_back({t, {u, v}});
        if (t == 0) dead.insert({u, v});
    }
    for(auto e: edges) {
        if (!dead.count(e)) {
            merge(e.first, e.second);
        }
    }
    reverse(V.begin(), V.end());
    vector<string> ans;
    for(auto a: V) {
        if (a.first == 0) {
            merge(a.second.first, a.second.second);
        } else {
            // cerr << "wtf " << a.second.first << " " << a.second.second << endl;
            ans.push_back((find(a.second.first) == find(a.second.second))?"safe":"unsafe");
        }
    }
    reverse(ans.begin(), ans.end());
    for (auto a: ans) {
        cout << a << endl;
    }
}