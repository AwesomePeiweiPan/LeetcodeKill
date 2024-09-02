/*
 为了更好地理解代码的运行逻辑，我们可以通过一步步的执行过程来展示如何进行拓扑排序。以下是图的构建和拓扑排序的详细过程：

 ### 示例图结构

 我们将以下图作为例子：

 ```
    0 → 1
    ↓ ↘
    2   5
    ↑  ↙
    3 → 4
    ↓
    6
 ```

 ### 图的顶点与边

 根据 `main` 函数中的 `addEdge` 调用，图的构建如下：
 - `g.addEdge(0, 1);` 添加边 `0 → 1`
 - `g.addEdge(0, 2);` 添加边 `0 → 2`
 - `g.addEdge(0, 5);` 添加边 `0 → 5`
 - `g.addEdge(1, 4);` 添加边 `1 → 4`
 - `g.addEdge(3, 2);` 添加边 `3 → 2`
 - `g.addEdge(3, 4);` 添加边 `3 → 4`
 - `g.addEdge(3, 5);` 添加边 `3 → 5`
 - `g.addEdge(3, 6);` 添加边 `3 → 6`
 - `g.addEdge(5, 2);` 添加边 `5 → 2`
 - `g.addEdge(6, 0);` 添加边 `6 → 0`
 - `g.addEdge(6, 4);` 添加边 `6 → 4`

 ### 拓扑排序执行过程

 1. **初始状态**：
    - 所有节点都未访问。
    - 访问数组：`visited = [false, false, false, false, false, false, false]`
    - 栈 `Stack` 初始为空。

 2. **遍历每个顶点，执行递归**：

    - **从节点 `0` 开始**：
      - `visited[0] = true`
      - 递归访问 `0` 的邻接节点 `1`, `2`, 和 `5`。

    - **节点 `1`**：
      - `visited[1] = true`
      - 递归访问 `1` 的邻接节点 `4`。

    - **节点 `4`**：
      - `visited[4] = true`
      - `4` 没有未访问的邻接节点，压入栈：`Stack = [4]`

    - 回到节点 `1`，`1` 完成，压入栈：`Stack = [1, 4]`

    - **节点 `2`**：
      - `visited[2] = true`
      - `2` 没有未访问的邻接节点，压入栈：`Stack = [2, 1, 4]`

    - **节点 `5`**：
      - `visited[5] = true`
      - 递归访问 `5` 的邻接节点 `2`（已访问）。
      - `5` 完成，压入栈：`Stack = [5, 2, 1, 4]`

    - 回到节点 `0`，`0` 完成，压入栈：`Stack = [0, 5, 2, 1, 4]`

    - **节点 `3`**：
      - `visited[3] = true`
      - 递归访问 `3` 的邻接节点 `2`, `4`, `5`, 和 `6`。

    - **节点 `6`**：
      - `visited[6] = true`
      - 递归访问 `6` 的邻接节点 `0`（已访问）和 `4`（已访问）。
      - `6` 完成，压入栈：`Stack = [6, 0, 5, 2, 1, 4]`

    - 回到节点 `3`，`3` 完成，压入栈：`Stack = [3, 6, 0, 5, 2, 1, 4]`

 3. **结果输出**：
    - 将栈中的元素按顺序弹出，得到拓扑排序结果。
    
    **拓扑排序结果**:
    ```
    3 6 0 5 2 1 4
    ```

 ### 运行逻辑总结

 1. 从未访问的节点开始，递归遍历所有邻接节点。
 2. 所有邻接节点都处理完后，当前节点入栈。
 3. 最后按栈的顺序弹出所有节点，形成拓扑排序结果。

 拓扑排序结果的顺序可能会有所不同，但所有排序都满足节点依赖关系。
 
 
 
 */




#include <string>
#include <list>
#include <vector>
#include <stack>
#include <assert.h>
#include <iostream>

using namespace std;

class Graph {
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists

    // A function used by topologicalSort
    void topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack);

public:
    Graph(int V);   // Constructor
    ~Graph();       // Destructor

    void addEdge(int v, int w);   // function to add an edge to graph
    list<int>* getAdj() const { return adj; }
    int getV() const { return V; }
    vector<int> sort();    // function to perform topological sort
};

Graph::Graph(int V) {
    this->V = V;
    // 动态分配包含 V 个 list<int> 的数组
    adj = new list<int>[V];
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v’s list.
}

void Graph::topologicalSortUtil(int v, vector<bool> &visited, stack<int> &Stack) {
    // Mark the current node as visited.
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);

    // Push current vertex to stack which stores result
    Stack.push(v);
}

vector<int> Graph::sort() {
    stack<int> Stack;
    vector<int> result;
    // Mark all the vertices as not visited
    vector<bool> visited(V, false);

    // Call the recursive helper function to store Topological Sort starting from all vertices one by one
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, Stack);

    // Now pop all vertices from stack and add to result
    while (!Stack.empty()) {
        result.push_back(Stack.top());
        Stack.pop();
    }
    return result;
}

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 5);
    g.addEdge(1, 4);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(3, 6);
    g.addEdge(5, 2);
    g.addEdge(6, 0);
    g.addEdge(6, 4);

    vector<int> result = g.sort();

    cout << "拓扑排序结果: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

