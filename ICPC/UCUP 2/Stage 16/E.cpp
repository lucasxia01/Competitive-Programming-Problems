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
#else
#define dbg(...)
#endif

mt19937_64 rng(213098);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string S; cin >> S;
    vector<string> PASSWORDS;
    vector<pair<string, string> > KEYS;
    if (S == "password") {
        int n; cin >> n;
        F0R(i, n) {
            string s; cin >> s;
            PASSWORDS.pb(s);
        }
    } else {
        int n; cin >> n;
        F0R(i, n) {
            string s1, s2; cin >> s1 >> s2;
            KEYS.pb({s1, s2});
        }
    }
    // check if it works
    int n8; cin >> n8;
    vector<string> v8, v4;
    F0R(i, n8) {
        string s;
        cin >> s;
        v8.pb(s);
    }
    int n4; cin >> n4;
    F0R(i, n4) {
        string s;
        cin >> s;
        v4.pb(s);
    }
    vector<pair<int, string> > v;
    map<string, vector<string> > keys;
    map<pair<string, string>, string> password;
    trav(s, v8) {
        int freq[26] = {};
        F0R(i, 8) freq[s[i]-'a']++;
        int cnt = 0;
        trav(t, v4) {
            bool ok = 1;
            F0R(i, 4) {
                freq[t[i]-'a']--;
                if (freq[t[i]-'a'] == -1) {
                    ok = 0;
                }
            }
            F0R(i, 4) {
                freq[t[i]-'a']++;
            }
            if (ok) {
                cnt++;
                keys[s].pb(t);
            }
        }
        v.pb({cnt, s});
    }
    sort(all(v));
    // pick 3 randomly without repeating pairs
    set<pair<string, string> > pairs;
    map<string, vector<string> > ass_keys;
    int bad = 0;
    int cnt = 0;
    trav(p, v) {
        string c = p.s;
        // pick 3 randomly
        int len = sz(keys[c]);
        if (len < 3) {
            bad++;
            continue;
        }
        F0R(i, 100000) {
            if (i == 99999) {
                // try single ones now
                bool win = 0;
                trav(t, keys[c]) {
                    if (pairs.count({t, t})) continue;
                    pairs.insert({t, t});
                    ass_keys[c] = {t, t, t};
                    password[{t, t}] = c;
                    win = 1;
                    break;
                }
                if (win) break;
                dbg(c, cnt, sz(keys[c]));
                trav(t, keys[c]) {
                    dbg(t);
                }
                assert(0);
            }
            // generate 3 distinct values
            int aa = rng()%len;
            int bb = rng()%(len-1);
            int cc = rng()%(len-2);
            cc += (cc >= bb);
            cc += (cc >= aa);
            bb += (bb >= aa);
            assert(aa != bb && bb != cc && cc != aa);
            string x = keys[c][aa];
            string y = keys[c][bb];
            string z = keys[c][cc];
            if (pairs.count({x, y}) || pairs.count({y, z}) || pairs.count({x, z})) continue;
            pairs.insert({x, y});
            pairs.insert({y, x});
            pairs.insert({y, z});
            pairs.insert({z, y});
            pairs.insert({z, x});
            pairs.insert({x, z});
            ass_keys[c] = {x, y, z};
            password[{x, y}] = c;
            password[{y, x}] = c;
            password[{y, z}] = c;
            password[{z, y}] = c;
            password[{z, x}] = c;
            password[{x, z}] = c;
            break;
        }
        cnt++;
    }
    assert(bad == 70);
    dbg("all matched up");
    if (S == "password") {
        trav(s, PASSWORDS) {
            trav(t, ass_keys[s]) cout << t << " ";
            cout << nl;
        }
    } else {
        trav(s, KEYS) {
            cout << password[{s.f, s.s}] << nl;
        }
    }
    return 0;
}
