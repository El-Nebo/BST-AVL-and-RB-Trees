#pragma once
#include "BSTree.h"
#include "BSTnode.h"

class RBTree : public BSTree
{
	

public:
	RBTree():BSTree(){
	}
	RBTree(BSTnode* root):BSTree(root){
	}

	virtual BSTnode* Insert(int value) {
		BSTnode* new_node = BSTree::Insert(value);
		BSTnode* node = new_node;
		while(_Color(node->Parent) == Red){
			if(node->Parent == node->Parent->Parent->Left_Child){
				BSTnode* uncle = node->Parent->Parent->Right_Child;
				if(_Color(uncle) == Red){
					node->Parent->Color = Black;
					uncle->Color = Black;
					node->Parent->Parent->Color = Red;
					node = node->Parent->Parent;
				}
				else{
					if(node == node->Parent->Right_Child){
						node = node->Parent;
						Left_Rotate(node);
					}
					node->Parent->Color = Black;
					node->Parent->Parent->Color = Red;
					Right_Rotate(node->Parent->Parent);
				}
			} 
			else{

				BSTnode* uncle = node->Parent->Parent->Left_Child;
				if (_Color(uncle) == Red) {
					node->Parent->Color = Black;
					uncle->Color = Black;
					node->Parent->Parent->Color = Red;
					node = node->Parent->Parent;
				}
				else {
					if (node == node->Parent->Left_Child) {
						node = node->Parent;
						Right_Rotate(node);
					}
					node->Parent->Color = Black;
					node->Parent->Parent->Color = Red;
					Left_Rotate(node->Parent->Parent);
				}

			}
		}
		Root->Color = Black;
		return new_node;
	}
	//virtual BSTnode* DeleteByVal(int value) {}
};