#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

 //Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
 
class Solution {

    void preoprel(TreeNode* node, std::vector<int>& answer)
    {
        if (node == nullptr)
            return;
        answer.push_back(node->val);
        preoprel(node->left, answer);
        preoprel(node->right, answer);
        return;
    }

public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr) //так быстрее
        {
            return {};
        }
        std::vector<int> answer;
        preoprel(root, answer);
        return answer;
    }

    std::vector<int> preorderTraversal2(TreeNode* root)
    {
        if (root == nullptr)
        {
            return {};
        }
        std::vector<int> answer;
        answer.push_back(root->val);
        std::vector<int> left = preorderTraversal2(root->left);
        answer.insert(answer.end(), std::make_move_iterator(left.begin()), std::make_move_iterator(left.end()));
        std::vector<int> right = preorderTraversal2(root->right);
        answer.insert(answer.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));

        return answer;
    }

    std::vector<int> preorderTraversalIterativ(TreeNode* root)
    {
        if (root == nullptr)
            return {};

        std::vector<int> answer;
        std::stack<std::pair<TreeNode*, bool>> stack;
        stack.push(std::make_pair(root, false));

        while (!stack.empty())
        {
            TreeNode* node = stack.top().first;
            bool flag = stack.top().second;

            //если поситили
            if (flag)
            {
                stack.pop();
                if(node->right!= nullptr)
                    stack.push(std::make_pair(node->right, false));
            }
            if (!flag)
            {
                answer.push_back(node->val);
                stack.top().second = true;
                if (node->left != nullptr)
                    stack.push(std::make_pair(node->left, false));
            }
        }

        return answer;
    }
};

void Test()
{
    using namespace std;
    Solution s;
    {
        TreeNode root;
        TreeNode left(3);
        TreeNode right(2, &left, nullptr);
        root.val = 1;
        root.right = &right;

        vector<int> result = { 1,2,3 };
        assert(result == s.preorderTraversal(&root));
    }
    {
        TreeNode root(1);
        vector<int> result = { 1 };
        assert(result == s.preorderTraversal(&root));
    }
    {
        TreeNode* root = nullptr;
        vector<int> result = s.preorderTraversal(root);
        assert(result.empty());
    }
    //---------------------------------------------------------
    {
        TreeNode root;
        TreeNode left(3);
        TreeNode right(2, &left, nullptr);
        root.val = 1;
        root.right = &right;

        vector<int> result = { 1,2,3 };
        assert(result == s.preorderTraversal2(&root));
    }
    {
        TreeNode root(1);
        vector<int> result = { 1 };
        assert(result == s.preorderTraversal2(&root));
    }
    {
        TreeNode* root = nullptr;
        vector<int> result = s.preorderTraversal2(root);
        assert(result.empty());
    }
    //--------------------------------------------------------
    {
        TreeNode root;
        TreeNode left(3);
        TreeNode right(2, &left, nullptr);
        root.val = 1;
        root.right = &right;

        vector<int> result = { 1,2,3 };
        vector<int> answer = s.preorderTraversalIterativ(&root);
        assert(result == s.preorderTraversalIterativ(&root));
    }
    {
        TreeNode root(1);
        vector<int> result = { 1 };
        assert(result == s.preorderTraversalIterativ(&root));
    }
    {
        TreeNode* root = nullptr;
        vector<int> result = s.preorderTraversalIterativ(root);
        assert(result.empty());
    }
    cout << "DONE";
}

int main()
{
    Test();
}