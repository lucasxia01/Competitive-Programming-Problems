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
template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){}
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int n;
vi ans;
int calc(array<int, 3> a) {
    int s = a[0]+a[1]+a[2];
    int ret = (s*(s-2*a[0])*(s-2*a[1])*(s-2*a[2]));
    return (ret > 0 ? ret : 0);
}

void output() {
    cout << "! ";
    trav(aa, ans) cout << aa << " ";
    cout << endl;
    cout.flush();
}

int query(array<int, 3> a) {
    sort(all(a));
    cout << "? " << a[0]+1 << " " << a[1]+1 << " " << a[2]+1 << endl;
    cout.flush();
    int x; cin >> x;
    return x;
}

void solve(int i, int j) {
    F0R(k, n) {
        if (k == i || k == j || ans[k] != -1) continue;
        int x = query({i, j, k});
        FOR(y, 1, 4) {
            if (calc({ans[i], ans[j], y}) == x) {
                ans[k] = y;
            }
        }
    }
    output();
}

void solve2(int i, int j) {
    // find 4 non 1s
    vi v;
    F0R(k, n) {
        if (k == i || k == j) continue;
        int x = query({i, j, k});
        if (x == 0) {
            v.pb(k);
            if (sz(v) == 4) break;
        } else {
            ans[k] = 1;
        }
    }
    // find a pair
    F0R(k, sz(v)) {
        F0R(kk, k) {
            int k1 = v[k], k2 = v[kk];
            int x = query({i, k1, k2});
            if (x != 0) {
                if (x == 15) ans[k1] = ans[k2] = 2;
                else if (x == 35) ans[k1] = ans[k2] = 3;
                else ans[k1] = ans[k2] = 4;
                solve(k1, k2);
                return;
            }
        }
    }
    if (sz(v) > 0) {
        cout << "! -1" << endl;
        cout.flush();
    } else output();
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    // FOR(i, 1, 4) FOR(j, 1, 4) FOR(k, 1, 4) {
    //     if (i <= j && j <= k) {
    //         int s = i+j+k;
    //         dbg(i, j, k, calc({i, j, k}));
    //     }
    // }
    cin >> n;
    ans.resize(n, -1);
    if (n < 9) {
        // just try all combinations
        map<array<int, 3>, int> m;
        F0R(k, n) {
            F0R(j, k) {
                F0R(i, j) {
                    m[{i, j, k}] = query({i, j, k});
                }
            }
        }
        int cnt = 0;
        F0R(i, (1<<(2*n))) {
            int x = i;
            vi v;
            F0R(j, n) {
                v.pb(x%4 + 1);
                x /= 4;
            }
            bool ok = 1;
            trav(p, m) {
                if (calc({v[p.f[0]], v[p.f[1]], v[p.f[2]]}) != p.s) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                cnt++;
                ans = v;
            }
        }
        if (cnt == 1) {
            output();
        } else {
            cout << "! -1" << endl;
            cout.flush();
        }
    } else {
        // randomly find a triple
        map<array<int, 3>, int> m;
        while (1) {
            array<int, 3> a;
            F0R(i, 3) a[i] = rng()%n;
            sort(all(a));
            if (a[0] == a[1] || a[1] == a[2]) continue;
            if (m.find(a) != m.end()) continue;
            int x = query(a);
            m[a] = x;
            if (x == 48 || x == 243 || x == 768) {
                if (x == 48) ans[a[0]] = ans[a[1]] = 2;
                else if (x == 243) ans[a[0]] = ans[a[1]] = 3;
                else ans[a[0]] = ans[a[1]] = 4;
                solve(a[0], a[1]);
                break;
            } else if (x == 3) {
                ans[a[0]] = ans[a[1]] = 1;
                solve2(a[0], a[1]);
                break;
            }
        }
    }
    return 0;
}
