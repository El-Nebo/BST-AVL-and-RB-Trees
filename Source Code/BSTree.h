#pragma once
#include "BSTnode.h"
#include <queue>
#include <iostream>
#include <string>

class RBTree;
class BSTree
{
protected:
	BSTnode* Root;


	int _Height(BSTnode* n)
	{
		if (n == nullptr)	return 0;
		return n->Height;
	}
	COLOR _Color(BSTnode* n) {
		if (n == nullptr)	return Black;
		return n->Color;
	}
	void Left_Rotate(BSTnode* node_x) {
		BSTnode* node_y = node_x->Right_Child;
		node_x->Right_Child = node_y->Left_Child;
		if (node_y->Left_Child != nullptr)	node_y->Left_Child->Parent = node_x;
		node_y->Parent = node_x->Parent;
		if (node_x->Parent == nullptr)
			Root = node_y;
		else if (node_x == node_x->Parent->Left_Child)
			node_x->Parent->Left_Child = node_y;
		else
			node_x->Parent->Right_Child = node_y;
		node_y->Left_Child = node_x;
		node_x->Parent = node_y;
		Update_Heights(node_x);
	}
	void Right_Rotate(BSTnode* node_x) {
		BSTnode* node_y = node_x->Left_Child;
		node_x->Left_Child = node_y->Right_Child;
		if (node_y->Right_Child != nullptr)	node_y->Right_Child->Parent = node_x;
		node_y->Parent = node_x->Parent;
		if (node_x->Parent == nullptr)
			Root = node_y;
		else if (node_x == node_x->Parent->Left_Child)
			node_x->Parent->Left_Child = node_y;
		else
			node_x->Parent->Right_Child = node_y;
		node_y->Right_Child = node_x;
		node_x->Parent = node_y;
		Update_Heights(node_x);
	}
	BSTnode* Update_Heights(BSTnode* y) {
		int rightheight, leftheight;
		BSTnode* Return_ptr = nullptr;
		while (y != nullptr) {
			rightheight = _Height(y->Right_Child);
			leftheight = _Height(y->Left_Child);
			y->Height = 1 + std::max(rightheight, leftheight);
			if (rightheight - leftheight > 1 || leftheight - rightheight > 1) {
				if (Return_ptr == nullptr)	Return_ptr = y;
			}
			y = y->Parent;
		}
		return Return_ptr;
	}


	BSTnode* Maximum(BSTnode* root) {
		while (root->Right_Child != nullptr)
			root = root->Right_Child;
		return root;
	}
	BSTnode* Minimum(BSTnode* root) {
		while (root->Left_Child != nullptr)
			root = root->Left_Child;
		return root;
	}
	BSTnode* Predecessor(BSTnode* root) {
		if (root->Left_Child != nullptr)
			return Maximum(root->Left_Child);
		BSTnode* p = root->Parent;
		while (p != nullptr && root == p->Left_Child) {
			root = p;
			p = root->Parent;
		}
		return p;
	}
	BSTnode* Successor(BSTnode* root) {
		if (root->Right_Child != nullptr)
			return Minimum(root->Right_Child);
		BSTnode* p = root->Parent;
		while (p != nullptr && root == p->Right_Child) {
			root = p;
			p = root->Parent;
		}
		return p;
	}
	void Inorder_traversal(BSTnode* root) {
		if (root == nullptr)	return;
		Inorder_traversal(root->Left_Child);
		std::cout << root->Data << ' ';
		Inorder_traversal(root->Right_Child);
	}
	void levelorder_traversal(BSTnode* root) {
		std::queue<BSTnode*> q;
		q.push(root);
		while (q.size()) {
			BSTnode* cur = q.front();
			q.pop();
			std::cout << cur->Data << ' ';
			if (cur->Left_Child != nullptr) q.push(cur->Left_Child);
			if (cur->Right_Child != nullptr) q.push(cur->Right_Child);
		}
	}
	BSTnode* Transplant(BSTnode* oldn, BSTnode* newn) {
		if (oldn->Parent == nullptr)		Root = newn;
		else if (oldn == oldn->Parent->Left_Child)	oldn->Parent->Left_Child = newn;
		else	oldn->Parent->Right_Child = newn;
		if (newn != nullptr)	 newn->Parent = oldn->Parent;
		return newn;
	}
	BSTnode* Delete_Node(BSTnode* node) {
		if (node->Left_Child == nullptr && node->Right_Child == nullptr)
		{//additional case for adjusting heights 
			BSTnode* Return_ptr = node->Parent;
			Transplant(node, node->Right_Child);
			return Return_ptr;
		}
		if (node->Left_Child == nullptr)
			return Transplant(node, node->Right_Child);
		else if (node->Right_Child == nullptr)
			return Transplant(node, node->Left_Child);
		else {
			BSTnode* Return_ptr = nullptr;
			BSTnode* newnode = Minimum(node->Right_Child);
			Return_ptr = newnode;
			if (newnode->Parent != node) {
				Return_ptr = Return_ptr->Parent;
				Transplant(newnode, newnode->Right_Child);
				newnode->Right_Child = node->Right_Child;
				newnode->Right_Child->Parent = newnode;
			}
			Transplant(node, newnode);
			newnode->Left_Child = node->Left_Child;
			newnode->Left_Child->Parent = newnode;
			return Return_ptr;
		}
	}
	void Tree_Print(BSTnode* node, std::string str, bool isRB) {
		if (node == nullptr)	return;
		if (node->Left_Child == nullptr && node->Right_Child == nullptr) return;

		std::cout << str << "|__ ";
		if (node->Right_Child != nullptr) {
			std::cout << node->Right_Child->Data;
			if (isRB) {
				if (node->Right_Child->Color == Red)	std::cout << "R";
				else		std::cout << "B";
			}
		}

		std::cout << std::endl;
		Tree_Print(node->Right_Child, str + "|   ", isRB);

		std::cout << str + "|   " << '\n';
		std::cout << str + "|   " << '\n';

		std::cout << str << "|__ ";
		if (node->Left_Child != nullptr) {
			std::cout << node->Left_Child->Data;
			if (isRB) {
				if (node->Left_Child->Color == Red)	std::cout << "R";
				else		std::cout << "B";
			}
		}
		std::cout << std::endl;
		Tree_Print(node->Left_Child, str + "   ", isRB);
	}

public:
	BSTree() {
		Root = nullptr;
	}
	BSTree(BSTnode* r) {
		Root = r;
	}
	BSTnode* Get_Root() {
		return Root;
	}
	int Tree_Maximum() {
		return Maximum(Root)->Data;
	}
	int Tree_Minimum() {
		return Minimum(Root)->Data;

	}
	BSTnode* SearchByValue(int key) {
		BSTnode* root = Root;
		while (root != nullptr && key != root->Data) {
			if (key < root->Data)	root = root->Left_Child;
			else					root = root->Right_Child;
		}
		return root;
	}
	virtual BSTnode* Insert(int value) {
		BSTnode* node_place = Root, * new_node_parent = nullptr;
		BSTnode* new_node = new BSTnode(value);
		while (node_place != nullptr) {
			new_node_parent = node_place;
			if (value < node_place->Data)		node_place = node_place->Left_Child;
			else								node_place = node_place->Right_Child;
		}
		if (new_node_parent == nullptr)	Root = new_node;
		else if (value < new_node_parent->Data)		new_node_parent->Left_Child = new_node;
		else										new_node_parent->Right_Child = new_node;
		new_node->Parent = new_node_parent;
		return new_node;
	}
	virtual BSTnode* DeleteByVal(int value) {
		BSTnode* node_to_delete = SearchByValue(value);
		if (node_to_delete == nullptr)	return node_to_delete;
		BSTnode* temp = Delete_Node(node_to_delete);
		delete node_to_delete;
		return temp;
	}
	void Print_Inorder() {
		Inorder_traversal(Root);
		std::cout << std::endl;
	}
	void Print_levelorder() {
		levelorder_traversal(Root);
		std::cout << std::endl;
	}
	virtual void Draw(bool isRB = 0) {
		if (Root == nullptr) {
			std::cout << "Empty Tree\n";
			return;
		}
		std::cout << Root->Data;
		if (isRB){
			if (Root->Color == Red)	std::cout << "R";
			else		std::cout << "B";
		}
		std::cout << std::endl;
		Tree_Print(Root, "", isRB);
	}
};