#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int ll

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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        int f[n]; F0R(i, n) cin >> f[i];
        int d[n]; F0R(i, n) cin >> d[i];
        int ans = n;
        F0R(i, n) {
            int cur = f[i] * d[i];
            vpi v[2*k+1];
            int pad = k-cur;
            F0R(j, n) {
                int val = f[j]*d[j];
                if (val >= cur-k && val <= cur+k) {
                    v[val+pad].pb({j, 1});
                }
                int tmp = (cur+f[j]-1)/f[j];
                int v1 = (tmp-1)*f[j];
                int v2 = tmp*f[j];
                if (v1 >= cur-k && v1 <= cur+k) 
                    v[v1+pad].pb({j, 0});
                if (v2 >= cur-k && v2 <= cur+k) 
                    v[v2+pad].pb({j, 0});
            }
            int freq[2*n]; F0R(i, 2*n) freq[i] = 0;
            int start = max(0LL, 1LL+pad);
            int cnt = 0;
            int chngs = 0;
            F0R(i, k+1) {
                int idx = start+i;
                trav(u, v[idx]) {
                    int c1 = freq[2*u.f+u.s], c2 =  freq[(2*u.f+u.s)^1];
                    if (c1 == 0 && c2 == 0)
                        cnt++;
                    if (u.s == 0 && c1 == 0 && c2 == 0)
                        chngs++;
                    if (u.s == 1 && c1 == 0 && c2 != 0)
                        chngs--;

                    freq[2*u.f+u.s]++;
                }
            }
            if (cnt == n) ckmin(ans, chngs);
            // window is now [start, start+k]
            while (start+k < 2*k) {
                int idx = start;
                trav(u, v[idx]) {
                    freq[2*u.f+u.s]--;

                    int c1 = freq[2*u.f+u.s], c2 =  freq[(2*u.f+u.s)^1];
                    if (c1 == 0 && c2 == 0)
                        cnt--;
                    if (u.s == 0 && c1 == 0 && c2 == 0)
                        chngs--;
                    if (u.s == 1 && c1 == 0 && c2 != 0)
                        chngs++;

                }

                start++;

                idx = start+k;
                trav(u, v[idx]) {
                    int c1 = freq[2*u.f+u.s], c2 =  freq[(2*u.f+u.s)^1];
                    if (c1 == 0 && c2 == 0)
                        cnt++;
                    if (u.s == 0 && c1 == 0 && c2 == 0)
                        chngs++;
                    if (u.s == 1 && c1 == 0 && c2 != 0)
                        chngs--;

                    freq[2*u.f+u.s]++;
                }
                if (cnt == n) ckmin(ans, chngs);
            }
        }
        cout << ans << nl;
    }
    return 0;
}
