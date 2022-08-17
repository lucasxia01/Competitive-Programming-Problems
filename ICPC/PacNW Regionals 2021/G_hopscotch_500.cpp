//By TheOneYouWant
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
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define int long long
#define all(x) x.begin(),x.end()
#define memreset(a) memset(a,0,sizeof(a))
#define testcase(t) int t;cin>>t;while(t--)
#define forstl(i,v) for(auto &i: v)
#define forn(i,e) for(int i=0;i<e;++i)
#define forsn(i,s,e) for(int i=s;i<e;++i)
#define rforn(i,s) for(int i=s;i>=0;--i)
#define rforsn(i,s,e) for(int i=s;i>=e;--i)
#define bitcount(a) __builtin_popcount(a) // set bits (add ll)
#define ln '\n'
#define getcurrtime() cerr<<"Time = "<<((double)clock()/CLOCKS_PER_SEC)<<endl
#define dbgarr(v,s,e) cerr<<#v<<" = "; forsn(i,s,e) cerr<<v[i]<<", "; cerr<<endl
#define inputfile freopen("input.txt", "r", stdin)
#define outputfile freopen("output.txt", "w", stdout)
#define dbg(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) { cerr<<endl; }
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << "\t"; err(++it, args...);
}
template<typename T1,typename T2>
ostream& operator <<(ostream& c,pair<T1,T2> &v){
	c<<"("<<v.fi<<","<<v.se<<")"; return c;
}
template <template <class...> class TT, class ...T>
ostream& operator<<(ostream& out,TT<T...>& c){
    out<<"{ ";
    forstl(x,c) out<<x<<" ";
    out<<"}"; return out;
}
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> p64;
typedef pair<int,int> p32;
typedef pair<int,p32> p96;
typedef vector<ll> v64;
typedef vector<int> v32; 
typedef vector<v32> vv32;
typedef vector<v64> vv64;
typedef vector<p32> vp32;
typedef vector<p64> vp64;
typedef vector<vp32> vvp32;
typedef map<int,int> m32;
const int LIM=2e5+5,MOD=1e9+7;
const ld EPS = 1e-9;
const ll INF = 1e18;

int read(){
    int xx=0,ff=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ff=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){xx=(xx<<3)+(xx<<1)+ch-'0';ch=getchar();}
    return xx*ff;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll time_till[505][505];
ll a[505][505];
vp32 pts[505*505];
ll col[505], row[505];

signed main(){
	fastio;

	int n, k;
	cin >> n >> k;

	if(k == 1){
		cout << 0 << ln;
		return 0;
	}


	forn(i,n){
		forn(j,n){
			time_till[i][j] = INF;
		}
	}


	forn(i, n){
		forn(j, n){
			cin >> a[i][j];
			if (a[i][j] == k) time_till[i][j] = 0;
		}
	}

	
	forn(i,n){
		forn(j,n){
			pts[a[i][j]].pb({i,j});
		}
	}
	
	for(int st = k; st >= 2; st--){
		// cost to go from k to k-1
		ll c[505], r[505];
		forn(i,n){
			col[i] = row[i] = r[i] = c[i] = INF;
		}
		

		set<int> start_row, start_col;
		set<int> end_row, end_col;

		forstl(r, pts[st]){
			int i, j;
			tie(i, j) = r;
			row[i] = min(row[i], time_till[i][j]);
			col[j] = min(col[j], time_till[i][j]);
			start_row.insert(i);
			start_col.insert(j);
		}

		forstl(r, pts[st-1]){
			int i, j;
			tie(i, j) = r;
			end_row.insert(i);
			end_col.insert(j);
		}

		forstl(k1, start_row){
			forstl(k2, end_row){
				r[k2] = min(r[k2], row[k1] + (k1-k2) * (k1-k2));
			}
		}

		forstl(k1, start_col){
			forstl(k2, end_col){
				c[k2] = min(c[k2], col[k1] + (k1-k2) * (k1-k2));
			}
		}

		forstl(R, pts[st-1]){
			int i, j;
			tie(i, j) = R;
			time_till[i][j] = min(r[i], c[j]);
		}
	}

	ll ans = INF;

	forn(i,n){
		forn(j,n){
			if(a[i][j] == 1){
				ans = min(ans, time_till[i][j]);
			}
		}
	}

	if(ans > 1e17){
		cout << -1 << ln;
	}
	else{
		cout << ans << ln;
	}
	return 0;
}