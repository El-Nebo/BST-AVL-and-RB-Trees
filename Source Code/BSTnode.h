#pragma once

enum COLOR {Red,Black};
class BSTnode
{
public:
	//All data are public to ease the implementation of the trees
	//In addition, same node has color property and height which is a waste of memory
	//However, we will ignore that to ,again :), ease the implementation 
	BSTnode* Parent, * Left_Child, * Right_Child;
	COLOR Color;
	int Height;
	int Data;
	
	BSTnode(int d)
	{
		Data = d;
		Parent = Left_Child = Right_Child = nullptr;
		Color = Red;
		Height = 1;
	}

	

};

