#pragma once
#include "BSTree.h"
#include "BSTnode.h"

class AVLTree : public BSTree
{
	public:
	AVLTree():BSTree(){
	}
	AVLTree(BSTnode* root):BSTree(root){
		root->Height = 1;
	}
	int Update_balance(BSTnode* n){
		if(n==nullptr)	return 0;
		return _Height(n->Left_Child) - _Height(n->Right_Child);
	}
	virtual BSTnode* Insert(int value) {
		BSTnode* new_node = BSTree::Insert(value);
		BSTnode *y = new_node->Parent;
		BSTnode* node_to_rotate = Update_Heights(y);
		if(node_to_rotate == nullptr)	//no rotation needed
			return new_node;
		int node_to_rotate_balance = Update_balance(node_to_rotate); 

		//LL
		if(node_to_rotate_balance > 1 && value < node_to_rotate->Left_Child->Data)
			Right_Rotate(node_to_rotate);
		//RR
		else if (node_to_rotate_balance < -1 && value > node_to_rotate->Right_Child->Data)
			Left_Rotate(node_to_rotate);
		//LR
		else if (node_to_rotate_balance > 1){
			Left_Rotate(node_to_rotate->Left_Child);
			Right_Rotate(node_to_rotate);
		}
		//RL
		else if (node_to_rotate_balance < -1){
			Right_Rotate(node_to_rotate->Right_Child);
			Left_Rotate(node_to_rotate);
		}
		return new_node;
	}
	virtual BSTnode* DeleteByVal(int value){
		BSTnode* n = BSTree::DeleteByVal(value);
		BSTnode* node_to_rotate = Update_Heights(n);
		if (node_to_rotate == nullptr)	//no rotation needed
			return n;////////////////doesn't matter(till now)
		int node_to_rotate_balance = Update_balance(node_to_rotate);

		//LL
		if (node_to_rotate_balance > 1 && Update_balance(node_to_rotate->Left_Child) >= 0)
			Right_Rotate(node_to_rotate);
		//RR
		else if (node_to_rotate_balance < -1 && Update_balance(node_to_rotate->Right_Child) <= 0)
			Left_Rotate(node_to_rotate);
		//LR
		else if (node_to_rotate_balance > 1) {
			Left_Rotate(node_to_rotate->Left_Child);
			Right_Rotate(node_to_rotate);
		}
		//RL
		else if (node_to_rotate_balance < -1) {
			Right_Rotate(node_to_rotate->Right_Child);
			Left_Rotate(node_to_rotate);
		}
		return n;////////////////doesn't matter(till now)
	}
};