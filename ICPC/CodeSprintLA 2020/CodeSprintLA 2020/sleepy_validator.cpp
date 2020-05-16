#include <iostream>
#include "testlib.h"

using namespace std;

const int MOD = 24*60;
const int MX = 1e5;

int main(int argc, char* argv[])
{
    registerValidation(argc, argv);

    int n = inf.readInt(1, MX, "n");
    inf.readEoln();
    for (int i = 0; i < n-1; i++) {
        inf.readInt(0, MOD-1, "t");
        inf.readSpace();
    }
    inf.readInt(0, MOD-1, "t");
    inf.readEoln();
    inf.readEof();
}
