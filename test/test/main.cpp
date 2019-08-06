//
//  main.cpp
//  test
//
//  Created by Lucas Xia on 10/20/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
using namespace std;

string justLetters(string s)
{
    string result = "";
    for (int k = 0; k != s.size(); k++)
    {
        if ( islower(s[k]) )
            result += s[k];
        if ( isupper(s[k]) )
            result += tolower(s[k]);
    }
    return result;
}
void foo(int *a, int &b) {
    *a = b;
}
int main(int argc, const char * argv[]) {
    cout << justLetters("CS 31 began September 28.") << endl;
    int x = 3;
    int y = 4;
    foo(&x, y);
    cout << x << " " << y << endl;
    string s = "hi";
    
    return 0;
}
