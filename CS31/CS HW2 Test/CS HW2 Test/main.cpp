#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    switch (n) {
        case 281:
            cout << "bigamy";
        case 321:
        case 322:
            cout << "selling illegal lottery tickets";
            break;case 383:
            cout << "selling rancid butter";
        case 598:
            cout << "injuring a bird in a public cemetery";
        default:
            cout << "some other crime";
    }
}
