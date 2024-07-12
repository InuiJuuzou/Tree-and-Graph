#include <iostream>
#include <stack>

struct TreeNode{
	int value;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
	TreeNode(int val) :value(val) {}
};

//считаем путь с максимумом в дереве только положительные числа
int calculate(TreeNode* root)
{
	//база и выход рекурсии если дошли до нулевого возвращаем его
	if (root == nullptr)
	{
		return 0;
	}
	//else if (root->left == nullptr && root->right==nullptr)
	//{
	//	return root->value;
	//}
	//находим рекурсивно суммы для правого и левого ребенка
	int sumLeft = calculate(root->left);
	int sumRight = calculate(root->right);
	return std::max(sumLeft, sumRight) + root->value;
}

//Просто сумма всех элементов
int sumImp(TreeNode* root)
{
	std::stack<TreeNode*> lists;
	lists.push(root);
	int sum=0;

	while (!lists.empty())
	{
		TreeNode* node = lists.top();
		lists.pop();
		sum += node->value;

		if (node->left != nullptr)
		{
			lists.push(node->left);
		}
		if (node->right != nullptr)
		{
			lists.push(node->right);
		}
	}
	return sum;
}

int main()
{
	TreeNode root(1);
	TreeNode left(4);
	TreeNode right(7);
	TreeNode l_left(2);
	TreeNode r_left(3);
	TreeNode l_r_left(2);
	TreeNode l_right(5);
	TreeNode r_right(4);

	root.left = &left;
	root.right = &right;

	left.left = &l_left;
	left.right = &r_left;
	r_left.left = &l_r_left;

	right.left = &l_right;
	right.right = &r_right;

	std::cout << calculate(&root);
}