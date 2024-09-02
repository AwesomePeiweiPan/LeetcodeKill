#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 按照arr2的顺序对arr1排序，并返回结果
vector<int> solution(const vector<int> &arr1, const vector<int> &arr2) {
    // 记录arr2中元素的顺序
    unordered_map<int, int> rank;
    for (int i = 0; i < arr2.size(); i++) {
        rank[arr2[i]] = i;
    }

    // 复制arr1以便排序
    vector<int> sortedArr1 = arr1;

    // 自定义排序规则
    // [&](int a, int b){...} 为lambda函数
    // return true 则代表 a 应该在 b 之前
    // return false 则代表 a 应该在 b 之后
    sort(sortedArr1.begin(), sortedArr1.end(), [&](int a, int b) {
        // 如果a和b都在arr2中，按arr2的顺序排
        if (rank.count(a) && rank.count(b)) {
            return rank[a] < rank[b];
        }
        // 如果a在arr2中，b不在，那么a优先
        else if (rank.count(a)) {
            return true;
        }
        // 如果b在arr2中，a不在，那么b优先
        else if (rank.count(b)) {
            return false;
        }
        // 如果都不在arr2中，按从小到大排
        else {
            return a < b;
        }
    });

    return sortedArr1;
}

int main() {
    vector<int> arr1 = {2, 3, 1, 3, 2, 4, 6, 19, 9, 2, 7};
    vector<int> arr2 = {2, 1, 4, 3, 9, 8};
    
    // 调用solution函数
    vector<int> result = solution(arr1, arr2);

    // 输出排序后的结果
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

