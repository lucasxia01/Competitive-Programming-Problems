#include <iostream>
#include <set>
#include <utility>
#include <cmath>
#include <cstdlib>
#include <string>

#define rep(i,n) for (int i = 0; i < n; i++)
#define ll long long
using namespace std;

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    string s;
    cin >> t;
   
    rep(j, t) {
        cin >> s;
        int count[3] = {0, 0, 0}; // U, l, numb3r
        int pos[3];
        rep(i, s.length()) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                count[0]++;
                pos[0] = i;
            } else if (s[i] >= 'a' && s[i] <= 'z') {
                count[1]++;
                pos[1] = i;
            } else if (s[i] >= '0' && s[i] <= '9') {
                count[2]++;
                pos[2] = i;
            }
        }
        if (count[0] == 0) {
            if (count[1] > 1) {
                s[pos[1]] = 'A';
                count[1]--;
                pos[1]--;
            } else {
                s[pos[2]] = 'A';
                count[2]--;
                pos[2]--;
            }
        }
        if (count[1] == 0) {
            if (count[0] > 1) {
                s[pos[0]] = 'a';
                count[0]--;
                pos[0]--;
            } else {
                s[pos[2]] = 'a';
                count[2]--;
                pos[2]--;
                
            }
        }
        if (count[2] == 0) {
            if (count[0] > 1) {
                s[pos[0]] = '0';
                count[0]--;
            } else {
                s[pos[1]] = '0';
                count[1]--;
            }
        }
        cout << s << endl;
    }
    
    return 0;
}
