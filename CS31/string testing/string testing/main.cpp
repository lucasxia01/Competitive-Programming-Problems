//
//  main.cpp
//  string testing
//
//  Created by Lucas Xia on 11/5/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;
const int MAX_WORD_LENGTH = 6;
int countLength( const char a[ ] [MAX_WORD_LENGTH+1], int n, int targetLength);

int main(int argc, const char * argv[]) {
    char s[10] = "hi";
    char t[100] = "no";
    strcat(t,  "hi");
    cout << t << endl;
    // strlen, strcpy, strcat, strcmp
    for (int i = 0; i < strlen(s); i++) {
        cout << i << " " << s[i] << endl;
    }
    const int MAX_PETS = 7;
       //7-1 for the \0
    char pets[7][MAX_WORD_LENGTH + 1] = {
        "cat", "mouse", "eel", "ferret", "horse", "reilly", ""
    };
    cout << strlen(pets[0]) << "HIHIH" << endl;
    cout << strlen(pets[1]) << "HIHIH" << endl;
    for (int i = 0; i < 7; i++) {
        cout << pets[i] << endl;
    }
    cout << countLength(pets, MAX_PETS, 5);
    double p = 5;
    double * q = &p;
    cout << (q) << endl;
    double x = 4;
    q = &x;
    cout << (q) << endl;
    cout << (&p) << endl;
    return 0;
}
int countLength( const char a[ ] [MAX_WORD_LENGTH+1], int n, int targetLength)
{
    int total=0;
    for (int k=0; k<n; k++)
    {
        cout << a[k] << " " << strlen(a[k]) << endl;
        if (strlen(a[k]) == targetLength)
            total++;
    }
    return total;

}
