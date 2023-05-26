#include <iostream>
using namespace std;

enum class Color 
{
	Black,
	Red,
};

template <class T>
class Node
{
public:
	T data;
	Node* left, * right, * parent;
	Color color;

	Node(T value = T(), Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, Color color = Color::Black) : 
		data(value), 
		left(nullptr), 
		right(nullptr), 
		parent(nullptr), 
		color(Color::Black)
	{}
	~Node() {}
};

template <class T>
class RedBlackTree
{
public:

	RedBlackTree();
	~RedBlackTree();

	void rotateLeft(Node<T>* ptr);
	void rotateRight(Node<T>* ptr);
	void insert(T value);

private:
	Node<T>* root;
	Node<T>* nullRoot;

	void fixInsertion(Node<T>* ptr);
};


int main()
{
	RedBlackTree<int> test;

	return 0;
}

template<class T>
RedBlackTree<T>::RedBlackTree()
{
	nullRoot = new Node<T>();
	root = nullRoot;
}

template<class T>
RedBlackTree<T>::~RedBlackTree()
{
}

template<class T>
void RedBlackTree<T>::rotateLeft(Node<T>* ptr)
{
	Node<T>* newRoot = ptr->right;
	ptr->right = newRoot->left;
	if (newRoot->left != this->nullRoot)
	{
		newRoot->left->parent = ptr;
	}
	newRoot->parent = ptr->parent;
	if (ptr->parent == nullptr)
	{
		this->root = newRoot;
	}
	else if (ptr == ptr->parent->left)
	{
		ptr->parent->left = newRoot;
	}
	else 
	{
		ptr->parent->right = newRoot;
	}
	newRoot->left = ptr;
	ptr->parent = newRoot;
}

template<class T>
void RedBlackTree<T>::rotateRight(Node<T>* ptr)
{
	Node<T>* newRoot = ptr->left;
	ptr->left = newRoot->right;
	if (newRoot->right != this->nullRoot)
	{
		newRoot->right->parent = ptr;
	}
	newRoot->parent = ptr->parent;
	if (ptr->parent == nullptr)
	{
		this->root = newRoot;
	}
	else if (ptr == ptr->parent->right)
	{
		ptr->parent->right = newRoot;
	}
	else
	{
		ptr->parent->left = newRoot;
	}
	newRoot->right = ptr;
	ptr->parent = newRoot;
}

template<class T>
void RedBlackTree<T>::insert(T value)
{
	Node<T>* newNode = new Node<T>(value, nullRoot, nullRoot, nullptr, Color::Red);

	Node<T>* parentNode, * soughtNode = this->root;
	while (soughtNode != this->nullRoot)
	{
		parentNode = soughtNode;
		newNode->data < soughtNode->left ? soughtNode = soughtNode->left : soughtNode = soughtNode->right;
	}

	newNode->parent = parentNode;
	if (parentNode == nullptr)
	{
		this->root = newNode;
	}
	else if (newNode->data < parentNode->data) 
	{
		parentNode->left = newNode;
	}
	else 
	{
		parentNode->right = newNode;
	}

	if (newNode->parent == nullptr)
	{
		newNode->color = Color::Black;
		return;
	}

	if (newNode->parent->parent == nullptr)
	{
		return;
	}

	fixInsertion(newNode);
}

template<class T>
void RedBlackTree<T>::fixInsertion(Node<T>* ptr)
{
	Node<T>* uncleNode;
	while (ptr->parent->color == Color::Red)
	{
		if (ptr->parent == ptr->parent->parent->right)
		{
			uncleNode = ptr->parent->parent->left;
			if (uncleNode->color == Color::Red)
			{
				ptr->parent->color = Color::Black;
				uncleNode->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				ptr = ptr->parent->parent;
			}
			else 
			{
				if (ptr == ptr->parent->left)
				{
					ptr = ptr->parent;
					rightRotate(ptr);
				}
				ptr->parent->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				leftRotate(ptr->parent->parent);
			}
		}
	}
}


/*

		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = 0;

*/