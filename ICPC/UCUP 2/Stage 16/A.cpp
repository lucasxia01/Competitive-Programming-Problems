#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b); i >= (a); i--)
#define trav(a, x) for (auto& a : x)
#define rep(i, a, b) for(int i = a; i < (b); ++i)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define ins insert
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

const char nl = '\n';
const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) { return a > b ? a=b, 1 : 0; }
template <typename T> bool ckmax(T& a, const T& b) { return b > a ? a=b, 1 : 0; }

void dbg_out () { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out (Head H, Tail... T) { cerr << H << " "; dbg_out(T...); }

#ifdef DBG
#define dbg(...) dbg_out(__VA_ARGS__);
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	trav(x,c) out<<x<<" ";
	out<<"}"; return out;
}
#else
#define dbg(...)
#endif

mt19937_64 rng(213098);

const int MX = 25;
ll dp1[MX+1] = {}, dp2[MX+1] = {}; // dp1 is matching braces, dp2 is not matching braces

ll solve(string s) { // find number of things less than it !
    int n = sz(s)/3;
    if (n == 0) return 0;
    ll ret = 0;
    // see if s is matching, and find the |
    int cnt = 0, idx = -1;
    bool split = 0;
    int m = sz(s);
    F0R(i, m) {
        if (s[i]=='(') cnt++;
        else if (s[i]==')')cnt--;
        if (s[i] == '|' && cnt == 1) {
            idx = i;
        }
        if (cnt == 0 && i != m-1) {
            split = 1;
            idx = i+1;
            break;
        }
    }
    dbg(s);
    if (!split) {
        assert(idx != -1);
        assert((idx - 1) % 3 == 0);
        // initial splits
        int splitpoint = (idx-1)/3;
        F0R(j, splitpoint) {
            ret += (dp1[j]+dp2[j]) * (dp1[n-1-j]+dp2[n-1-j]);
        }
        ret += solve(s.substr(1, idx-1)) * (dp1[n-1-splitpoint] + dp2[n-1-splitpoint]);
        ret += solve(s.substr(idx+1, m-idx-2));
    } else {
        assert(idx%3 == 0);
        int splitpoint = idx/3;
        FOR(j, 1, splitpoint-1) {
            ret += (dp1[j])*(dp1[n-j]+dp2[n-j]);
        }
        ret += solve(s.substr(0, idx)) * (dp1[n-splitpoint] + dp2[n-splitpoint]);
        ret += solve(s.substr(idx, m-idx));
    }
    return ret;
}

string solve2(int n, ll cnt, bool split) {
    if (!split) { // then we are one chunk
        ll cur = 0;
        F0R(j, n) {
            ll prev = cur;
            cur += (dp1[j]+dp2[j]) * (dp1[n-1-j]+dp2[n-1-j]);
            if (cur >= cnt) {
                cur = prev;
                if (cur + dp1[j]*(dp1[n-1-j]+dp2[n-1-j]) >= cnt) {
                    if (cur + dp1[n-1-j] >= cnt)
                        return "(" + solve2(j, cnt, 1) + "|" + solve2(n-1-j, );
                } else {
                    return 
                }
                return 
            }
                
        }
        assert(0);
    } else {

    }
    assert(0);
    return "";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // generate all the shitters
    dp1[0] = 0;
    dp2[0] = 1;
    dp1[1] = 1;
    dp2[1] = 0;
    FOR(i, 2, MX) {
        dp1[i] = 0;
        dp2[i] = 0;
        F0R(j, i) {
            dp1[i] += dp1[j]*dp1[i-1-j];
            dp1[i] += dp1[j]*dp2[i-1-j];
            dp1[i] += dp2[j]*dp1[i-1-j];
            dp1[i] += dp2[j]*dp2[i-1-j];
        }
        FOR(j, 1, i-1) {
            dp2[i] += dp1[j]*dp1[i-j];
            dp2[i] += dp1[j]*dp2[i-j];
        }
        dbg(dp1[i], dp2[i]);
    }

    string s; cin >> s;
    if (s == "encode") {
        int T; cin >> T;
        while (T--) {
            int n; cin >> n;
            string t; cin >> t;
            ll ans = solve(t);
            cout << ans << nl;
        }
    } else {
        int T; cin >> T;
        while (T--) {
            int n; cin >> n;
        }
    }
    return 0;
}
