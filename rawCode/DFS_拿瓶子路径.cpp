#include <iostream>
#include <vector>
#include <climits> // 包含 INT_MAX

using namespace std;

int dfs(int x, int y, int state, int cost, int n, int c, int d, vector<pair<int, int>>& bottles) {
    // << 为左移动操作，n=3，则为0001左移动1三位变成1000
    // 这行代表拿完了的状态。 n=3则 state = 1000 - 0001 = 0111，三个瓶子都拿了
    if (state == (1 << n) - 1) {
        return cost + abs(x - c) + abs(y - d); // 所有瓶子都被捡起后返回最终代价
    }

    int min_cost = INT_MAX;

    for (int i = 0; i < n; i++) {
        // 按位与操作 0110 & 0001 = 0000，表示为假，！以后为真，则是原来的状态没有捡起来 0001 瓶子
        if (!(state & (1 << i))) { // 如果第 i 个瓶子还没有被捡起
            int nx = bottles[i].first;
            int ny = bottles[i].second;
            
            // 按位或操作 0100 | 0010 = 0110
            int new_state = state | (1 << i); // 捡起第 i 个瓶子
            int new_cost = dfs(nx, ny, new_state, cost + abs(nx - x) + abs(ny - y), n, c, d, bottles);
            min_cost = min(min_cost, new_cost);
        }
    }

    return min_cost;
}

int main() {
    int a, b, c, d, n;
    cin >> a >> b >> c >> d;
    cin >> n;

    vector<pair<int, int>> bottles(n);
    for (int i = 0; i < n; i++) {
        cin >> bottles[i].first >> bottles[i].second;
    }

    int result = dfs(a, b, 0, 0, n, c, d, bottles);
    cout << result << endl;

    return 0;
}

