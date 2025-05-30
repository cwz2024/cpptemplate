#include <bits/stdc++.h>
using namespace std;

// 异或线性方程组
void gause(vector<vector<int>> &mat, int x, int y)
{
    if (x >= int(mat.size()) || y >= int(mat[0].size()))
        return;
    if (mat[x][y] == 0)
    {
        int pos = -1;
        for (int i = x; i < int(mat.size()); i++)
        {
            if (mat[i][y] != 0)
            {
                pos = i;
                break;
            }
        }
        if (pos == -1)
        {
            gause(mat, x, y + 1);
            return;
        }
        swap(mat[x], mat[pos]);
    }
    for (int i = x + 1; i < int(mat.size()); i++)
    {
        if (mat[i][y] == 0)
            continue;
        for (int j = y; j < int(mat[0].size()); j++)
            mat[i][j] ^= mat[x][j];
    }
    gause(mat, x + 1, y + 1);
}