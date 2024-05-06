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
        string s; cin >> s;
        int n = sz(s);
        ll pos; cin >> pos;
        pos--;
        bool deleted[n]; F0R(i, n) deleted[i] = 0;
        int nxt[n]; F0R(i, n) nxt[i] = i+1;
        nxt[n-1] = -1;
        int prev[n]; F0R(i, n) prev[i] = i-1;
        prev[0] = -1;
        // delete a char until pos is within the string
        set<int> del_set;
        F0R(i, n-1) {
            if (s[i] > s[i+1]) {
                del_set.insert(i);
            }
        }
        del_set.insert(n-1); // last one can always be deleted
        F0R(i, n) {
            if (pos < n-i) {
                // find which char it is
                int cnt = 0;
                F0R(j, n) {
                    if (deleted[j]) continue;
                    if (cnt == pos) {
                        cout << s[j];
                        break;
                    }
                    cnt++;
                }
                break;
            }
            // find which char to delete
            auto it = del_set.begin();
            int idx = *it;
            dbg(i, idx, prev[idx], nxt[idx]);
            if (prev[idx] != -1) {
                if (nxt[idx] == -1 || s[prev[idx]] > s[nxt[idx]]) {
                    del_set.insert(prev[idx]);
                }
            }
            // delete *it in linked list
            if (nxt[idx] != -1) prev[nxt[idx]] = prev[idx];
            if (prev[idx] != -1) nxt[prev[idx]] = nxt[idx];
            deleted[idx] = 1;
            del_set.erase(it);
            pos -= (n-i);
        }
    }
    cout << nl;
    return 0;
}
