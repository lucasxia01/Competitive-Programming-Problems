#include <iostream>
#include <string>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int t, n;
    cin >> t;
    string s;
    while (t--) {
        cin >> n >> s;
        string a = "1", b = "1";
        int flag = 0; // marks if a is bigger than b, set it when a must become larger
        for (int i = 1; i < n; i++) {
            if (s[i] == '0') {
                a += '0';
                b += '0';
            } else if (s[i] == '1') {
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
        cout << a << '\n' << b << endl;
    }
    return 0;
}
