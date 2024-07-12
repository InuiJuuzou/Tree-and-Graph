#include <iostream>
#include <vector>
#include <cassert>
#include <stack>
#include <utility>

#pragma execution_character_set("utf-8")

 //Definition for a binary tree node.
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 //симметричный обход узлов дерева
class Solution {
public:
    //долго и неособо правильно
    //рекурсивно
    std::vector<int> inorderTraversalSlow(TreeNode* root) {
        if (root == nullptr)
        {
            return {};
        }
        std::vector<int> answer = inorderTraversalSlow(root->left);
        answer.push_back(root->val);
        std::vector<int> right = inorderTraversalSlow(root->right);
        answer.insert(answer.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));

        return answer;
    }
    //рекурсивно
    std::vector<int> inorderTraversal(TreeNode* root)
    {
        std::vector<int> answer;
        inorder(root, answer);
        return answer;
    }
    //итеративно
    std::vector<int> inorderTraversalIt(TreeNode* root)
    {
        //сам узел и то посещяли или нет
        std::stack<std::pair<TreeNode*,bool>> lists;
        std::vector<int> answer;
        lists.push(std::make_pair(root, false));
        while (!lists.empty())
        {
            TreeNode* node = lists.top().first;
            bool flag = lists.top().second;
            if (node != nullptr)
            {
                //если левого ребенка нет добавляем в ответ
                if (node->left == nullptr)
                {
                    lists.pop();
                    answer.push_back(node->val);
                    if (node->right != nullptr)
                    {
                        lists.push(std::make_pair(node->right,false));
                    }
                }
                else
                {
                    //true - посещяли
                    if (flag)
                    {
                        answer.push_back(node->val);
                        lists.pop();
                        //если есть правый потомок
                        if (node->right != nullptr)
                        {
                            lists.push(std::make_pair(node->right, false));
                        }
                    }
                    else //не посещяли
                    {
                        lists.top().second = true;
                        lists.push(std::make_pair(node->left, false));
                    }
                }
            }
        }
        return answer;
    }
private:
    void inorder(TreeNode* node, std::vector<int>& answer)
    {
        if (node == nullptr)
        {
            return;
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            answer.push_back(node->val);
            return;
            //return answer;
        }

        inorder(node->left, answer);
        answer.push_back(node->val);
        inorder(node->right, answer);
        return;
    }


};

void Test()
{
    using namespace std;
    Solution s;
    {
        TreeNode root(1);
        TreeNode l(2);
        TreeNode lr(3);
        root.right = &l;
        l.left = &lr;
        vector<int> truu_ans = { 1,3,2 };
        //assert(truu_ans == s.inorderTraversalIt(&root));
        vector<int> ans = s.inorderTraversalIt(&root);

        for (int i : ans)
        {
            cout << i << " ";
        }
    }
    {

    }
    cout << "DONE" << endl;
}

int main()
{
    Test();
}