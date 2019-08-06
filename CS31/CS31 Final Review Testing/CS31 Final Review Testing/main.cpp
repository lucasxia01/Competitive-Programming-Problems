#include <iostream>
using namespace std;

//This function takes as input a pointer to the first element
//of a c-string and a pointer to the last element of a c-string
//(including 0 byte) and outputs a new c-string that reverses
//the order of characters in the original string

char* reverseString(char* first, char* last)
{
    char *newString = new char[last-first+1];
    int i = 0;
    last = last - 1;
    while (last!=first)
    {
        newString[i]=*last;
        last = last - 1;
        i++;
    }
    newString[i]=*last;
    newString[i+1]=0;
    return newString;
}

//This function takes as input a c-string containing a number and
//the number of characters in the array (not including 0 byte)
//It outputs an integer representation of that number.
int convertStringToInt(char number[], int len)
{
    int rtrn = 0;
    int multiplier=1;
    for (int i = len-1; i >= 0; i--)
    {
        rtrn+=(number[i]-'0')*multiplier;
        multiplier*=10;
    }
    return rtrn;
}
void f2(int k, int *p2) {
    p2 = p2 - 2;
    *p2 = k - 5;
}
int* f1(int *p1) {
    f2(*p1, p1);
    return p1 - 2;
}
void f() {
    int zorn[] = {19, 14, 18, 12, 10};
    cin >> zorn[4];
    int *p = &zorn[3];
    cout << (*p) + 1 << endl;
    cout << *(p + 1) << endl;
    p = f1(zorn + 2);
    p[3] = 9;
    for (int i = 0; i < 5; i++)
        cout << zorn[i] << endl;
}

//Write very basic test code to test your functions
int main()
{
    char * first;
    char * last;
    
    char str[6]="12345";
    
    first = str;
    last = str+5;
    
    cout << reverseString(first, last) << endl;
    
    cout << convertStringToInt(str, 5)+1 << endl;
    f();
    return 0;
}
