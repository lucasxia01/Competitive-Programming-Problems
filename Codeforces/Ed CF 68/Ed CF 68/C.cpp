#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> q;
    string s, t, p;
    for (int i = 0; i < q; i++) {
        cin >> s >> t >> p;
        int k = 0; // points to s
        int letters[26] = {};
        for (int j = 0; j < t.length(); j++) {
            if (k != s.length() && s[k] == t[j]) k++;
            else {
                letters[t[j] - 'a']++;
            }
        }
        if (k != s.length()) {
            cout << "NO" << endl;
            continue;
        }
        int letters_p[26] = {};
        for (int j = 0; j < p.length(); j++) {
            letters_p[p[j] - 'a']++;
        }
        int j;
        for (j = 0; j < 26; j++) {
            if (letters[j] > letters_p[j]) break;
        }
        if (j == 26) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
