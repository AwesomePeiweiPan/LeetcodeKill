
/*
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<long long, int> PII;

vector<vector<PII>> adj;  // 邻接表表示图

vector<long long> dijkstra(int start, int n) {
    priority_queue<PII, vector<PII>, greater<PII>> pq;
    vector<long long> dist(n + 1, LLONG_MAX);
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto [weight, v] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

long long greedyTSP(int n) {
    vector<bool> visited(n + 1, false);
    int current = 1;
    long long total_distance = 0;

    visited[current] = true;

    for (int i = 1; i < n; ++i) {
        vector<long long> dist = dijkstra(current, n);
        long long min_dist = LLONG_MAX;
        int next_node = -1;

        for (int j = 1; j <= n; ++j) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                next_node = j;
            }
        }

        if (next_node == -1) {
            return -1;  // 无法到达所有节点
        }

        visited[next_node] = true;
        total_distance += min_dist;
        current = next_node;
    }

    return total_distance;
}

int main() {
    int n;
    cin >> n;
    adj.resize(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].emplace_back(w, y);
        adj[y].emplace_back(w, x);
    }

    long long result = greedyTSP(n);

    if (result == -1) {
        cout << "无法到达所有节点" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool isValid(int x, int y, int n, int m) {
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

int bfs(int n, int m, int x1, int y1, int x2, int y2) {
    vector<vector<vector<vector<bool>>>> visited(n + 1, vector<vector<vector<bool>>>(m + 1, vector<vector<bool>>(n + 1, vector<bool>(m + 1, false))));
    queue<tuple<int, int, int, int>> q;
    q.push(make_tuple(x1, y1, x2, y2));
    visited[x1][y1][x2][y2] = true;

    int reachable = 0;

    while (!q.empty()) {
        auto [cx1, cy1, cx2, cy2] = q.front();
        q.pop();

        reachable += 2;

        for (const auto& dir : directions) {
            int nx1 = cx1 + dir[0], ny1 = cy1 + dir[1];
            int nx2 = cx2 + dir[0], ny2 = cy2 + dir[1];

            if (isValid(nx1, ny1, n, m) && isValid(nx2, ny2, n, m) && 
                !visited[nx1][ny1][nx2][ny2] && 
                (nx1 != nx2 || ny1 != ny2)) {
                
                visited[nx1][ny1][nx2][ny2] = true;
                q.push(make_tuple(nx1, ny1, nx2, ny2));
            }
        }
    }

    return reachable;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, x1, y1, x2, y2;
        cin >> n >> m >> x1 >> y1 >> x2 >> y2;

        int reachable = bfs(n, m, x1, y1, x2, y2);

        int total_points = n * m;
        int unreachable = total_points - reachable / 2; // 每次移动会算2个点

        cout << unreachable << endl;
    }

    return 0;
}

