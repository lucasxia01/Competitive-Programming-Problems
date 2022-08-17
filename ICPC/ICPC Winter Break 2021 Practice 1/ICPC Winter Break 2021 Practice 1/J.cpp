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

set<string> vis;
map<string, vector<string> > gr;

string goal = "";
bool dfs(string n, vector<string> path) {
    if (vis.find(n) != vis.end()) return false;
    vis.insert(n);
    if (n == goal) {
        trav(v, path) {
            cout << v << " ";
        }
        cout << nl;
        return true;
    }
    trav(v, gr[n]) {
        path.pb(v);
        if (dfs(v, path)) return true;
        path.pop_back();
    }
    return false;
}

int n;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    string s;
    getline(cin, s);
    F0R(i, n) {
        getline(cin, s);
        int pos = 0;
        string token;
        int x = 0;
        string t = "";
        while ((pos = s.find(" ")) != string::npos) {
            token = s.substr(0, pos);
            if (x == 0) {
                vector<string> temp;
                gr[token] = temp;
                t = token;
                x++;
            } else {
                gr[t].pb(token);
                if (gr.find(token) == gr.end()) {
                    vector<string> temp;
                    gr[token] = temp;
                }
                gr[token].pb(t);
            }
            s.erase(0, pos + 1);
        }
        gr[t].pb(s);
        if (gr.find(s) == gr.end()) {
            vector<string> temp;
            gr[s] = temp;
        }
        gr[s].pb(t);
    }
    string start;
    cin >> start >> goal;
    vector<string> temp;
    temp.pb(start);
    if (!dfs(start, temp)) cout << "no route found" << nl;
    
    return 0;
}
