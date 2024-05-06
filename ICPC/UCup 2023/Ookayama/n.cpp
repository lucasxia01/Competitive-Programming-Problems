#include<bits/stdc++.h>
using namespace std;

#define F0R(i, n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)

typedef vector<int> vi;
typedef pair<int, int> pii;
#define sz(x) (int)(x).size();
typedef long long ll;

ll cc2(ll x) {
    return x * (x-1) / 2;
}

struct RollbackUF {
    vi e; vector<pii> st;
    ll c2 = 0;
    RollbackUF(int n) : e(n, -1) {}
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return sz(st); }
    void rollback(int t) {
        // cout << "UNDOING " << t << '\n';
        for (int i = time(); i --> t;) {
            if (e[st[i].first] < 0) {
                c2 -= cc2(-e[st[i].first]);
            }
            e[st[i].first] = st[i].second;
            if (e[st[i].first] < 0) {
                c2 += cc2(-e[st[i].first]);
            }
        }
        st.resize(t);
    }
    bool join(int a, int b) {
        //cout << "JOINING " << a << ' ' << b << '\n';
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        st.push_back({a, e[a]});
        st.push_back({b, e[b]});
        if (e[a] < 0) c2 -= cc2(-e[a]);
        if (e[b] < 0) c2 -= cc2(-e[b]);
        e[a] += e[b]; e[b] = a;
        if (e[a] < 0) c2 += cc2(-e[a]);
        //cout << c2 << ' ' << e[a] << ' ' << e[b] << '\n';
        return true;
    }
};

struct Edge {
    int a, b, c;
    bool operator<(const Edge &o) const {
        return c < o.c;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    vector<Edge> es;
    for (int i = 0; i < m; i++) {
        Edge e; cin >> e.a >> e.b >> e.c;
        es.push_back(e);
    }
    sort(es.begin(), es.end());

    int q; cin >> q;
    vector<array<int, 2>> qs;
    vector<int> qans(q);
    for (int qi = 0; qi < q; qi++) {
        int x; cin >> x;
        qs.push_back({x, qi});
    }
    sort(qs.begin(), qs.end());

    RollbackUF uf(n+2);
    int stime = uf.time();

    int kbit = (1 << (32-__builtin_clz(k)));
    int kmask = (-1 << (32-__builtin_clz(k)));
    //cout << "KBITMASK " << kbit << ' ' << kmask << '\n';
    
    // organize into groups
    for (int i = 0; i < q;) {
        int topp = qs[i][0] & kmask;
        int dli = i;
        i++;
        while (i < q && (qs[i][0] & kmask) == topp) {
            i++;
        }
        int dri = i;

        // get all edges in that group
        int esi = lower_bound(es.begin(), es.end(), Edge{0, 0, topp}) - es.begin();
        // end exclusive
        int eei = lower_bound(es.begin(), es.end(), Edge{0, 0, topp+kbit}) - es.begin();

        //cout << dli << ' ' << dri << ' ' << esi << ' ' << eei << '\n';

        if (esi >= eei || esi >= m) {
            for (int qi = dli; qi < dri; qi++) {
                qans[qs[qi][1]] = 0;
            }
            continue;
        }

        // ki should be single bit
        function<void(int, int, int, int, int, int)> divconq = [&](int ki, int di, int ql, int qr, int el, int er) {
            if (ql >= qr) return;
            //cout << ki << ' ' << di << ' ' << ql << ' ' << qr << ' ' << el << ' ' << er << '\n';
            if (ki == 0) {
                int rolltime = uf.time();
                for (int ei = el; ei < er; ei++) {
                    uf.join(es[ei].a, es[ei].b);
                }
                for (int qi = ql; qi < qr; qi++) {
                    //cout << "ANSWER " << qs[qi][1] << " " << uf.c2 << '\n';
                    qans[qs[qi][1]] = uf.c2;
                }
                uf.rollback(rolltime);
                return;
            }

            // calculate d split point
            int dsplit = lower_bound(qs.begin() + ql, qs.begin() + qr, array<int, 2>{di + ki + topp, 0}) - qs.begin();

            if ((k & ki) > 0) {
                // cout << "1 case\n";
                // d = 0
                int rolltime = uf.time();
                int nel = el;
                while (nel < er && (es[nel].c & ki) == 0) {
                    uf.join(es[nel].a, es[nel].b);
                    nel++;
                }
                divconq(ki >> 1, di, ql, dsplit, nel, ki > 1 ? er : -1);
                uf.rollback(rolltime);

                // d = 1
                int ner = er;
                while (ner > el && (es[ner-1].c & ki) > 0) {
                    uf.join(es[ner-1].a, es[ner-1].b);
                    ner--;
                }
                divconq(ki >> 1, di + ki, dsplit, qr, ki > 1 ? el : ner, ner);
                uf.rollback(rolltime);
            } else if (ki == 1) {
                divconq(ki >> 1, di, ql, qr, -1, -1);
            } else {
                // cout << "0 case\n";
                // d = 0
                int ner = er;
                while (ner > el && (es[ner-1].c & ki) > 0) {
                    ner--;
                }
                divconq(ki >> 1, di, ql, dsplit, el, ner);

                // d = 1
                int nel = el;
                while (nel < er && (es[nel].c & ki) == 0) {
                    nel++;
                }
                divconq(ki >> 1, di + ki, dsplit, qr, nel, er);
            }
        };

        divconq(kbit >> 1, 0, dli, dri, esi, eei);
        uf.rollback(stime);
    }

    for (int i = 0; i < q; i++) {
        cout << qans[i] << '\n';
    }
}