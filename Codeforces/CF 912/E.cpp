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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n == -1) {
            return 0;
        }
        pi start; cin >> start.f >> start.s;
        pi p[n]; F0R(i, n) cin >> p[i].f >> p[i].s;
        vi cnt[2];
        bool done[n]; F0R(i, n) done[i] = 0;
        F0R(i, n) {
            cnt[(p[i].f+p[i].s)%2].pb(i);
        }
        int startSide = (start.f+start.s)%2;
        int side = 0;
        int turn = 1;
        if (sz(cnt[startSide]) >= sz(cnt[1-startSide])) {
            cout << "First" << endl;
            cout.flush();
            side = 1-startSide;
            turn = 0;
        } else {
            cout << "Second" << endl;
            cout.flush();
            side = startSide;
        }
        while (n--) {
            if (turn == 0) { // output something on side
                while (sz(cnt[side]) && done[cnt[side].back()]) {
                    cnt[side].pop_back();
                }
                if (sz(cnt[side])) {
                    cout << cnt[side].back()+1 << endl;
                    cout.flush();
                    done[cnt[side].back()] = 1;
                    cnt[side].pop_back();
                } else {
                    while (sz(cnt[1-side]) && done[cnt[1-side].back()]) {
                        cnt[1-side].pop_back();
                    }
                    assert(sz(cnt[1-side]));
                    cout << cnt[1-side].back()+1 << endl;
                    cout.flush();
                    done[cnt[1-side].back()] = 1;
                    cnt[1-side].pop_back();
                }
            } else {
                // see what they did and mark it as done
                int x; cin >> x;
                if (x == -1) {
                    return 0;
                }
                done[x-1] = 1;
            }
            turn = 1-turn;
        }
    }
    return 0;
}
