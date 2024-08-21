/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3

*/

/*
 与 DFS_计算矩阵的不连通子矩阵不同的是
 这里并没有重新创建一个矩阵 visited 来判断是否已经被访问过了，而是将不为0的值直接设置为0
 同时在增加的时候只需要判断是否当前的grid为1即可，十分巧妙
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        
        int num_islands = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        
        // 遍历整个网格
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // 如果当前位置是陆地，则进行DFS
                if (grid[i][j] == '1') {
                    ++num_islands;  // 发现一个新的岛屿
                    dfs(grid, i, j); // 通过DFS把整个岛屿淹掉
                }
            }
        }
        
        return num_islands;
    }
    
private:
    void dfs(vector<vector<char>>& grid, int i, int j) {
        int rows = grid.size();
        int cols = grid[0].size();
        
        // 边界检查
        if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] == '0') {
            return;
        }
        
        // 将当前的陆地标记为水
        grid[i][j] = '0';
        
        // 向四个方向进行DFS
        dfs(grid, i + 1, j); // 下
        dfs(grid, i - 1, j); // 上
        dfs(grid, i, j + 1); // 右
        dfs(grid, i, j - 1); // 左
    }
};
