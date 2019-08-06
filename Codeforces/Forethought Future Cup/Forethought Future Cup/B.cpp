#include <iostream>
using namespace std;

int main() {
    string t;
    cin >> t;
    int a = 0;
    for (int i = 0; i < t.length(); i++) {
        if (t[i] == 'a') a++;
    }
    int l = (t.length() - a) / 2;
    string s2 = t.substr(t.length() - l, t.length());
    string t2 = "";
    for (int i = 0; i < t.length(); i++) {
        if (t[i] != 'a') t2 += t[i];
        if (i >= a + l && t[i] == 'a') l = -1;
    }
    if (t2.length() != 2 * l || t2.substr(0, l) != t2.substr(l, 2*l)) {
        cout << ":(" << endl;
    } else cout << t.substr(0, t.length() - l) << endl;
}
