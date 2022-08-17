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
 
// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};
 
#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif
 
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
const int MX = 1<<20;
 
string f(vi freq) {
    string ret = "";
    F0R(i, 26) {
        while (freq[i]--) {
            ret += ('a'+i);
        }
    }
    return ret;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        string ans = "";
        vi freq(26, 0);
        F0R(i, sz(s)) freq[s[i]-'a']++;
        F0R(i, 26) {
            if (freq[i] == 1) {
                ans += (char)(i+'a');
                freq[i]--;
                ans += f(freq);
                break;
            }
        }
        if (sz(ans) == sz(s)) {
            cout << ans << nl;
            continue;
        }
        int cnt = 0;
        F0R(i, 26) {
            cnt += (freq[i] > 0);
        }
        if (cnt == 1) {
            ans = f(freq);
            cout << ans << nl;
            continue;
        }
        int m = 0;
        while (freq[m] == 0) m++;
        int N = freq[m];
        int num = freq[m];
        freq[m] = 0;
        string rest = f(freq);
        int rest_ptr = 0;
        ans = "";
        ans += (m+'a');
        ans += (m+'a');
        num -= 2;
        while (rest_ptr < sz(rest) && num) {
            ans += rest[rest_ptr++];
            ans += (m+'a');
            num--;
        }
        if (num == 0) {
            while (rest_ptr < sz(rest)) ans += rest[rest_ptr++];
            cout << ans << nl;
            continue;
        }
        // else we can't have two m's at the start
        num = N;
        rest_ptr = 0;
        ans = "";
        ans += (m+'a'); num--;
        if (cnt == 2) { // this is the best option: abbbbbaaaaaaaa
            ans += rest;
            F0R(i, num) ans += (m+'a');
            cout << ans << nl;
        } else { // we can now use a c to help: abaaaaaaaaaaacbbbbbccccc, etc...
            string temp = "";
            ans += rest[rest_ptr++];
            F0R(i, num) ans += (m+'a');
            int ptr = rest_ptr;
            while (rest_ptr < sz(rest) && rest[rest_ptr] == rest[ptr]) {
                temp += rest[rest_ptr++];
            }
            ans += rest[rest_ptr++];
            ans += temp;
            ans += rest.substr(rest_ptr);
            cout << ans << nl;
        }
    }
    return 0;
}