#include <iostream>
#include "BSTree.h"
#include "AVLTree.h"
#include "RBTree.h"
using namespace std;
int main()
{
	BSTree* ptr = nullptr;
	cout<<"Note: Since it is out of course range, deleting a node from a red-black tree is not implemented in this program\n";
	cout << "please choose tree type\n1-BST\n2-AVL\n3-Red Black\n";
	int c;	cin >> c;
	bool isrb = false;
	while (c != 1 && c != 2 && c != 3) {
		cout << "please choose 1, 2, or 3\n";
		cin >> c;
	}
	if (c == 1)	ptr = new BSTree();
	else if (c == 2)	ptr = new AVLTree();
	else if (c == 3)	ptr = new RBTree, isrb = true;

	while (1) {
		cout << "\n\nchoose the operation\n1-insert\n2-delete\n3-search a value\n4-draw tree\n5- print tree inorder\n6- print tree levelorder\nany other key to exit\n";
		int n;	cin >> n;
		if (n == 1) {
			cout << "enter numbers one by one , -1 to stop" << endl;
			int x;	cin >> x;
			while (x != -1) {
				ptr->Insert(x);
				cin >> x;
			}
		}
		else if (n == 2) {
			cout << "enter numbers one by one , -1 to stop" << endl;
			int x;	cin >> x;
			while (x != -1) {
				ptr->DeleteByVal(x);
				cin >> x;
			}
		}
		else if (n == 3) {
			cout << "enter value you want to search for" << endl;
			int x;	cin >> x;
			if (ptr->SearchByValue(x) == nullptr)	cout << "value is not in the tree\n";
			else				cout << "value found\n";
		}	
		else if (n==4)	ptr->Draw(isrb);
		else if (n==5)	ptr->Print_Inorder();
		else if (n==6)	ptr->Print_levelorder();
		else	break;
	}

}
