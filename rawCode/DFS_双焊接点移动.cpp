/*
文远的硬件组购置了一台奇怪的焊接机。这台焊接机可以在一个 n*m 个焊点的电路板上工作，具有两个垂直于电路板的焊接头。它们工作时，可以滴下适量的焊锡到电路板上，来完成焊接工作。

这两个焊接头可以沿着行或列的方向进行移动。奇怪的是，这两个针头必须同时移动，并且方向保持一致。并且任意一个针头都不能离开电路板的状态。它们只能在各自的行和列上移动，且初始时两个针头不能在同一行或列。

你需要回答的问题是，电路板上有多少个焊点是无法被焊接到的。

输入描述
第一行包含一个整数，表示数据组数。
接下来的若干行，每行表示一组数据，包含六个整数 n, m, x1, y1, x2, y2，表示电路板的大小和焊接头的初始位置，具体含义如下：
n: 电路板的行数
m: 电路板的列数
(x1, y1): 第一个焊接头的初始行和列
(x2, y2): 第二个焊接头的初始行和列
保证 两个焊接头的初始位置不在同一行和同一列。


3
4 4 1 1 3 3
4 3 1 1 2 2
3 5 2 4 3 5

8
2
2







*/


#include <queue>
#include <map>
#include <set>
#include <tuple>

using namespace std;

struct State {
    int x1, y1, x2, y2;
};

int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, m;

bool is_valid(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

pair<int, set<pair<int, int>>> count_unreachable_points(int n, int m, int x1, int y1, int x2, int y2) {
    // tuple 类似于 pair 的推广
    map<tuple<int, int, int, int>, bool> visited;
    set<pair<int, int>> visited_points;
    queue<State> q;

    q.push({x1, y1, x2, y2});
    visited[make_tuple(x1, y1, x2, y2)] = true;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        // 记录当前访问的点
        visited_points.insert(make_pair(cur.x1, cur.y1));
        visited_points.insert(make_pair(cur.x2, cur.y2));

        // 尝试移动两个焊接头
        for (int i = 0; i < 4; ++i) {
            int nx1 = cur.x1 + directions[i][0];
            int ny1 = cur.y1 + directions[i][1];
            int nx2 = cur.x2 + directions[i][0];
            int ny2 = cur.y2 + directions[i][1];

            if (is_valid(nx1, ny1) && is_valid(nx2, ny2) && !visited[make_tuple(nx1, ny1, nx2, ny2)]) {
                visited[make_tuple(nx1, ny1, nx2, ny2)] = true;
                q.push({nx1, ny1, nx2, ny2});
            }
        }
    }

    // 计算未访问的点
    set<pair<int, int>> unreachable_points;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (visited_points.find(make_pair(i, j)) == visited_points.end()) {
                unreachable_points.insert(make_pair(i, j));
            }
        }
    }

    int unreachable_count = unreachable_points.size();
    return make_pair(unreachable_count, unreachable_points);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        auto result = count_unreachable_points(n, m, x1, y1, x2, y2);
        int unreachable_points = result.first;
        set<pair<int, int>> unreachable_coordinates = result.second;

        cout << "Number of unreachable points: " << unreachable_points << endl;
        cout << "Coordinates of unreachable points:" << endl;
        for (const auto& point : unreachable_coordinates) {
            cout << "(" << point.first << ", " << point.second << ")" << endl;
        }
    }
    return 0;
}
