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
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[5][n]; 
        int freq[5][10]; F0R(i, 5) F0R(j, 10) freq[i][j] = 0;
        F0R(i, n) {
            cin >> a[0][i];
            freq[0][a[0][i]]++;
        }
        cout << "- 0" << endl;
        cout.flush(); fflush(stdout);
        bool found = 0;
        F0R(k, 2) {
            F0R(i, n) {
                cin >> a[k+1][i];
                freq[k+1][a[k+1][i]]++;
            }
            FOR(i, 1, 9) {
                if (freq[k+1][i] > freq[0][i]) {
                    // remove everything else but i
                    found = 1;
                    vi v;
                    int total = 0;
                    F0R(j, n) {
                        if (a[k+1][j] != i) {
                            v.pb(j+1);
                            total++;
                        }
                    }
                    cout << "- " << sz(v);
                    trav(u, v) cout << " " << u;
                    cout << endl;
                    cout.flush(); fflush(stdout);
                    n-=total;

                    // set up freq[2]
                    FOR(j, 1, 9) {
                        if (j != i) freq[2][j] = 0;
                        else freq[2][j] = freq[k+1][i];
                    }
                    break;
                }
            }
            if (!found) {
                cout << "- 0" << endl;
                cout.flush(); fflush(stdout);
            } else break;
        }
        if (!found) assert(0);
        // now just wait for the change to happen
        found = 0;
        F0R(k, 2) {
            F0R(i, n) {
                cin >> a[3+k][i];
                freq[k+3][a[k+3][i]]++;
            }
            FOR(i, 1, 9) {
                if (freq[k+3][i] > freq[2][i]) {
                    // remove everything else but i
                    found = 1;
                    dbg("found 2");
                    F0R(j, n) {
                        if (a[k+3][j] == i) {
                            cout << "! " << j+1 << endl;
                            cout.flush(); fflush(stdout);
                            break;
                        }
                    }
                    break;
                }
            }
            if (!found) {
                cout << "- 0" << endl;
                cout.flush(); fflush(stdout);
            } else break;
        }
        if (!found) assert(0);
    }
    return 0;
}
