#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <stack>

#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i <= b; i++)

using namespace std;

int main() {
    int n;
    cin >> n;
    bool vals[n];
    char c;
    F0R(i, n) {
        cin >> c;
        if (c == 'T') vals[i] = 1;
        else vals[i] = 0;
    }
    string t;
    getline(cin, t);
    getline(cin, t);
    stack<bool> s;
    bool a, b, top;
    F0R(i, t.length()) {
        c = t[i];
        if (c >= 'A' && c <= 'Z') s.push(vals[c-'A']);
        else if (c == '+') {
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            s.push(a+b);
        } else if (c == '*') {
            a = s.top();
            s.pop();
            b = s.top();
            s.pop();
            s.push(a*b);
        } else if (c == '-') {
            a = s.top();
            s.pop();
            s.push(true^a);
        }
        top = s.top();
    }
    if (top == 0) cout << 'F' << endl;
    else cout << 'T' << endl;
    return 0;
}
