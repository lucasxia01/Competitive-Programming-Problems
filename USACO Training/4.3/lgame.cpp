/*
ID: lucasxi1
TASK: lgame
LANG: C++                 
*/
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

int main() {
    freopen("lgame.dict", "r", stdin);
    set<string> dict;
    string in; cin >> in;
    while (in != ".") {
        dict.insert(in);
        cin >> in;
    }
    dict.insert("");
    freopen("lgame.in", "r", stdin);
    freopen("lgame.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    map<char, int> m = {{'q', 7}, {'w', 6}, {'e', 1}, {'r', 2}, {'t', 2}, {'y', 5}, {'u', 4}, {'i', 1}, {'o', 3}, {'p', 5}, {'a', 2}, {'s', 1}, {'d', 4}, {'f', 6}, {'g', 5}, {'h', 5}, {'j', 7}, {'k', 6}, {'l', 3}, {'z', 7}, {'x', 7}, {'c', 4}, {'v', 6}, {'b', 5}, {'n', 2}, {'m', 5}};
    string s; cin >> s;
    int n = sz(s);
    // try all bitmasks of s and permutations with a space
    int hi = 0;
    set<string> ans;
    F0R(mask, 1<<n) {
        vector<char> v;
        int cur = 0;
        F0R(i, n) if (mask&(1<<i)) {
            v.pb(s[i]);
            cur += m[s[i]];
        }
        if (cur < hi) continue;
        v.pb(' ');
        sort(all(v));
        do {
            // break it up by space
            string t = ""; trav(x, v) t += x;
            string a = t.substr(0, t.find(' '));
            string b = t.substr(t.find(' ')+1);
            // dbg(t, a, b);
            if (dict.count(a) && dict.count(b)) {
                dbg(cur, t, a, b);
                if (a > b) swap(a, b);
                string x = a+" "+b;
                if (a == "") x = b;
                if (cur > hi) {
                    hi = cur;
                    ans.clear();
                }
                if (hi == cur) ans.insert(x);
            }
        } while (next_permutation(all(v)));
    }
    cout << hi << nl;
    dbg(sz(ans));
    trav(x, ans) cout << x << nl;
    return 0;
}
