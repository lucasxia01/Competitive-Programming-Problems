#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define trav(a, x) for(auto& a : x)
#define f first
#define s second
#define pb push_back
const char nl = '\n';

#ifdef DBG
void dbg_out() { cerr << nl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

ll mod = 998244353;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll euclid(ll a, ll b, ll &x, ll &y){
    if(!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}
ll inv(ll a){
    ll x, y, g = euclid(a, mod, x, y);
    assert(g==1); return ((x+mod)%mod);

}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    char a[n][n];
    for(int i = 0; i<n; i++){
        string s;
        cin >> s;
        for(int j = 0; j<n; j++){
            a[i][j] = s[j];
        }
    }
    vector<int> max_r(n);
    vector<int> max_c(n);
    vector<int> min_r(n);
    vector<int> min_c(n);
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            if(a[i][j]=='1'){
                min_r[i] = j+1;
            }
            if(a[j][i]=='1'){
                min_c[i] = j+1;
            }
        }
        max_r[i] = n;
        max_c[i] = n;
        for(int j = n-1; j>=0; j--){
            if(a[i][j]=='0'){
                max_r[i] = j;
            }
            if(a[j][i]=='0'){
                max_c[i] = j;
            }
        }
    }
    int row_le[n][n+1];
    int col_le[n][n+1];
    // [row][x]
    for(int i = 0; i<n; i++){
        for(int j = 0; j<=n; j++){
            int mini = min_r[i];
            int maxi = min(max_r[i],j);
            int can = max(0,maxi-mini+1);
            row_le[i][j] = can;
        }
        for(int j = 0; j<=n; j++){
            int mini = min_c[i];
            int maxi = min(max_c[i],j);
            int can = max(0,maxi-mini+1);
            col_le[i][j] = can;
        }
    }
    ll row_le_pre[n+1][n+1];
    ll col_le_pre[n+1][n+1];
    // [row][x]
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=n; j++){
            if(i==0){
                row_le_pre[i][j] = 1;
                col_le_pre[i][j] = 1;
                continue;
            }
            row_le_pre[i][j] = row_le[i-1][j];
            if(j>0){
                row_le_pre[i][j] *= row_le_pre[i-1][j];
                row_le_pre[i][j] %= mod;
            }

            col_le_pre[i][j] = col_le[i-1][j];
            if(i>0){
                col_le_pre[i][j] *= col_le_pre[i-1][j];
                col_le_pre[i][j] %= mod;
            }
        }
    }
    ll dp[n+1];
    dp[0] = 1LL;
    for(int i = 1; i<=n; i++){
        ll ret = 0LL;
        ll cnt = (ll)min(i,max_r[i-1])*(ll)min(i,max_c[i-1]);
        if(max_r[i-1]>=i && max_c[i-1]>=i){
            cnt -= 2;
            assert(cnt >= 1);
        }
        cnt %= mod;
        ll none = cnt * dp[i-1];
        none %= mod;
        ret += none;
        // ll none = col_le[i-1][i-1]*row_le[i-1][i-1];
        // none %= mod;
        // none *= dp[i-1];
        // none %= mod;
        // ret += none;
        for(int j = 1; j<i; j++){
            ll cur = 1LL;
            // do row j is first full
            if(min_r[j]> i){
                continue;
            }
            if(max_r[j]<i){
                continue;
            }
            ll now = row_le_pre[i-1][i]*inv(row_le_pre[j+1][i]);
            now %= mod;
            now *= row_le[i][j-1];
            now %= mod;
            cur *= now;
            cur %= mod;
            now = col_le_pre[i][j] * inv(col_le_pre[j][j]);
            now %= mod;
            cur *= now;
            cur %= mod;
            cur *= dp[j];
            cur %= mod;
            ret += cur;
            ret %= mod;
        }

        dp[i] = ret;
    }
    cout << dp[n] << endl;

}