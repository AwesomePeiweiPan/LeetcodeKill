/*
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' 组成，捕获 所有 被围绕的区域：

连接：一个单元格与水平或垂直方向上相邻的单元格连接。
区域：连接所有 'O' 的单元格来形成一个区域。
围绕：如果您可以用 'X' 单元格 连接这个区域，并且区域中没有任何单元格位于 board 边缘，则该区域被 'X' 单元格围绕。
通过将输入矩阵 board 中的所有 'O' 替换为 'X' 来 捕获被围绕的区域。

 

示例 1：

输入：board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]

输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]

*/

/*
这里不像岛屿数量，按照之前的逻辑，在遇到四个O的时候，由于边界没有把它们变成X，因此会出现死循环的情况
这里使用反向的DFS，从边界的O开始延续变成X，然后再去做转换
*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;

        int rows = board.size();
        int cols = board[0].size();

        // 从边界出发，将与边界相连的所有'O'标记为'#'
        for (int i = 0; i < rows; ++i) {
            if (board[i][0] == 'O') dfs(board, i, 0); // 左边界
            if (board[i][cols - 1] == 'O') dfs(board, i, cols - 1); // 右边界
        }
        for (int j = 0; j < cols; ++j) {
            if (board[0][j] == 'O') dfs(board, 0, j); // 上边界
            if (board[rows - 1][j] == 'O') dfs(board, rows - 1, j); // 下边界
        }

        // 遍历整个网格，替换所有的'O'为'X'，并将'#'还原为'O'
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == '#') {
                    board[i][j] = 'O';
                }
            }
        }
    }

private:
    void dfs(vector<vector<char>>& board, int i, int j) {
        int rows = board.size();
        int cols = board[0].size();

        // 边界检查和状态检查
        if (i < 0 || i >= rows || j < 0 || j >= cols || board[i][j] != 'O') {
            return;
        }

        // 将当前的'O'标记为'#'，表示已经访问过
        board[i][j] = '#';

        // 向四个方向进行DFS
        dfs(board, i + 1, j); // 下
        dfs(board, i - 1, j); // 上
        dfs(board, i, j + 1); // 右
        dfs(board, i, j - 1); // 左
    }
};