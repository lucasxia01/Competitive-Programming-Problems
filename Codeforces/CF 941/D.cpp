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

/**** Credit to chatgpt 4.0 ****/

// Stream operator for std::pair
template<typename T1, typename T2>
ostream& operator<<(ostream &out, const pair<T1, T2> &v) {
    out << "(" << v.first << ", " << v.second << ")"; 
    return out;
}

// Trait to check if a type is iterable
template<typename T, typename = void>
struct is_iterable : false_type {};

template<typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

// Stream operator for iterable types excluding std::string
template<typename TT>
typename enable_if<is_iterable<TT>::value && !is_same<TT, string>::value, ostream&>::type
operator<<(ostream& out, const TT& c) {
    out << "{ ";
    for (const auto& x : c) out << x << " ";
    out << "}"; 
    return out;
}

template<typename T>
ostream& operator<<(ostream& out, std::stack<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.top());
        container.pop();
    }
    std::reverse(elements.begin(), elements.end()); // Reverse to maintain order
    return out << elements;
}

template<typename T>
ostream& operator<<(ostream& out, std::queue<T> container) {
    std::vector<T> elements;
    while (!container.empty()) {
        elements.push_back(container.front());
        container.pop();
    }
    return out << elements;
}

// Helper function to print std::priority_queue
template<typename T, typename Container, typename Compare>
ostream& operator<<(ostream& out, std::priority_queue<T, Container, Compare> pq) {
    out << "{";
    while (!pq.empty()) {
        out << " " << pq.top();
        pq.pop();
    }
    out << " }";
    return out;
}

#ifdef DBG
void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":", dbg_out(__VA_ARGS__);
#define dbg_array(a, n) cerr << #a << ": { "; for(int i = 0; i < n; i++) cerr << a[i] << " "; cerr << "}\n";
#else
#define dbg(...)
#define dbg_array(a, n)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 3e5+5;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<int, int> m;
        F0R(i, n*(n+1)/2 - 1) {
            int x; cin >> x;
            m[x]++;
        }
        // find number of odd
        vi odds;
        trav(p, m) {
            if (p.s%2) odds.pb(p.f);
        }
        sort(all(odds));
        int mids = (n+1)/2;
        int found = 0;
        if (sz(odds) == mids+1) { // we are missing a paired one
            int sum = 0;
            F0R(i, mids+1) {
                odds[i] = odds[i]-sum;
                sum += odds[i];
            }
            dbg(odds);
            int l = 0, r = 0;
            vi pts;
            if (odds[1]%2 == 1 && odds[2]%2 == 0) {
                odds[1] += odds[0];
                found++;
                odds.erase(odds.begin());
            }
            F0R(i, sz(odds)) {
                dbg(i, odds[i]);
                if (i == 0) {
                    if (n%2) {
                        l = 0, r = odds[i];
                        pts.pb(l);
                        pts.pb(r);
                        continue;
                    } else {
                        pts.pb(0);
                    }
                }
                // now we have to check that odds[i] is even
                if (odds[i]%2) {
                    // if its not even, then we know this is the bad one
                    found++;
                    odds[i+1] += odds[i];
                    assert(i+1 < mids+1);
                    continue;
                }
                l -= odds[i]/2;
                r += odds[i]/2;
                pts.pb(r);
                pts.pb(l);
            }
            sort(all(pts));
            dbg(pts);
            if (sz(pts) == n+1) {
                // we're done
                assert(found == 1);
                F0R(i, n) cout << pts[i+1]-pts[i] << ' ';
                cout << nl;
            } else {
                assert(found == 0);
                assert(sz(pts) == n+3);
                // generate all the subarray lengths
                map<int, int> m2;
                F0R(i, sz(pts)) {
                    F0R(j, i) {
                        m2[pts[i]-pts[j]]++;
                    }
                }
                trav(p, m) {
                    // subtract it from m2
                    assert(m2[p.f] > 0);
                    m2[p.f] -= p.s;
                    assert(m2[p.f] >= 0);
                }
                // now for the remaining, we should have n+2 pairs
                // try assuming each point is invalid
                bool good = 0;
                F0R(i, sz(pts)) {
                    map<int, int> cur_m;
                    F0R(j, sz(pts)) {
                        if (i == j) continue;
                        cur_m[abs(pts[i]-pts[j])]++;
                    }
                    bool ok = 1;
                    trav(p, cur_m) {
                        if (m2[p.f] != 2*p.s) {
                            ok = 0;
                            break;
                        }
                    }
                    if (ok) {
                        assert(i != 0 && i != sz(pts)-1);
                        // i is the loser
                        int prev = 0;
                        F0R(j, sz(pts)-1) {
                            if (j+1 == i || j+1 == sz(pts)-1-i) continue;
                            cout << pts[j+1]-pts[prev] << ' ';
                            prev = j+1;
                        }
                        cout << nl;
                        good = 1;
                        break;
                    }
                }
                assert(good);
            }
        } else if (sz(odds) == mids-1) { // we are missing an unpaired one
            int sum = 0;
            F0R(i, mids-1) {
                odds[i] = odds[i]-sum;
                sum += odds[i];
            }
            dbg(odds);
            int l = 0, r = 0;
            vi pts;
            F0R(i, sz(odds)) {
                dbg(i, odds[i]);
                if (i == 0) {
                    if (n%2) {
                        l = 0, r = odds[i];
                        pts.pb(l);
                        pts.pb(r);
                        continue;
                    } else {
                        pts.pb(0);
                    }
                }
                // now we have to check that odds[i] is even
                assert(odds[i]%2 == 0);
                l -= odds[i]/2;
                r += odds[i]/2;
                pts.pb(r);
                pts.pb(l);
            }
            sort(all(pts));
            dbg(pts);
            assert(sz(pts) == n-1);
            map<int, int> m2;
            F0R(i, n-1) {
                F0R(j, i) {
                    m2[pts[i]-pts[j]]++;
                }
            }
            // subtract it from m
            trav(p, m2) {
                assert(m[p.f] > 0);
                m[p.f] -= p.s;
                assert(m[p.f] >= 0);
                if (m[p.f] == 0) m.erase(p.f);
            }
            assert(sz(m) > 0);
            // m should have 2n-2 things total
            int small = m.begin()->f;
            // we know its small away from a pt
            bool good = 0;
            F0R(i, sz(pts)) {
                // just try pts[i]-small and pts[i]+small
                map<int, int> cur_m;
                F0R(j, sz(pts)) {
                    cur_m[abs(pts[i]-small-pts[j])]++;
                }
                bool ok = 1;
                trav(p, cur_m) {
                    if (m[p.f] != 2*p.s) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    // then its pts[i]-small
                    pts.pb(pts[i]-small);
                    pts.pb(pts[n-2-i]+small);
                    dbg(pts[i]-small, pts);
                    sort(all(pts));
                    F0R(i, n) cout << pts[i+1]-pts[i] << ' ';
                    cout << nl;
                    good = 1;
                    break;
                }

                ok = 0;
                cur_m.clear();

                F0R(j, sz(pts)) {
                    cur_m[abs(pts[i]+small-pts[j])]++;
                }
                trav(p, cur_m) {
                    if (m[p.f] != 2*p.s) {
                        ok = 0;
                        break;
                    }
                }
                if (ok) {
                    // then its pts[i]+small
                    pts.pb(pts[i]+small);
                    pts.pb(pts[n-2-i]-small);
                    dbg(pts[i]+small, pts);
                    sort(all(pts));
                    F0R(i, n) cout << pts[i+1]-pts[i] << ' ';
                    cout << nl;
                    good = 1;
                    break;
                }
            }
            assert(good);
        } else assert(0);
    }
    return 0;
}
