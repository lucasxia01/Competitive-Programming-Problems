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

int n;
int race(const set<int>& v) {
    assert(sz(v) == n);
    cout << "? ";
    trav(u, v) cout << u << " ";
    cout << endl;
    cout.flush();
    int x; cin >> x;
    return x;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t = 1; 
    cin >> t;
    while (t--) {
        cin >> n;
        int total = n*n - n + 1;
        // race the pepes
        vector<set<int> > groups(n);
        F0R(i, n) {
            F0R(j, n) groups[i].insert(i*n+j+1);
        }
        vi ans;
        vi fastest(n);
        int updated = -1;
        set<int> last_winners;
        set<int> last_losers;
        while (1) {
            if (updated == -1) {
                F0R(i, n) {
                    set<int> v = groups[i];
                    int x = race(v);
                    fastest[i] = x;
                }
            } else {
                // find which bucket it came from
                F0R(i, n) {
                    if (groups[i].count(updated)) {
                        // remove from this group and recalculate this
                        groups[i].erase(groups[i].find(updated));
                        // we need to move things to this group and recalculate
                        // add stuff to this group
                        F0R(j, n) {
                            if (sz(groups[i]) == n) break;
                            if (i!=j) {
                                // move stuff that are not winners from j to i
                                for (auto it = groups[j].begin(); it != groups[j].end(); ) {
                                    if (*it == fastest[j]) {
                                        ++it;
                                        continue;
                                    }
                                    dbg("moving", *it, "from", j, "to", i);
                                    groups[i].insert(*it);
                                    groups[j].erase(it++);
                                    if (sz(groups[i]) == n) {
                                        break;
                                    }
                                }
                            }
                        }
                        int y = race(groups[i]);
                        fastest[i] = y;
                        break;
                    }
                }
            }
            if (total == n) {
                dbg("breaking out with n to go");
                F0R(i, n) last_winners.insert(fastest[i]);
                F0R(i, n) trav(x, groups[i]) if (x != fastest[i]) last_losers.insert(x);
                break;
            }
            set<int> s; 
            F0R(i, n) s.insert(fastest[i]);
            int x = race(s);
            ans.pb(x);
            updated = x;
            total--;
        }
        assert(sz(last_winners) == n);
        assert(sz(last_losers) == n-1);
        // total is 2*n-1 now
        F0R(i, n-1) {
            // race them
            set<int> s = last_winners;
            dbg("race", i);
            trav(x, last_losers) if (sz(s) < n) s.insert(x);
            int x = race(s);
            ans.pb(x);
            last_winners.erase(x);
        }
        assert(sz(last_winners) == 1);
        ans.pb(*last_winners.begin());
        // race these fast pepes and insert the remaining garbage
        cout << "! ";
        trav(a, ans) cout << a << " ";
        cout << endl;
    }
    return 0;
}