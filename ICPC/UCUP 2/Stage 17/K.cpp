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
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int hi(multiset<int>& s) {
    return *s.rbegin();
}
int lo(multiset<int>& s) {
    return *s.begin();
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        ll a[n]; F0R(i, n) cin >> a[i];
        F0R(i, n) a[i]-=i;
        // make everything constant at median
        multiset<int> lower, upper; // make upper the bigger one
        int r = 0;
        ll curans = 0;
        ll best = 0;
        ll uppersum = 0, lowersum = 0;
        F0R(l, n) {
            // move r until you can't
            while (r < n && curans <= k) {
                // throw in a[r] to the big side, move to lower if necessary
                lower.insert(a[r]);
                lowersum += a[r];
                // move something to upper
                int tmp = hi(lower);
                lower.erase(lower.find(tmp));
                lowersum -= tmp;
                uppersum += tmp;
                upper.insert(tmp);
                // rebalance down
                if (sz(lower) > sz(upper)) { // move something from lower to upper
                    int val = hi(lower);
                    lower.erase(lower.find(val));
                    lowersum -= val;
                    uppersum += val;
                    upper.insert(val);
                }
                if (sz(lower) < sz(upper)-1) {// move something from upper to lower
                    int val = lo(upper);
                    upper.erase(upper.find(val));
                    uppersum -= val;
                    lowersum += val;
                    lower.insert(val);
                }
                ll median = lo(upper);
                ll ans = uppersum - median*sz(upper) + median*sz(lower) - lowersum;
                dbg(l, r, uppersum, lowersum, median, ans);
                if (ans > k) {
                    // remove a[r]
                    if (lower.find(a[r]) != lower.end()) {
                        lowersum -= a[r];
                        lower.erase(lower.find(a[r]));
                    } else {
                        uppersum -= a[r];
                        upper.erase(upper.find(a[r]));
                    }
                    // rebalance
                    if (sz(lower) > sz(upper)) { // move something from lower to upper
                        int val = hi(lower);
                        lower.erase(lower.find(val));
                        lowersum -= val;
                        uppersum += val;
                        upper.insert(val);
                    }
                    if (sz(lower) < sz(upper)-1) {// move something from upper to lower
                        int val = lo(upper);
                        upper.erase(upper.find(val));
                        uppersum -= val;
                        lowersum += val;
                        lower.insert(val);
                    }
                    break;
                }
                curans = ans;
                r++;
            }
            // now increase l
            if (lower.find(a[l]) != lower.end()) {
                lowersum -= a[l];
                lower.erase(lower.find(a[l]));
            } else {
                uppersum -= a[l];
                upper.erase(upper.find(a[l]));
            }
            // rebalance
            if (sz(lower) > sz(upper)) { // move something from lower to upper
                int val = hi(lower);
                lower.erase(lower.find(val));
                lowersum -= val;
                uppersum += val;
                upper.insert(val);
            }
            if (sz(lower) < sz(upper)-1) {// move something from upper to lower
                int val = lo(upper);
                upper.erase(upper.find(val));
                uppersum -= val;
                lowersum += val;
                lower.insert(val);
            }
            ckmax(best, r-l);
            dbg(l, r);
            assert(sz(upper) == sz(lower) || sz(upper) == sz(lower)+1);

        }
        cout << best << nl;
    }
    return 0;
}
