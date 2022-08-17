#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX_LEVELS = 900;
const int MAX_WEIGHT = 1048576;

int main()
{
//    int n;
//    cin >> n;
//    int seed;
//    cin >> seed;
//    srand(seed);
//
//    for (int i = 0; i < n; i++)
//    {
//        int l = rand() % MAX_LEVELS + 100;
//        cout << l << endl;
//        for (int j = 1; j <= l; j++)
//        {
//            for (int k = 0; k < j; k++)
//                cout << rand() % MAX_WEIGHT + 1 << " ";
//        }
//        cout << endl;
//    }
    cout << 1 << endl;
    cout << 5 << endl;
    cout << 1 << endl;
    for (int j = 1; j <= 4; j++)
    {
        for (int k = 0; k <= j; k++)
            cout << (1 << 20) << " ";
        cout << endl;
    }
}
