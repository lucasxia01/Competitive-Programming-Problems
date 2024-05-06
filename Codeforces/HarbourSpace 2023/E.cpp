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
const ll MOD = 998244353;
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

ll mod_pow(ll a, ll b) {
    if (b == 0) return 1LL;
    ll p = mod_pow(a, b >> 1);
    p = p * p % MOD;
    if (b & 1)
        p = p * a % MOD;
    return p;
}

ll mod_inv(ll n) {
    return mod_pow(n, MOD - 2);
}

struct Node {
    int cnt = 0;
    int subtreeSZ = -1;
    Node *c[2];
    Node() {
        c[0] = c[1] = NULL;
    }
    int SZ() {
        int ans = cnt;
        if (c[0]) ans += c[0]->SZ();
        if (c[1]) ans += c[1]->SZ();
        subtreeSZ = ans;
        return ans;
    }
    void insert(vector<bool>& v, int idx) {
        if (idx == 30) {
            cnt++;
            return;
        }
        if (!c[v[idx]]) c[v[idx]] = new Node();
        c[v[idx]]->insert(v, idx+1);
    }
};

int cSize(Node* r) {
    if (r) return r->subtreeSZ;
    return 0;
}

ll mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int a[n]; F0R(i, n) cin >> a[i];
        Node root;
        dbg(sizeof(root));
        vector<bool> s[n];
        F0R(i, n) {
            vector<bool> v;
            int tmp = a[i];
            F0R(j, 30) {
                v.pb(a[i]%2);
                a[i]/=2;
            }
            a[i] = tmp;
            reverse(all(v));
            s[i] = v;
            root.insert(v, 0);
        }
        assert(root.SZ() == n);
        int ans = 0;
        F0R(i, n) {
            int tmp = 0;
            // traverse the shit and do the thing
            Node *cur = &root;
            int cnt = 0;
            int sum = 0;
            F0R(j, 30) {
                if (s[i][j] == 0) {
                    // check how many are 1
                    int SZ = cSize(cur->c[1]);
                    if (cnt%2 == 0) tmp += mod(1LL*(cnt+1)*SZ);
                    else tmp += mod((cnt+2)*SZ);
                    tmp %= MOD;
                } else {
                    int SZ = cSize(cur->c[0]);
                    if (cnt%2==0) tmp += mod(1LL*(cnt+2)*SZ);
                    else tmp += (1LL*mod((cnt+1)*SZ));
                    tmp %= MOD;
                    cnt++;
                }
                cur = cur->c[s[i][j]];
            }
            int SZ = cSize(cur);
            // now check how many are same
            dbg(a[i], SZ, tmp);
            cnt++;
            tmp += mod(1LL*cnt*SZ);
            ans += tmp;
            ans %= MOD;
        }
        dbg("before n*n", ans);
        int INVN = mod_inv(n);
        cout << (((1LL*ans*INVN)%MOD)*INVN)%MOD << nl;
    }
    return 0;
}
