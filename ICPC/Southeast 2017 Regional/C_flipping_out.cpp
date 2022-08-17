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

// from @jacob.b.zhang :)
template<typename T> class SafeVector : public vector<T> {
    public:
        using vector<T>::vector;
 
        typename vector<T>::reference operator[](size_t n) {
            return vector<T>::at(n);
        }
 
        typename vector<T>::const_reference operator[](size_t n) const {
            return vector<T>::at(n);
        }
};

#ifdef DBG
#define dbg(desc, ...) cerr << '(' << desc << "): "; dbg_out(__VA_ARGS__);
#define vector SafeVector
#else
#define dbg(...)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MX = 1<<20;

struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		F0R(i,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			F0R(i, alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		F0R(i,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};

struct SuffixArray {
    string s;
    int order[MX];
    vi lcp;
    SuffixArray(string t) {
        s = t;
        s += ' ';
        int n = (int) s.length();
        vector<pi> v;
        F0R(i, n) v.pb({s[i], i});
        sort(all(v));
        F0R(i, n) order[i] = v[i].s;
        int eqClass[n]; eqClass[order[0]] = 0;
        FOR(i, 1, n-1) eqClass[order[i]] = eqClass[order[i-1]] + (v[i].f != v[i-1].f);
        int sz = 1;
        while (sz < n) {
            vector<pair<pi, int> > w;
            F0R(i, n) w.pb({{eqClass[(order[i]+n-sz)%n], eqClass[order[i]]}, (order[i]+n-sz)%n});
            count_sort(w);
            F0R(i, n) order[i] = w[i].s;
            eqClass[order[0]] = 0;
            FOR(i, 1, n-1) eqClass[order[i]] = eqClass[order[i-1]] + (w[i].f != w[i-1].f);
            sz *= 2;
        }
        
        int k = 0;
        F0R(i, n) lcp.pb(0);
        F0R(i, n-1) {
            int j = eqClass[i]; // rank of ith suffix
            int ii = order[j-1]; // index of suffix that comes before current suffix in ordering
            while (s[ii+k] == s[i+k]) k++;
            lcp[j] = k;
            k = max(k-1, 0);
        }
    }
    
    void count_sort(vector<pair<pi, int> >& w) {
        int n = sz(w);
        int c[n], p[n];
        F0R(i, n) c[i] = p[i] = 0;
        F0R(i, n) c[w[i].f.f]++;
        p[0] = 0;
        FOR(i, 1, n-1) p[i] = p[i-1] + c[i-1];
        vector<pair<pi, int> > w2 = w;
        F0R(i, n) w2[p[w[i].f.f]++] = w[i];
        w = w2;
    }
    
    int find(string t) {
        int lo = 0, hi = (int) s.length();
        int len = (int) t.length();
        while (lo < hi) {
            int mid = (lo+hi)/2;
            int i = 0;
            for (; i < len; i++) {
                if (s[order[mid]+i] < t[i]) lo = mid+1;
                else if (s[order[mid]+i] > t[i]) hi = mid;
                else continue;
                break;
            }
            if (i == len) hi = mid;
        }
        return lo;
    }
    int count(string t) {
        int l = find(t), r = find(t+'}');
        return r-l;
    }
};

const int ALPHABET_SIZE = 26;
 
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};
 
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
 
    pNode->isEndOfWord = false;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
 
    return pNode;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}
 
// Returns true if key presents in trie, else
// false

int u, l;
int bad = 0;
void search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'A';
        if (!pCrawl->children[index])
            return;
 
        pCrawl = pCrawl->children[index];
        if (pCrawl->isEndOfWord && i+1 > l && i+1 <= u) bad++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<string> pats; string t; 
    F0R(i, n-1) {
        cin >> t;
        pats.pb(t);
    }
    cin >> t;
    int m = sz(t);
    AhoCorasick ac(pats);
    vector<vi> V = ac.findAll(pats, t);
    // trav(vv, V) {
    //     trav(u, vv) cout << u << " "; cout << nl;
    // }
    // wrong ones
    set<int> flipped;
    int cnt = 0;
    F0R(i, m) {
        if (cnt%2 == (t[i]=='T')) {
            flipped.insert(m-i);
            cnt++;
        }
        cnt += sz(V[i]);
    }
    // cout << "flipped" << nl;
    // trav(f, flipped) {
    //     cout << f << nl;
    // }
    if (sz(flipped) == 0) {
        cout << -1 << nl;
        return 0;
    }
    reverse(all(t));
    SuffixArray sa(t);
    // cout << t << nl;
    // F0R(i, m+1) cout << sa.order[i] << " "; cout << nl;
    // F0R(i, m) cout << " " << sa.lcp[i+1]; cout << nl;
    sa.lcp.pb(0);
    cnt = 0;
    int ans = INF;
    int lower = 0;
    FOR(i, 0, m) {
        if (flipped.find(sa.order[i]) != flipped.end()) { // consecutive
            if (cnt+1 != sz(flipped)) ckmin(ans, sa.lcp[i+1]);
            ckmin(ans, m-sa.order[i]);
            if (cnt == 0) ckmax(lower, sa.lcp[i]);
            cnt++;
            if (cnt == sz(flipped)) {
                if (i < m && sa.order[i+1] == 0) ckmax(lower, min(sa.lcp[i+1], sa.lcp[i+2]));
                else ckmax(lower, sa.lcp[i+1]);
            }
        } else {
            if (cnt > 0 && cnt < sz(flipped)) { // answer is 0
                cout << 0 << nl;
                return 0;
            }
        }
    }
    dbg(lower, ans);
    if (lower >= ans) {
        cout << 0 << nl;
        return 0;
    }
    u = ans, l = lower;
    struct TrieNode *root = getNode();
    F0R(i, n-1) {
        reverse(all(pats[i]));
        insert(root, pats[i]);
    }
    string s = t.substr(*flipped.begin());
    // cout << s << nl;
    search(root, s);

    cout << ans-lower-bad << nl;
    return 0;
}
