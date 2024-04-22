#include <bits/stdc++.h>
using namespace std;

#define int ll
#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

#define trav(a, x) for(auto& a : x)
#define f first
#define s second
#define pb push_back
const char ln = '\n';
const int INF = int(1e9);

#ifdef DBG
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) dbg_out(__VA_ARGS__);
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct s1 {
    int l, r, val, id, lid, rid;
    bool operator<(const s1 a) const {
        if(l == a.l)
            return r < a.r;
        return l < a.l;
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n);
    int m = 0, cost = 0;
    rep(i, 0, n) { 
        cin >> a[i];
        cost += a[i];
    }
    rep(i, 0, n-1)
        m += abs(a[i] - a[i+1]);
    m -= a[0] + a[n-1];

    //set<s1> sg;
    vector<s1> sg = {s1{-1, 0, INF, 0, -1, 1}};
    //priority_queue<s2, vector<s2>, greater<s2>> pq;
    vector<vector<s1>> bs(n+1);
    int mlen = 0;
    int id = 1;
    for(int i = 0; i < n;) {
        int j = i+1;
        while(j < n && a[j] == a[i]) j++;
        s1 cur = s1{i, j, a[i], id, id-1, id+1};
        sg.pb(cur);
        if(!((i > 0 && a[i-1] < a[i]) || (j < n && a[j] < a[j-1])))
            bs[j - i].pb(cur);
        i = j;
        id++;
    }
    sg.pb(s1{n, n+1, INF, id, id-1, -1});
    while(m > 0) {
        while(sz(bs[mlen]) == 0) { 
            // if(mlen == n) {
            //     rep(i, 0, n)
            //         cout << a[i] << " ";
            //     cout << endl;
            // }
            mlen++;
        }
        s1 s = bs[mlen].back();
        bs[mlen].pop_back();
        s = sg[s.id];
        //dbg("mlen: ", mlen);
        //dbg("Segment: ", s.l, s.r, s.val);
        s1 l = sg[s.lid];
        s1 r = sg[s.rid];
        //dbg("Left: ", l.l, l.r, l.val);
        //dbg("Right: ", r.l, r.r, r.val);
        if(2*(min(l.val, r.val) - s.val) >= m) {
            cost += (m/2)*(s.r - s.l);
            break;
        }
        m -= 2*(min(l.val, r.val) - s.val);
        cost += (s.r - s.l)*(min(l.val, r.val) - s.val);
        //sg.erase(s1{s.l, s.r, s.val});
        // rep(i, s.l, s.r)
        //     a[i] = min(l.val, r.val);
        if(l.val < r.val) {
            //dbg("Merging Left");
            s1 ll = sg[l.lid];
            
            sg[s.id] = s1{l.l, s.r, l.val, s.id, l.lid, s.rid};
            if(ll.val > l.val)
                bs[s.r - l.l].pb(sg[s.id]);
            sg[l.lid].rid = s.id;
        } else if(l.val > r.val) {
            //dbg("Merging Right");
            s1 rr = sg[r.rid];
            sg[s.id] = s1{s.l, r.r, r.val, s.id, s.lid, r.rid};
            if(rr.val > r.val)
                bs[r.r-s.l].pb(sg[s.id]);
            sg[r.rid].lid = s.id;
        } else {
            //dbg("Merging Both");
            s1 ll = sg[l.lid];
            s1 rr = sg[r.rid];
            sg[s.id] = s1{l.l, r.r, l.val, s.id, l.lid, r.rid};
            if(ll.val > l.val && rr.val > l.val)
                bs[r.r - l.l].pb(sg[s.id]);
            sg[l.lid].rid  = s.id;
            sg[r.rid].lid = s.id;
        }
    }
    cout << cost << ln;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while(t--) solve();

}