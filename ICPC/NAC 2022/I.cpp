#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define rep(i, a, b) for(int i = a; i < (b); ++i)
typedef pair<int, int> pii;
#define f first
#define s second

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
    ll n, c; cin >> n >> c;
    pii p[n]; rep(i,0,n) cin >> p[i].f >> p[i].s;
    ll l = 0, r = 1e9*n/min(n, c)+100;
    while (l < r) {
        ll mid = (l + r) / 2, space = 0, left = 0, cnt = 0;
        rep(i, 0, n) {
            ll hard = p[i].f-(mid+1)*p[i].s;
            left += max(0LL, hard);
            if (hard <= 0) space += (p[i].f+p[i].s-1)/p[i].s;
            else cnt++;
        }
        ll val = min(c-cnt, (mid+1)*(c-cnt)-space);
        if (left <= val) r = mid;
        else l = mid+1;
    }
    cout << l << '\n';
}