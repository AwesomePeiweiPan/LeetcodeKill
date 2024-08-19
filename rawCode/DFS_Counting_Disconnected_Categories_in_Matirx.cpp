// 输入一个矩阵，判断 有多少个连通分量，0的不算；和多少特征值数量
// 1 2 0
// 2 0 0
// 0 0 1
// 可以看出这里有两个连通分量，3个特征值数量

// 第一种写法 是否访达和原始数据设定为全局变量，这样不用传递参数更简单
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N, M;
vector<vector<int>> grid;
vector<vector<bool>> visited;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

void dfs(int x, int y) {
    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny] && grid[nx][ny] != 0) {
            dfs(nx, ny);
        }
    }
}

int main() {
    cin >> N >> M;
    grid.resize(N, vector<int>(M));
    visited.resize(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    int clusterCount = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 最重要的地方
            if (!visited[i][j] && grid[i][j] != 0) {
                dfs(i, j);
                clusterCount++;
            }
        }
    }

    cout << clusterCount << endl;

    return 0;
}


// 第二种写法，是否访达和原始数据设定为局部变量，这样需要传递参数，更加规范
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int N, M;

void dfs(int x, int y, vector<vector<int>>& matrix, vector<vector<bool>>& visited) {
    
    visited[x][y] = true;

    for (int i = 0; i < 4; ++i) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];
        if (nx >= 0 && nx < N && ny >= 0 && ny < M && !visited[nx][ny]&& matrix[x][y]!=0) {
            dfs(nx, ny, matrix, visited);
        }
    }
}

int main() {
    // 读取行数和列数
    cin >> N >> M;

    // 动态创建矩阵和访问标记矩阵
    vector<vector<int>> matrix(N, vector<int>(M));
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    // 读取矩阵输入
    set<int> unique_features;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i][j];
            unique_features.insert(matrix[i][j]);
        }
    }

    int cluster_count = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!visited[i][j] && matrix[i][j]!=0) {
                // 最重要的地方
                dfs(i, j, matrix, visited);
                cluster_count++;
            }
        }
    }

    // 输出聚类数量和不同特征值的数量
    cout << cluster_count << " " << unique_features.size() << endl;

    return 0;
}

