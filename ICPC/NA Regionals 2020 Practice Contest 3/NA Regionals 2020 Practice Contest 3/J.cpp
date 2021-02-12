#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <chrono>
#include <cassert>
#include <climits>

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
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#else
#define dbg(...) dbg_out(__VA_ARGS__);
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll n, m, k; cin >> n >> m >> k;
    priority_queue<pair<string, ll>, vector<pair<string, ll> >, greater<pair<string, ll> > > pq;
    pq.push({"Jane Eyre", k});
    string s;
    getline(cin, s);
    F0R(i, n) {
        getline(cin, s);
        s = s.substr(1);
        string t = s.substr(0, s.find('\"'));
        string temp = s.substr(s.find('\"')+2);
        pq.push({t, stoi(temp)});
    }
    ll time = 0;
    vector<pair<ll, pair<string, ll> > > v;
    F0R(i, m) {
        ll x; cin >> x;
        getline(cin, s);
        s = s.substr(2);
        string t = s.substr(0, s.find('\"'));
        string temp = s.substr(s.find('\"')+2);
        v.pb({x, {t, stoi(temp)}});
    }
    sort(all(v));
    int ptrV = 0;
    while (1) {
        // first add into the pq
        while (ptrV < sz(v) && v[ptrV].f <= time) {
            pq.push(v[ptrV++].s);
        }
        pair<string, int> p = pq.top(); pq.pop();
        time += p.s;
//        dbg(p.f, p.s);
        if (p.f == "Jane Eyre") break;
    }
    cout << time << nl;
    return 0;
}
