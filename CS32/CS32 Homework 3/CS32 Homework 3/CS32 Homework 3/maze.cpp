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
    int dx[4] = {1, 0, -1, 0}, dy[4] = {0, -1, 0, 1};
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
