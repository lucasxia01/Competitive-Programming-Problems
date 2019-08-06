#include <iostream>
#include <cassert>
#include <stack>

using namespace std;

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) return true;
    maze[sr][sc] = 'X';
    bool ans = false;
    for (int i = 0; i < 4; i++) {
        int xCur = sr + dx[i], yCur = sc + dy[i];
            if (xCur >= 0 && xCur < nRows && yCur >= 0 && yCur < nCols && maze[xCur][yCur] == '.')
            ans = ans || pathExists(maze, nRows, nCols, xCur, yCur, er, ec);
    }
    return ans;
}

int main() {
    string maze1[10] = {
        "XXXXXXXXXX",
        "X...X....X",
        "XX.X..XX.X",
        "XX...X...X",
        "X.X.X..XXX",
        "X...X.X.XX",
        "X.X.X....X",
        "XXX.X.XX.X",
        "X...X..X.X",
        "XXXXXXXXXX",
    };
    
    string maze2[10] = {
        "XXXXXXXXXX",
        "X...X....X",
        "XX.X..XX.X",
        "XX...X...X",
        "X.X.X..XXX",
        "X...X.X.XX",
        "X.X.X....X",
        "XXX.X.XXXX",
        "X...X..X.X",
        "XXXXXXXXXX",
    };
    
    string maze3[10] = {
        "XXXXXXXXXX",
        "XXXXXXX..X",
        "XX.......X",
        "X..X....XX",
        "X..X..XXXX",
        "X..XXX.X.X",
        "XX...X...X",
        "X....XX..X",
        "XXX.....XX",
        "XXXXXXXXXX",
    };
    
    string maze4[10] = {
        "XXXXXXXXXX",
        "XXXXXXX..X",
        "XX.....X.X",
        "X..X....XX",
        "X..X..XXXX",
        "X..XXX.X.X",
        "XX...X...X",
        "X....XX..X",
        "XXX.....XX",
        "XXXXXXXXXX",
    };
    
    assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
    assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
    assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
    assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));
    cout << "PASSED" << endl;
    return 0;
}
