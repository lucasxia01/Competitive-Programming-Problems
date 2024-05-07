#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
#define f first
#define s second
typedef pair<int,int> pi;

const int INF = 1LL<<50;

pi calc(pi a, pi b, char op) {
    int hi, lo;
    if (op == '*') {
        hi = max(max(a.f*b.f, a.f*b.s), max(a.s*b.f, a.s*b.s));
        lo = min(min(a.f*b.f, a.f*b.s), min(a.s*b.f, a.s*b.s));
    } else if (op == '+') {
        hi = max(max(a.f+b.f, a.f+b.s), max(a.s+b.f, a.s+b.s));
        lo = min(min(a.f+b.f, a.f+b.s), min(a.s+b.f, a.s+b.s));
    } else if (op == '-') {
        hi = max(max(a.f-b.f, a.f-b.s), max(a.s-b.f, a.s-b.s));
        lo = min(min(a.f-b.f, a.f-b.s), min(a.s-b.f, a.s-b.s));
    }
    return {hi, lo};
}

pi upd(pi a, pi b) {
    if (a.f >= INF) return b;
    return {max(a.f, b.f), min(a.s, b.s)};
}

signed main() {
    int n; cin >> n;
    // cerr << INF << endl;
    vector<int> v;
    for (int i = 0; i < n; i++) {
        int x; cin >> x; v.push_back(x);
        char c; if (i != n-1) {
            cin >> c;
            v.push_back(c);
        }
    }
    pair<int, int> dp[2*n+1][2*n+1]; // max, min
    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < i; j++) dp[i][j] = {0, 0};
        for (int j = i; j < 2*n; j++) dp[i][j] = {INF, INF};
    }
    for (int len = 1; len <= 2*n-1; len++) {
        for (int i = 0; i < 2*n-1; i++) {
            int j = i+len-1;
            if (j >= 2*n-1 || j%2 == 1) continue;
            if (len == 1) {
                dp[i][j] = {v[i], v[i]};
            }
            for (int k = i; k < j; k++) {
                if (k%2 == 1) {
                    dp[i][j] = upd(dp[i][j], calc(dp[i][k-1], dp[k+1][j], v[k]));
                } else {
                    dp[i][j] = upd(dp[i][j], calc(dp[i][k], dp[k+1][j], '*'));
                }
            }
            // cerr << i << " " << j << " " << dp[i][j].f << " " << dp[i][j].s << endl;
        }
    }
    cout << dp[0][2*n-2].f << endl;
    
}