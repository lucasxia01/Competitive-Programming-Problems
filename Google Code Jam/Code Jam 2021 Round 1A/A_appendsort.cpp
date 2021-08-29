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

string inc(string s) {
    int len = s.length();
    string ret = "";
    bool done = 0;
    F0Rd(i, len) {
        if (done) { 
            ret += s[i];
            continue;
        }
        if (s[i]-'0' + 1 == 10) {
            ret += '0';
        } else {
            ret += (s[i]+1);
            done = 1;
        }
    }
    if (!done) ret += '1';
    reverse(all(ret));
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    F0R(tt, t) {
        int n; cin >> n;
        string a[n]; F0R(i, n) cin >> a[i];
        int ans = 0;
        FOR(i, 1, n-1) {
            // try all 0s first, then all 9s
            if ((a[i-1] < a[i] && a[i-1].length() == a[i].length()) || a[i-1].length() < a[i].length()) continue; // we chilling
            else if (a[i-1].length() == a[i].length()) {
                a[i] += '0';
                ans++;
            } else { // a[i] is smaller length
                int len = a[i].length();
                string S = inc(a[i-1]);
                // dbg(a[i-1], S);
                string s = S.substr(0, len);
                string t = a[i];
                if (s == a[i]) {
                    ans += S.length()-len;
                    a[i] = S;
                } else if (s < a[i]) {
                    // add all 0s
                    F0R(j, S.length()-len) { a[i] += '0'; ans++; }
                } else {
                    F0R(j, S.length()-len+1) { a[i] += '0'; ans++; }
                }
            }
        }
        cout << "Case #" << tt+1 << ": " << ans << nl;
    }
    
    return 0;
}
