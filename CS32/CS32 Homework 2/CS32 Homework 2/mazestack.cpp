//#include <iostream>
//#include <stack>
//
//using namespace std;
//
//const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
//    stack<Coord> s;
//    s.push(Coord(sr, sc));
//    while (!s.empty()) {
//        Coord cur(s.top().r(), s.top().c());
//        //cout << "(" << cur.r() << ", " << cur.c() << "), ";
//        s.pop();
//        maze[cur.r()][cur.c()] = 'X';
//        if (cur.r() == er && cur.c() == ec) return true;
//        for (int i = 0; i < 4; i++) {
//            int xCur = cur.r() + dx[i], yCur = cur.c() + dy[i];
//            if (xCur >= 0 && xCur < nRows && yCur >= 0 && yCur < nCols && maze[xCur][yCur] == '.') {
//                s.push(Coord(xCur, yCur));
//            }
//        }
//    }
//    return false;
//}
//
//int main() {
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X....X...X",
//        "X.XX.XX..X",
//        "XXX....X.X",
//        "X.XXX.XXXX",
//        "X.X...X..X",
//        "X...X.X..X",
//        "XXXXX.X.XX",
//        "X........X",
//        "XXXXXXXXXX"
//    };
//    
//    if (pathExists(maze, 10,10, 3,5, 8,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//    return 0;
//}
