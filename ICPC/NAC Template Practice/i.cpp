#pragma GCC optimize("-O2")

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define f first
#define s second

#define ins insert
#define lb lower_bound
#define ub upper_bound

#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()

#define forstl(i,v) for(auto & i : v)
#define forn(i,e) for(int i = 0; i<e; i++)
#define forsn(i,s,e) for(int i=s;i<e;i++)

#define F0R(i,n) for(int i = 0; i < n; i++)
#define FOR(i,a,b) for(int i=a; i <= b; i++)
#define F0Rd(i,a) for(int i=(a)-1; i >=0; i--)
#define FORd(i,a,b) for(int i = (b); i >= (a); i--)

#define trav(a,x) for(auto & a :x)

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define ln '\n'
#define nl '\n'

typedef long long ll;
typedef long double ld;

typedef pair<int,int> p32;
typedef vector<int> v32;
typedef pair<int,int> pi;
typedef vector<int> vi;
typedef pair<ll, ll> pl;

const ll MOD = 1e9+7;

template<typename T> bool ckmin(T & a, const T & b){
	return a > b ? a=b, 1 : 0;
}
template<typename T> bool ckmax(T & a, const T & b){
	return b > a ? a=b, 1 : 0;
}

template<typename T1, typename T2>
ostream& operator <<(ostream &c, pair<T1, T2> &v){
	c << "(" << v.fi << "," <<v.se <<")"; return c;
}

template<template<class...> class TT, class ...T>
ostream& operator<<(ostream&out, TT<T...>&c){
	out << "{ ";
	forstl(x,c) out<<x<<" ";
	out<<"}"; return out;
}

// template<typename Head, typename... Tail> void dbg_out (Head H, )

struct P {
	int x, y, s, i;
	bool operator<(const P& o) const {
		return (tie(x, s, y, i) < tie(o.x, o.s, o.y, o.i));
	}
};

vector<P> v;
ll X;

vector<pair<pi, pi> > segs;

pl find_y(int i) {
	pair<pl,pl> seg = segs[i];
	ll temp = (X-seg.f.f)*seg.s.s + ((ll)seg.s.f-X)*seg.f.s;
	pl ans = {temp, seg.s.f-seg.f.f};
	return ans;
}

vi toposort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	trav(li,gr) for(int x: li) indeg[x]++;
	queue<int> q;
	rep(i, 0, sz(gr)) if(indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front();
		ret.pb(i);
		q.pop();
		for (int x : gr[i])
			if(--indeg[x] == 0) q.push(x);
	}
	return ret;
}

vector<vi> gr;

signed main(){
	fastio;
	int n; cin >> n;
	vector<pair<P, P> > W;
	F0R(i, n) {
		int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
		if (x1 > x2) {
			swap(x1, x2);
			swap(y1, y2);
		}
		segs.pb({{x1, y1}, {x2, y2}});
		P temp = {x1, y1, 0, i};
		v.pb(temp);
		P temp2 = {x2, y2, 1, i};
		v.pb(temp2);
		W.pb({temp, temp2});
	}
	sort(all(v));
	auto cmp = [](P a, P b) {
		pl y1 = find_y(a.i);
		pl y2 = find_y(b.i);
		return (y1.f*y2.s < y2.f*y1.s);
	};
	set<P, decltype(cmp)> s(cmp);
	gr.resize(n);
	trav(u, v) {
		X = u.x;
		if (u.s == 1) {
			// delete it 
			auto it = s.lower_bound(u);
			while (it->i != u.i) it++;
			// while(s.find(u) == s.end());
			// if (s.find(u)->i != u.i) {
			// 	P e = *s.find(u);
			// 	int idx = e.i;
			// 	if (segs[idx].f.f <= X && X <= segs[idx].s.f) {
			// 		pl y2 = find_y(e.i);
			// 		if (u.y*y2.s == y2.f) {
			// 			cout << -1111111 << nl;
			// 			return 0;
			// 		} else assert(0);
			// 	} else assert(0);
			// }
			s.erase(it);
		} else {
			auto it = s.lower_bound(u);
			if (it != s.end()) {
				gr[it->i].pb(u.i);
			}
			if (it != s.begin()) {
				--it;
				gr[u.i].pb(it->i);
			}
			s.insert(u);
		}
		// cout << "x " << X << nl;
		// trav(ss, s) {
		// 	cout << ss.i << " ";
		// } cout << nl;
		
	}
	int x; cin >> x;
	vi order = toposort(gr);
	// trav(o, order) cout << o << " "; cout << nl;
	trav(o, order) {
		if (x >= segs[o].f.f && x <= segs[o].s.f) {
			if (segs[o].f.s < segs[o].s.s) x = segs[o].f.f;
			else x = segs[o].s.f;
		}
		// cerr <<x << nl;;
	}
	cout << x << nl;
	return 0;
}