#include <iostream>
#include <string>
using namespace std;

int main() {
    string s; getline(cin, s);
    bool a = (s.find(":)") != -1);
    bool b = (s.find(":(") != -1);
    if (a&b) cout << "double agent" << endl;
    else if (a) cout << "alive" << endl;
    else if (b) cout << "undead" << endl;
    else cout << "machine" << endl;

}