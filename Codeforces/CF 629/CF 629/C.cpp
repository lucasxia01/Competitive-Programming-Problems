#include <iostream>
#include <string>
using namespace std;

#define F0R(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i <= b; i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, n;
    cin >> t;
    string x;
    while (t--) {
        cin >> n >> x;
        string a = "1", b = "1";
        int flag = 0; // marks if a is bigger than b, set it when a must become larger
        FOR(i, 1, n-1) {
            if (x[i] == '0') {
                a += '0';
                b += '0';
            } else if (x[i] == '1') {
                if (flag == 1) {
                    b += '1';
                    a += '0';
                } else if (flag == 0) {
                    a += '1';
                    b += '0';
                    flag = 1;
                }
            } else {
                if (flag == 1) {
                    b += '2';
                    a += '0';
                } else if (flag == 0) {
                    a += '1';
                    b += '1';
                }
            }
        }
        cout << a << endl << b << endl;
    }
    return 0;
}
