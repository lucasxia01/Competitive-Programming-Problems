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

const int MX = 1e6+5;

int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int inv(int a, int M) {
    int x, y;
    int g = gcd(a, M, x, y);
    assert(g == 1);
    return (x%M+M)%M;
}

pi ans;
int M;
void mul(int x) {
    while (x%M == 0) {
        x/=M;
        ans.s++;
    }
    ans.f = (ans.f*x)%M;
}
void div(int x) {
    while (x%M == 0) {
        ans.s--;
        x/=M;
    }
    ans.f = (ans.f * inv(x, M))%M;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // run sieve to 1e6
    vector<int> lp(MX);
    vector<int> pr;

    for (int i=2; i < MX; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < MX; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    int x, q; cin >> x >> q >> M;
    // factor x
    while (x%2==0) x/=2;
    map<int, int> m;
    ans = {1, 0};
    trav(p, pr) {
        if (p*p > x) break;
        int cnt = 0;
        while (x%p == 0) {
            x/=p;
            cnt++;
        }
        if (cnt) m[p] = cnt;
        mul(cnt+1);
    }
    if (x > 1) {
        m[x] = 1;
        mul(2);
    }
    F0R(i, q) {
        int y; cin >> y;
        while (y%2==0) y/=2;
        while (y > 1) {
            int f = lp[y];
            m[f]++;
            int val = m[f];
            mul(val+1);
            div(val);
            y /= f;
        }
        cout << (ans.s ? 0 : ans.f) << nl;
    }
    return 0;
}
