#pragma GCC optimize("-O2")

#include<bits/stdc++.h>
#include <bits/extc++.h> /** keep-include */

using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

#define pb push_back
#define mp make_pair
#define fi first
#define se second
//#define f first
//#define s second

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
const ll inf = ll(1e18)+10;
const ld eps = 1e-8;

typedef pair<int,int> p32;
typedef vector<int> v32;
typedef pair<int,int> pii;
typedef vector<int> vi;

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
using namespace __gnu_pbds;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
};


typedef Point<ll> P;
vi nxt;
vector <pair <P, P>> v;
ll x, fx;

double query(int a, ll x) {
    double la = double(x - v[a].fi.x)/(v[a].se.x - v[a].fi.x);
    if(la < -eps || la > 1+eps)
        return -1e9;
    return v[a].fi.y*(1 - la) + v[a].se.y*la;
}

struct cmp {
    bool operator()(const int &a, const int &b) const {
        return query(a, x) < query(b, x);
    }
};

P bottom(int i) {
    if(v[i].fi.y < v[i].se.y)
        return v[i].fi;
    return v[i].se;
}

vector <pair <P, pii>> evs;
set <int, cmp> s;

bool cmp2(pair <P, pii> a, pair <P, pii> b) {
    if(a.fi == b.fi)
        return a.se < b.se;
    if(a.fi.x != b.fi.x)
        return a.fi.x < b.fi.x;
    if(a.se.fi != b.se.fi)
        return a.se.fi < b.se.fi;
    if(a.se.fi == 1)
        return a.fi.y < b.fi.y;
    else 
        return a.fi.y > b.fi.y;
}


int main() {
    #ifdef LOCAL
    freopen("stuff.in","r",stdin);
    //freopen("stuff.out","w",stdout);
    #endif
	fastio;
    int n;
    cin >> n;
    nxt.resize(n, -1);
    rep(i, 0, n) {
        P a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        if(a.x > b.x)
            swap(a, b);
        v.push_back({a, b});
        evs.push_back({a, {1, i}});
        evs.push_back({b, {2, i}});
    }
    cin >> fx;
    sort(all(evs), cmp2);
    trav(e, evs) {
        int id = e.se.se;
        x = e.fi.x;
        if(e.se.fi == 1) {
            s.insert(id);
            if(e.fi == bottom(id)) {
                auto it = s.find(id);
                if(it != s.begin()) {
                    --it;
                    nxt[id] = (*it); 
                }
            }
        } else {
            if(e.fi == bottom(id)) {
                auto it = s.find(id);
                if(it != s.begin()) {
                    --it;
                    nxt[id] = (*it); 
                }
            }
            s.erase(id);
        }
    }

    int top = 0;
    rep(i, 0, n)
        if(query(i, fx) > query(top, fx))
            top = i;
   // cout << nxt << endl;
    while(nxt[top] != -1)
        top = nxt[top];
    
    cout << bottom(top).x << ln;



    
    



	return 0;
}