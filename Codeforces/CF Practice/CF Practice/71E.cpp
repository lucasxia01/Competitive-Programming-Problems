#include <vector>
#include <stack>
#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <functional>
#include <set>
#include <cstring>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <complex>
#include <iterator>
#include <regex>
#include <fstream>
#include <utility>
#include <unordered_map>

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
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define FORd(i,a,b) for (int i = (b)-1; i >= (a); i--)
#define trav(a, x) for (auto& a : x)

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound

const int MAX_N = 1000011;
const ll INF = (1<<29) + 123;
const ll MOD = 1000000007; // 998244353
const ld PI = 4*atan((ld)1);

#define sz(x) (int)x.size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    unordered_map<string, int> elms({
        { "H", 1 },
        { "He", 2 },
        { "Li", 3 },
        { "Be", 4 },
        { "B", 5 },
        { "C", 6 },
        { "N", 7 },
        { "O", 8 },
        { "F", 9 },
        { "Ne", 10 },
        { "Na", 11 },
        { "Mg", 12 },
        { "Al", 13 },
        { "Si", 14 },
        { "P", 15 },
        { "S", 16 },
        { "Cl", 17 },
        { "Ar", 18 },
        { "K", 19 },
        { "Ca", 20 },
        { "Sc", 21 },
        { "Ti", 22 },
        { "V", 23 },
        { "Cr", 24 },
        { "Mn", 25 },
        { "Fe", 26 },
        { "Co", 27 },
        { "Ni", 28 },
        { "Cu", 29 },
        { "Zn", 30 },
        { "Ga", 31 },
        { "Ge", 32 },
        { "As", 33 },
        { "Se", 34 },
        { "Br", 35 },
        { "Kr", 36 },
        { "Rb", 37 },
        { "Sr", 38 },
        { "Y", 39 },
        { "Zr", 40 },
        { "Nb", 41 },
        { "Mo", 42 },
        { "Tc", 43 },
        { "Ru", 44 },
        { "Rh", 45 },
        { "Pd", 46 },
        { "Ag", 47 },
        { "Cd", 48 },
        { "In", 49 },
        { "Sn", 50 },
        { "Sb", 51 },
        { "Te", 52 },
        { "I", 53 },
        { "Xe", 54 },
        { "Cs", 55 },
        { "Ba", 56 },
        { "La", 57 },
        { "Ce", 58 },
        { "Pr", 59 },
        { "Nd", 60 },
        { "Pm", 61 },
        { "Sm", 62 },
        { "Eu", 63 },
        { "Gd", 64 },
        { "Tb", 65 },
        { "Dy", 66 },
        { "Ho", 67 },
        { "Er", 68 },
        { "Tm", 69 },
        { "Yb", 70 },
        { "Lu", 71 },
        { "Hf", 72 },
        { "Ta", 73 },
        { "W", 74 },
        { "Re", 75 },
        { "Os", 76 },
        { "Ir", 77 },
        { "Pt", 78 },
        { "Au", 79 },
        { "Hg", 80 },
        { "Tl", 81 },
        { "Pb", 82 },
        { "Bi", 83 },
        { "Po", 84 },
        { "At", 85 },
        { "Rn", 86 },
        { "Fr", 87 },
        { "Ra", 88 },
        { "Ac", 89 },
        { "Th", 90 },
        { "Pa", 91 },
        { "U", 92 },
        { "Np", 93 },
        { "Pu", 94 },
        { "Am", 95 },
        { "Cm", 96 },
        { "Bk", 97 },
        { "Cf", 98 },
        { "Es", 99 },
        { "Fm", 100 },
    });
    int n, k;
    cin >> n >> k;
    int a[n];
    string s;
    F0R(i, n) {
        cin >> s;
        a[i] = elms[s];
    }
    int b[k];
    F0R(i, k) {
        cin >> s;
        b[i] = elms[s];
    }
    int dp[k+1][1<<n];
    return 0;
}
 /*
  
  */
