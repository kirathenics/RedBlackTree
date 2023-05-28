#include "RedBlackTree.h"

int main()
{
	RedBlackTree<int> bst;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	bst.erase(25);
	bst.printTree();
	bst.makeImage();
	return 0;
}