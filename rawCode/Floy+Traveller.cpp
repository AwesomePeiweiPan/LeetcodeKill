/*
n 个地点，从第一个点开始，n-1条路径，求不返回起点的最短路径
输入
5
5 3 60
4 3 63
3 1 14
1 2 97

输出
371

*/


#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int INF = 1e9;
int n = 5; // 地点的数量
vector<vector<int>> dist; // 存储任意两点之间的最短距离
map<set<int>, vector<int>> dp; // 动态规划数组

void floydWarshall() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    // 初始化距离矩阵
    dist = vector<vector<int>>(n, vector<int>(n, INF));
    
    // 设定直接连接的节点距离
    dist[4][2] = 60; // 节点 5 和 节点 3 之间的距离为 60
    dist[2][4] = 60; // 对称距离
    dist[3][2] = 63; // 节点 4 和 节点 3 之间的距离为 63
    dist[2][3] = 63; // 对称距离
    dist[2][0] = 14; // 节点 3 和 节点 1 之间的距离为 14
    dist[0][2] = 14; // 对称距离
    dist[0][1] = 97; // 节点 1 和 节点 2 之间的距离为 97
    dist[1][0] = 97; // 对称距离

    // 自己到自己的距离为0
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }

    // 运行Floyd-Warshall算法，计算任意两点之间的最短路径
    floydWarshall();

    // 初始化动态规划表
    set<int> startState = {0};
    dp[startState] = vector<int>(n, INF);
    dp[startState][0] = 0; // 从节点1出发

    // 动态规划求解
    for (auto &S : dp) {
        set<int> currentSet = S.first;
        for (int i = 0; i < n; ++i) {
            if (currentSet.find(i) == currentSet.end()) continue; // 节点 i 未被访问
            for (int j = 0; j < n; ++j) {
                if (currentSet.find(j) != currentSet.end()) continue; // 节点 j 已被访问
                set<int> nextSet = currentSet;
                nextSet.insert(j);
                int newDist = dp[currentSet][i] + dist[i][j];
                if (dp.find(nextSet) == dp.end()) {
                    dp[nextSet] = vector<int>(n, INF);
                }
                if (newDist < dp[nextSet][j]) {
                    dp[nextSet][j] = newDist;
                }
            }
        }
    }

    // 计算最短路径长度
    int result = INF;
    set<int> finalState;
    for (int i = 0; i < n; ++i) {
        finalState.insert(i);
    }

    for (int i = 0; i < n; ++i) {
        if (dp[finalState][i] < result) {
            result = dp[finalState][i];
        }
    }

    // 输出最短路径长度
    cout << "最短路径长度: " << result << endl;

    return 0;
}