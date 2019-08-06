//
//  main.cpp
//  ptrtest
//
//  Created by Lucas Xia on 11/20/18.
//  Copyright © 2018 Lucas Xia. All rights reserved.
//

#include <iostream>
using namespace std;
int* maxwell(int* a, int* b)
{
    if (*a > *b)
        return a;
    else
        return b;
}

void swap1(int* a, int* b)
{
    int* temp = a;
    a = b;
    b = temp;
}

void swap2(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void removeS(char * p) {
    char * s = p;
    for (; *p != 0; p++) {
        if (*p != 's' && *p != 'S') {
            *s = *p;
            s++;
        }
    }
    *s = 0;
}
int main()
{
    int array[6] = { 5, 3, 4, 17, 22, 19 };
    
    int* ptr = maxwell(array, &array[2]);
    *ptr = -1; //{ -1, 3, 4, 17, 22, 19 }
    ptr += 2;
    ptr[1] = 9; // { -1, 3, 4, 9, 22, 19 }
    *(array+1) = 79; // { -1, 79, 4, 9, 22, 19 }
    
    cout << &array[5] - ptr << endl; // 3
    
    swap1(&array[0], &array[1]);
    swap2(array, &array[2]);
    
    for (int i = 0; i < 6; i++)
        cout << array[i] << endl; // { 4, 79, -1, 9, 22, 19 }
    char msg[50] = "She'll be a massless princess.";
    removeS(msg);
    cout << msg;  // prints   he'll be a male prince.
}
