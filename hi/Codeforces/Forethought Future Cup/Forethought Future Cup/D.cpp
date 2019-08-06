#include <iostream>
using namespace std;

#define ll long long
ll a, b;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    if (a < b) return gcd(b, a);
    return gcd(b, a % b);
}

ll fill(int* dp, ll size, ll pos, int f) {
    ll jump, njump;
    ll an = 0;
    if (f) jump = a; else jump = -b;
    if (f) njump = -b; else njump = a;
    for (ll i = pos; i >= 0 && i < size && dp[i] != 1; i += jump) {
        dp[i] = 1; an++;
        an += fill(dp, size, i + njump, 1 - f);
    }
    return an;
}
int main() {
    ll m;
    cin >> m >> a >> b;
    ll ans = 0;
    int dp[a + b + 11];
    for (int i = 1; i < a + b + 11; i++) dp[i] = 0;
    dp[0] = 1;
    ll cur = 1;
    ans += min(m + 1, a);
    //cout << ans << endl;
    for (ll i = a; i < min(m + 1, a + b); i++) {
        if (dp[i - a] == 1) {
            dp[i] = 1; cur++;
            cur += fill(dp, i, i - b, 0);
        }
        ans += cur;
//        cout << i << " " << cur << endl;
//        for (int j = 0; j <  a + b; j++) {
//            cout << dp[j] << " ";
//        }
//        cout << endl;
    }
    //cout << ans << endl;
    if (m >= a + b) {
        ll GCD = gcd(a, b);
        ll low = (a + b) / GCD + 1;
        ll high = m / GCD + 1;
        ll nterms = high - low + 1;
        ans += nterms * GCD * (high + low) / 2;
        ll extra = (GCD - (m%GCD) - 1) * high;
        //cout << low << " " << high << " " << nterms << " " << extra << endl;
        ans -= extra;
    }
    cout << ans << endl;
    return 0;
}
