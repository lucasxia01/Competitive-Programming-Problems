#include <iostream>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

typedef long long ll;
#define F0R(i, n) for (int i = 0; i < n; i++)
#define sz(x) (int)x.size()

const int MX = 2e5+5;
const ll INF = 1LL<<50;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, k; ll d;
    cin >> n >> k >> d;
    int s[61] = {};
    int x;
    F0R(i, k) {
        cin >> x;
        s[--x] = 1;
        d -= 1LL<<x;
    }
    if (d&1) {
        cout << 0 << endl;
        return 0;
    }
    d/=2;
    F0R(i, 60) {
        if (d&(1LL<<i) && s[i]) {
            cout << 0 << endl;
            return 0;
        }
    }
    cout << (1LL<<k) << endl;
    
    return 0;
}
