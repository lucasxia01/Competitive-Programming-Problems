#include <bits/stdc++.h>
#define f first
#define s second
#define pi pair<int, int>
using namespace std;
int main() {
    int n, m, k; cin >> n >> m >> k;
    int cur = 0;
    stack<pi> s;
    int t[n+m];
    long long ans = 0;
    for(int i=0; i<n+m;i++) {
        t[i] = 0;
        int f = 0;
        if (i < n) cin >> f;
        s.push({f, i});
        while (cur < k && s.size() && s.top().s > i-m) {
            pi p = s.top(); s.pop();
            int v = min(k-cur, p.f);
            if (v < p.f) s.push({p.f-v, p.s});
            cur += v;
            t[p.s] += v;
            ans += v;
        }
        if (i-m > -2) cur -= t[i-m+1];
    }
    cout << ans << '\n';
}