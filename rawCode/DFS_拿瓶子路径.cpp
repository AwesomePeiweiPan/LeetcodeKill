#include <iostream>
#include <vector>
#include <climits> // 包含 INT_MAX

using namespace std;

int dfs(int x, int y, int state, int cost, int n, int c, int d, vector<pair<int, int>>& bottles) {
    // 递归终止条件：所有瓶子都被捡起后返回最终代价
    // (1 << n) - 1 计算解释：左移操作用于生成一个所有瓶子都捡起的状态。
    // 例如，如果 n = 3，则 1 << 3 = 1000（二进制），再减 1 得到 0111，表示三个瓶子都捡起的状态。
    if (state == (1 << n) - 1) {
        return cost; // 所有瓶子都被捡起后，无需再返回目标位置
    }

    int min_cost = INT_MAX;

    for (int i = 0; i < n; i++) {
        // 使用按位与操作符 '&' 检查当前状态是否包含第 i 个瓶子。
        // 例如，state = 0110 & (1 << 1) 结果为 0010，即第 1 个瓶子已被捡起。
        // (!(state & (1 << i))) 结果为 true 表示当前状态没有捡起第 i 个瓶子。
        if (!(state & (1 << i))) { // 如果第 i 个瓶子还没有被捡起
            int nx = bottles[i].first;
            int ny = bottles[i].second;
            
            // 使用按位或操作符 '|' 更新状态，表示捡起了第 i 个瓶子。
            // 例如，当前 state = 0100 | (1 << 1) = 0110，表示状态更新为第 0 和第 1 个瓶子都被捡起。
            int new_state = state | (1 << i); 
            
            // 先计算到达当前瓶子的位置的代价
            int cost_to_bottle = cost + abs(nx - x) + abs(ny - y);
            
            // 从瓶子位置移动到目标位置的代价
            int cost_to_goal = cost_to_bottle + abs(nx - c) + abs(ny - d);
            
            // 递归调用，从目标位置 `(c, d)` 出发去捡下一个瓶子
            int new_cost = dfs(c, d, new_state, cost_to_goal, n, c, d, bottles);
            
            // 更新最小代价
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

    // 从初始位置 `(a, b)` 开始，初始状态为 `0`，初始代价为 `0`
    int result = dfs(a, b, 0, 0, n, c, d, bottles);
    cout << result << endl;

    return 0;
}
