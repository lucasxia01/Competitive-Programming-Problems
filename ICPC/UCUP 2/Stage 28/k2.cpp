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
    int last1_row[n][n+1];
    int last1_col[n][n+1];
    for(int i = 0; i<n; i++){
        last1_row[i][0] = 0;
        last1_col[i][0] = 0;
        for(int j = 1; j<=n; j++){
            if(a[i][j-1]=='1'){
                last1_row[i][j] = j;
            }
            else{
                last1_row[i][j] = last1_row[i][j-1];
            }
        }
        for(int j = 1; j<=n; j++){
            if(a[j-1][i]=='1'){
                last1_col[i][j] = j;
            }
            else{
                last1_col[i][j] = last1_col[i][j-1];
            }
        }
    }
    // int row_le[n][n+1];
    // int col_le[n][n+1];
    // [row][x]
    // for(int i = 0; i<n; i++){
    //     row_le[i][0] = 1LL;
    //     col_le[i][0] = 1LL;
    //     bool colZero = false;
    //     bool rowZero = false;
    //     for(int j = 1; j<=n; j++){
    //         if(a[i][j-1]=='0'){
    //             rowZero = true;
    //             row_le[i][j] = row_le[i][j-1];
    //         }
    //         else if(a[i][j-1] == '1'){
    //             if(rowZero){
    //                 row_le[i][j] = 0;
    //             }
    //             else{
    //                 row_le[i][j] = 1;
    //             }
    //         }
    //         else{
    //             if(rowZero){
    //                 row_le[i][j] = row_le[i][j-1];
    //             }
    //             else{
    //                 row_le[i][j] = row_le[i][j-1]+1;
    //             }
    //         }
    //     }
    //     for(int j = 1; j<=n; j++){
    //         if(a[j-1][i]=='0'){
    //             rowZero = true;
    //             col_le[i][j] = col_le[i][j-1];
    //         }
    //         else if(a[j-1][i] == '1'){
    //             if(rowZero){
    //                 col_le[i][j] = 0;
    //             }
    //             else{
    //                 col_le[i][j] = 1;
    //             }
    //         }
    //         else{
    //             if(rowZero){
    //                 col_le[i][j] = col_le[i][j-1];
    //             }
    //             else{
    //                 col_le[i][j] = col_le[i][j-1]+1;
    //             }
    //         }
    //     }
        
    // }
    ll dp[n+1][n+1];
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=n; j++){
            if(i==0 || j==0){
                dp[i][j] = 1LL;
                continue;
            }
            ll rowWays = max(0, min(max_r[i-1],j)-last1_row[i-1][j]+1);
            ll colWays = max(0,min(max_c[j-1],i)-last1_col[j-1][i]+1);
            ll ret = dp[i-1][j] * rowWays;
            ret %= mod;
            ret += dp[i][j-1] * colWays;
            ret %= mod;
            ll cnt = rowWays*colWays;
            if(max_r[i-1]>=j){
                cnt -= colWays;
            }
            if(max_c[j-1]>=i){
                cnt -= rowWays;
            }
            if(max_r[i-1]>=j && max_c[j-1]>=i){
                cnt += 2;
            }
            cnt %= mod;
            ll over = cnt * dp[i-1][j-1];
            over %= mod;
            ret -= over;
            ret %= mod;
            ret += mod;
            ret %= mod;
            dp[i][j] = ret;
        }
        
    }
    cout << dp[n][n] << endl;

}


// OK 4
// hmm 1 1 2 2
// OK 7
// hmm 1 2 3 4
// OK 7
// hmm 2 1 3 4
// OK 18
// hmm 2 2 4 7
// 4