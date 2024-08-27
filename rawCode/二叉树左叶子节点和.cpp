/**
 *题目，给一个树，求左叶子的和
 *Exmaple 1:
 *   3
 *  / \
 * 9   20
 *     / \
 *    15  7
 * input: root = [3,9,20,null,null,15,7]
 * Output: 24
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstdlib>
#include <sstream>



using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int stringToInt(const string& str){
    int num;
    stringstream ss(str);
    ss >> num;
    return num;
}



TreeNode* buildTree(const vector<string>& nodes){
    
    
    if (nodes.empty() || nodes[0]=="null") return nullptr;
    
    int rootValue = stringToInt(nodes[0]);
    
    TreeNode* root = new TreeNode(rootValue);
    queue<TreeNode*> q;
    q.push(root);
    int i =1;
    
    while(i<nodes.size()){
        TreeNode* current = q.front();
        q.pop();
        
        if(nodes[i]!="null"){
            int leftValue = stringToInt(nodes[i]);
            current->left = new TreeNode(leftValue);
            q.push(current->left);
            cout<<"left "<<current->left->val<<endl;
        }
        i++;
        
        if(i<nodes.size() && nodes[i]!="null"){
            int rightValue = stringToInt(nodes[i]);
            current->right = new TreeNode(rightValue);
            q.push(current->right);
            cout<<"right "<<current->right->val<<endl;
        }
        i++;
    }
    return root;
}


int sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr) return 0;
    
    int sum =0;
    
    if(root->left && root->left->left == nullptr && root->left->right ==nullptr){
        sum += root->left->val;
        cout<<sum<<endl;
    }
    
    sum +=sumOfLeftLeaves(root->left);
    sum +=sumOfLeftLeaves(root->right);

    return sum;
}


int main() {
    // 直接在代码中定义输入数据
    std::vector<std::string> nodes = {"3", "9", "20", "null", "null", "15", "7"};

    // 根据输入构建二叉树并输出节点构建情况
    TreeNode* root = buildTree(nodes);

    // 计算左叶子节点的和
    int result = sumOfLeftLeaves(root);
    std::cout << "左叶子节点的和: " << result << std::endl;

    return 0;
}