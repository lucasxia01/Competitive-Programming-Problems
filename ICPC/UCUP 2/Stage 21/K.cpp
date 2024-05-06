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
        // n = 6k + 2..7
        // first, removing the big square in bottom right

        // then with the remaining shitters, fill it in lets go
        char ans[n][n]; F0R(i, n) F0R(j, n) ans[i][j] = '.';
        int N = n;
        n++;
        int rem = n%6;
        n -= rem;
        if (rem == 1) {
            n-=6;
            rem+=6;
        }
        // solve for rem by rem
        if (rem == 3) {
            ans[0][0] = ans[0][1] = '#';
        } else if (rem == 4) {
            ans[0][0] = ans[0][1] = ans[2][0] = ans[2][1] = '#';
        } else if (rem == 5) {
            ans[0][0] = ans[0][1] = ans[2][0] = ans[3][0] = 
                ans[3][2] = ans[3][3] = ans[1][3] = ans[0][3] = '#';
        } else if (rem == 7) {
            ans[0][0] = ans[0][1] = ans[2][0] = ans[2][1] = '#';
            // rotate 90 degrees
            ans[5][0] = ans[4][0] = ans[5][2] = ans[4][2] = '#';
            // rotate 90 degrees
            ans[5][5] = ans[5][4] = ans[3][5] = ans[3][4] = '#';
            // rotate 90 degrees
            ans[0][5] = ans[1][5] = ans[0][3] = ans[1][3] = '#';
        }
        // now solve each of the rectangles
        // n x rem
        dbg(n);
        F0R(i, n/6) {
            // we can add up 2s and 3s to get 2 through 7
            int ii = i*6 + rem;
            int j = 0;
            while (j < rem) {
                if (rem-j == 3) {
                    ans[j][ii] = ans[j+1][ii] = '#';
                    ans[j][ii+2] = ans[j+1][ii+2] = '#';
                    ans[j][ii+4] = ans[j+1][ii+4] = '#';
                    j += 3;
                } else {
                    ans[j][ii] = ans[j][ii+1] = '#';
                    ans[j][ii+3] = ans[j][ii+4] = '#';
                    j += 2;
                }
            }
        }
        // solve for bottom left rectangle
        F0R(i, n/6) {
            int ii = i*6 + rem;
            int j = 0;
            while (j < rem) {
                if (rem-j == 3) {
                    ans[ii][j] = ans[ii][j+1] = '#';
                    ans[ii+2][j] = ans[ii+2][j+1] = '#';
                    ans[ii+4][j] = ans[ii+4][j+1] = '#';
                    j += 3;
                } else {
                    ans[ii][j] = ans[ii+1][j] = '#';
                    ans[ii+3][j] = ans[ii+4][j] = '#';
                    j += 2;
                }
            }
        }

        // solve bottom left
        F0R(i, n/6) F0R(j, n/6) {
            int ii = i*6 + rem;
            int jj = j*6 + rem;
            // place a square here
            F0R(k, 3) F0R(l, 2) F0R(m, 2) {
                ans[ii+2*k][jj+3*l+m] = '#';
            }
        }
        F0R(i, N) {
            F0R(j, N) cout << ans[i][j];
            cout << nl;
        }
        
    }
    return 0;
}
