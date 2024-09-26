#include <iostream>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
#define MAX_N 1000011
#define INF (1<<29) + 123

using namespace std;

ll BIT[MAX_N];

int query(int i) {
    int sum = 0;
    i++;
    while (i > 0) {
        sum += BIT[i];
        i -= (i&-i);
    }
    return sum;
}
void update(int i, int n, ll v) {
    i++;
    while (i <= n) {
        BIT[i] += v;
        i += (i&-i);
    }
}
int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n;
    int count = 0;
    int a[n];
    rep(i, n) {
        cin >> a[i];
        update(i, n, a[i]);
    }
    rep(i, n + 1) cout << BIT[i] << " "; cout << endl;
    cin >> q;
    char c;
    int id;
    ll val;
    rep(i, q) {
        cin >> c;
        if (c == 'q') {
            cin >> id;
            cout << query(id) << endl;
        } else if (c == 'u') {
            cin >> id >> val;
            update(id, n, val);
            rep(i, n + 1) cout << BIT[i] << " "; cout << endl;
        } else {
            i--;
        }
    }
    
    cout << count << endl;
    return 0;
}
