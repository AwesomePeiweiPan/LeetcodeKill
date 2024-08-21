#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    unordered_map<Node*, Node*> visited;

    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        if (visited.find(node) != visited.end()) {
            return visited[node];
        }

        Node* cloneNode = new Node(node->val);
        visited[node] = cloneNode;

        for (auto neighbor : node->neighbors) {
            cloneNode->neighbors.push_back(cloneGraph(neighbor));
        }

        return cloneNode;
    }
};

// 辅助函数：通过二维列表构建图
Node* buildGraph(const vector<vector<int>>& adjList) {
    if (adjList.empty()) return nullptr;

    // 创建所有节点
    unordered_map<int, Node*> nodes;
    for (int i = 1; i <= adjList.size(); ++i) {
        nodes[i] = new Node(i);
    }

    // 建立邻居关系
    for (int i = 0; i < adjList.size(); ++i) {
        for (int neighbor : adjList[i]) {
            nodes[i + 1]->neighbors.push_back(nodes[neighbor]);
        }
    }

    return nodes[1];  // 返回第一个节点的引用
}

// 辅助函数：打印图结构（BFS遍历）
void printGraph(Node* node) {
    if (!node) return;

    unordered_map<Node*, bool> visited;
    queue<Node*> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << "Node " << current->val << " has neighbors: ";
        for (Node* neighbor : current->neighbors) {
            cout << neighbor->val << " ";
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
        cout << endl;
    }
}

int main() {
    // 输入的二维邻接表
    vector<vector<int>> adjList = {{2, 4}, {1, 3}, {2, 4}, {1, 3}};

    // 构建原始图
    Node* originalGraph = buildGraph(adjList);

    // 打印原始图
    cout << "Original Graph:" << endl;
    printGraph(originalGraph);

    // 克隆图
    Solution solution;
    Node* clonedGraph = solution.cloneGraph(originalGraph);

    // 打印克隆后的图
    cout << "\nCloned Graph:" << endl;
    printGraph(clonedGraph);

    return 0;
}

