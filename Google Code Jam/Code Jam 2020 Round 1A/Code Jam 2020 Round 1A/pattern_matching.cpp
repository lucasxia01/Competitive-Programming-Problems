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
#define lb lower_bound
#define ub upper_bound
#define sz(x) (int)x.size()

const int MAX_N = 100011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

template <typename T> bool ckmin(T& a, const T& b) {
    return a > b ? a=b, 1 : 0;
}
template <typename T> bool ckmax(T& a, const T& b) {
    return b > a ? a=b, 1 : 0;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

void print(int i, string s) {
    cout << "Case #" << i << ": " << s << '\n';
}

bool strcmplen(string a, string b) {
    return a.length() > b.length();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    FOR(t, 1, T) {
        int n;
        cin >> n;
        string s[n];
        int noAst = -1;
        vector<string> pref, suf; // main idea is only check prefixes and suffixes
        string str = ""; // otherwise, add in everything to the middle
        F0R(i, n) {
            cin >> s[i];
            if (s[i].find("*") == -1) {
                noAst = i;
                break;
            }
            int f = s[i].find_first_of('*'), l = s[i].find_last_of('*');
            pref.pb(s[i].substr(0, f));
            suf.pb(s[i].substr(l+1));
            if (f == l) continue;
            string t = s[i].substr(f+1, l-f-1);
            F0R(j, t.length()) if (t[j] != '*') str += t[j];
        }
        bool ok = true;
        if (noAst != -1) {
            F0R(i, n) {
                if (s[i] != s[noAst]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) print(t, "*");
            else print(t, s[noAst]);
            continue;
        }
        sort(pref.begin(), pref.end(), strcmplen);
        sort(suf.begin(), suf.end(), strcmplen);
        trav(a, pref) if (a != pref[0].substr(0, a.length())) {
            ok = false;}
        trav(a, suf) {
            if (a != suf[0].substr(suf[0].length()-a.length())) {
                ok = false;
            }
        }
        if (!ok) print(t, "*");
        else print(t, pref[0]+str+suf[0]);
    }
    return 0;
}
