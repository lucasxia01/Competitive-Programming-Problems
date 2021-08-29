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

string lower(string s) {
    string t = "";
    F0R(i, (int)s.length()) t += tolower(s[i]);
    return t;
}

void print_word(string s) {
    cout << "What does the word \"" << s << "\" mean?" << nl;
}
void print_sent(string s) {
    s.erase(--s.end());
    if (s.find(" ") == -1) return;
    cout << "What does the sentence \"" << s << "\" mean?" << nl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    string term = ".,:;?!#*";
    int casecnt = 1;
    while (cin >> n) {
        cout << "Learning case " << casecnt++ << nl;
        set<string> seen;
        set<string> seenSubs;
        seen.insert("joe");
        seenSubs.insert("joe ");
        // learning phase
        while (1) {
            string s;
            vector<string> sent;
            while (cin >> s && term.find(s) == -1) {
//                dbg(s);
                string t = lower(s);
                sent.pb(t);
                if (seen.find(t) == seen.end()) seen.insert(t);
            }
            if (s == "*") {
                if (sz(sent)) seenSubs.insert(sent[0]+' ');
                break;
            } else {
                // store the sentence
                int len = sz(sent);
                F0R(i, len) {
                    string cur = "";
                    F0R(j, n) {
                        if (i+j >= len) break;
                        cur += sent[i+j] + ' ';
                        seenSubs.insert(cur);
                    }
                }
            }
        }
        
        // checking phase
        while (1) {
            string s;
            vector<string> sent;
            string Sent = "";
            while (cin >> s && term.find(s) == -1) {
                string t = lower(s);
                sent.pb(t);
                Sent += s + ' ';
                if (seen.find(t) == seen.end()) {
                    print_word(s);
                    seen.insert(t);
                }
            }
            if (s == "#") {
                if (sz(sent)) seenSubs.insert(sent[0]+' ');
                break;
            } else {
                // check if the sentence is understood
                bool ok = 1;
                int len = sz(sent);
                F0R(i, len) {
                    string cur = "";
                    F0R(j, n) {
                        if (i+j >= len) break;
                        cur += sent[i+j] + ' ';
                        if (seenSubs.find(cur) == seenSubs.end()) {
                            ok = 0;
                            seenSubs.insert(cur);
                        }
                    }
                }
                if (!ok) print_sent(Sent);
            }
        }
        cout << nl;
    }
    return 0;
}
