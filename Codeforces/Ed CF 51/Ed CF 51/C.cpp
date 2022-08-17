#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int a[n];
    int f[101] = {};
    int count = 0;
    int count2 = 0;
    int c = 0;
    int c1 = 0;
    int num = -1;
    rep(i, n) {
        cin >> a[i];
        f[a[i]]++;
    }
    rep(i, 101) {
        if (f[i] == 1) count++;
        else if (f[i] > 2) {
            num = i;
            count2++;
        }
    }
    //cout << count << " " << count2 << endl;
    if (count % 2) {
        if (count2 == 0) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            rep(i, n) {
                if (f[a[i]] == 1) {
                    if (c % 2) cout << 'B';
                    else cout << 'A';
                    c++;
                } else if (a[i] == num) {
                    if (c1) cout << 'A';
                    else cout << 'B';
                    c1++;
                }
                else cout << 'A';
            }
            cout << endl;
        }
    } else {
        cout << "YES" << endl;
        rep(i, n) {
            if (f[a[i]] == 1) {
                if (c % 2) cout << 'B';
                else cout << 'A';
                c++;
            } else cout << 'A';
        }
        cout << endl;
    }
    return 0;
}
