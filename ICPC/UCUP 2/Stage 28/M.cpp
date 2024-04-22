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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = sz(s);
        // find the first k < and > to the left of i
        int ptrL[n+1][n+2];
        int ptrR[n+1][n+2];
        rep(i, 0, n+1) rep(j, 0, n+2) ptrL[i][j]=ptrR[i][j]=-1;
        rep(i, 1, n+1) {
            int cntL = 0, cntR = 0;
            ptrL[i][cntL] = ptrR[i][cntR] = i;
            for (int j = i; j >= 1; j--) {
                if (s[j-1] != '>') {
                    ptrL[i][++cntL] = j-1;
                }
                if (s[j-1] != '<') {
                    ptrR[i][++cntR] = j-1;
                }
            }
        }
        int dp[n+1]; dp[0] = 0; // count max number of good robots
        rep(i, 1, n+1) {
            dp[i] = dp[i-1];
            rep(len, 1, i+1) {
                int jj = -1, j = -1;
                if ((jj=ptrL[i][len]) != -1 && (j=ptrR[jj][len])!= -1) {
                    dp[i] = max(dp[i], dp[j]+2*len-1);
                }
                if ((jj=ptrL[i][len+1]) != -1 && (j=ptrR[jj][len])!= -1) {
                    dp[i] = max(dp[i], dp[j]+2*len);
                }
                if ((jj=ptrL[i][len]) != -1 && (j=ptrR[jj][len+1])!= -1) {
                    dp[i] = max(dp[i], dp[j]+2*len);
                }
            }
        }
        cout << dp[n] << nl;
    }
}