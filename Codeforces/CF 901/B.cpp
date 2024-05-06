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

int conv(vi v) {
    int ret = 0;
    int pow = 1;
    F0R(i, sz(v)) {
        if (v[i] == -1) v[i] = 0;
        ret += pow*v[i];
        pow *= 4;
    }
    return ret;
}

int conv2(vi v) {
    int ret = 0;
    int pow = 1;
    F0R(i, 16) {
        if (v[i] == -1) v[i] = 0;
        ret += pow*v[i];
        pow *= 2;
    }
    return ret;
}

vi rconv2(int x) {
    vi ret;
    F0R(i, 16) {
        ret.pb(x%2);
        x /= 2;
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        int a, b, c, d, m; cin >> a >> b >> c >> d >> m;
        vi val(8, -1);
        bool ok = 1;
        F0R(i, 30) {
            int x = ((a>>i)&1);
            int y = ((b>>i)&1);
            int w = ((c>>i)&1);
            int z = ((d>>i)&1);
            int k = ((m>>i)&1);
            int pos = 4*k+2*y+x;
            int nxt = 2*z+w;
            if (val[pos] == -1) val[pos] = nxt;
            ok &= (val[pos]==nxt);
        }
        if (!ok) {
            cout << -1 << nl;
            continue;
        }
        vi goal = rconv2(conv(val));
        F0R(i, 8) {
            if (val[i] == -1) goal[2*i]=goal[2*i+1] = -1;
        }
        // F0R(i, 16) cout << goal[i] << ' ';
        // cout << nl;
        vi first;
        F0R(i, 8) {
            first.pb(i%4);
        }
        bool found = 0;
        int ans = -1;
        // now that we have the mapping, we need to run bfs on the 256 states
        unordered_map<int, int> dist;
        dist[conv(first)] = 0;
        queue<int> q; q.push(conv(first));
        while (!q.empty()) {
            int curV = q.front(); q.pop();
            
            vi cur = rconv2(curV);
            // cout << dist[curV] << nl;
            // F0R(i, 16) cout << cur[i] << ' ';
            // cout << nl;
            bool good = 1;
            F0R(i, 16) {
                if (goal[i] == -1) continue;
                if (goal[i] != cur[i]) {
                    good = 0;
                    break;
                }
            }
            if (good) {
                found = 1;
                ans = dist[curV];
                break;
            }
            // do the operations
            vi nxt = cur;
            F0R(i, 8) {
                nxt[2*i] &= nxt[2*i+1];
            }
            int nxtV = conv2(nxt);
            if (dist.find(nxtV) == dist.end()) {
                dist[nxtV] = dist[curV]+1;
                q.push(nxtV);
            }

            nxt = cur;
            F0R(i, 8) {
                nxt[2*i] |= nxt[2*i+1];
            }
            nxtV = conv2(nxt);
            if (dist.find(nxtV) == dist.end()) {
                dist[nxtV] = dist[curV]+1;
                q.push(nxtV);
            }

            nxt = cur;
            F0R(i, 8) {
                nxt[2*i+1] ^= nxt[2*i];
            }
            nxtV = conv2(nxt);
            if (dist.find(nxtV) == dist.end()) {
                dist[nxtV] = dist[curV]+1;
                q.push(nxtV);
            }

            nxt = cur;
            FOR(i, 4, 7) {
                nxt[2*i+1] ^= 1;
            }
            nxtV = conv2(nxt);
            if (dist.find(nxtV) == dist.end()) {
                dist[nxtV] = dist[curV]+1;
                q.push(nxtV);
            }
        }
        if (found) cout << ans << nl;
        else cout << -1 << nl;
    }
    return 0;
}
