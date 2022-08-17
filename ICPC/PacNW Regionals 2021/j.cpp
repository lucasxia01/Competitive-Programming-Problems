//By TheOneYouWant
#pragma GCC optimize ("-O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
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

int read(){
    int xx=0,ff=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')ff=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){xx=(xx<<3)+(xx<<1)+ch-'0';ch=getchar();}
    return xx*ff;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int conv(char c){
	if(c == 'F') return 0;
	else return 1;

}

v32 adj[LIM];
bool mark[LIM];

void dfs(int node){
	mark[node] = 1;
	forstl(r, adj[node]){
		if(mark[r]) continue;
		dfs(r);
	}
}

int main(){
	fastio;

	int n, k;

	cin >> n >> k;

	forn(i,n){
		string s;
		cin >> s;
		forn(j,k){
			if(s[k]=='X') continue;
			forsn(l,j+1,k){
				if(s[l]=='X') continue;
				int x = conv(s[j]);
				int y = conv(s[l]);
				int n1 = 2 * j + x;
				int n2 = 2 * l + 1 - y;
				adj[n1].pb(n2);
				n1 = 2 * j + 1 - x;
				n2 = 2 * l + y;
				adj[n2].pb(n1);
			}
		}
	}

	int ans[k] = {0};
	bool done[k] = {0};
	bool can_do = 1;

	forn(i,k){
		if(done[i]) continue;
		// check if 2*i+0 can be taken
		forn(j,2*k) mark[j] = 0;
		dfs(2*i);

		bool pos = 1;
		forn(j,k){
			if((mark[2*j]==1) && (mark[2*j+1]==1)){
				pos = 0;
				break;
			}
			if(done[j]==1){
				if((mark[2*j] == 1) && (ans[j]==1)){
					pos = 0;
					break;
				} 
				else if((mark[2*j+1]==1) && (ans[j]==0)){
					pos = 0;
					break;
				}
			}
		}
		if(pos){
			forn(j,k){
				if(mark[2*j]==1){
					done[j] = 1;
					ans[j] = 0;
				}
				if(mark[2*j+1]==1){
					done[j] = 1;
					ans[j] = 1;
				}
			}
			continue;
		}

		forn(j,2*k) mark[j] = 0;
		dfs(2*i+1);

		pos = 1;
		forn(j,k){
			if((mark[2*j]==1) && (mark[2*j+1]==1)){
				pos = 0;
				break;
			}
			if(done[j]==1){
				if((mark[2*j] == 1) && (ans[j]==1)){
					pos = 0;
					break;
				} 
				else if((mark[2*j+1]==1) && (ans[j]==0)){
					pos = 0;
					break;
				}
			}
		}
		if(pos){
			forn(j,k){
				if(mark[2*j]==1){
					done[j] = 1;
					ans[j] = 0;
				}
				if(mark[2*j+1]==1){
					done[j] = 1;
					ans[j] = 1;
				}
			}
			continue;
		}
		can_do = 0;
		break;
	}

	if(can_do==0){
		cout << -1 << ln;
		return 0;
	}

	forn(j,k){
		if(ans[j]==0) cout << 'F';
		else cout << 'T';
	}
	cout << ln;

	return 0;
}