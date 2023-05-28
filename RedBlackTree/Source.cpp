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
	void erase(T value);
	Node<T>* find(T value);
	void clear();
	T minimum();
	T maximum();

private:
	Node<T>* root;
	Node<T>* nullRoot;

	Node<T>* findMinimum(Node<T>* ptr);
	Node<T>* findMaximum(Node<T>* ptr);

	void fixInsertion(Node<T>* ptr);
	void deleteNodeHelper(Node<T>* ptr, T value);
	void rbTransplant(Node<T>* u, Node<T>* v);
	void fixDelete(Node<T>* ptr);
	Node<T>* findNode(Node<T>* ptr, T value);
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
Node<T>* RedBlackTree<T>::findMinimum(Node<T>* ptr)
{
	while (ptr->left != this->nullRoot)
	{
		ptr = ptr->left;
	}
	return ptr;
}

template<class T>
Node<T>* RedBlackTree<T>::findMaximum(Node<T>* ptr)
{
	while (ptr->right != this->nullRoot)
	{
		ptr = ptr->right;
	}
	return ptr;
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
		else
		{
			uncleNode = ptr->parent->parent->right;
			if (uncleNode->color == Color::Red)
			{
				ptr->parent->color = Color::Black;
				uncleNode->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				ptr = ptr->parent->parent;
			}
			else
			{
				if (ptr == ptr->parent->right)
				{
					ptr = ptr->parent;
					leftRotate(ptr);
				}
				ptr->parent->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				rightRotate(ptr->parent->parent);
			}
		}
	}
}

template<class T>
void RedBlackTree<T>::erase(T value)
{
	deleteNodeHelper(this->root, data);
}

template<class T>
Node<T>* RedBlackTree<T>::find(T value)
{
	return findNode(this->root, value);
}

template<class T>
T RedBlackTree<T>::minimum()
{
	return findMinimum(this->root)->data;
}

template<class T>
T RedBlackTree<T>::maximum()
{
	return findMaximum(this->root)->data;
}

template<class T>
void RedBlackTree<T>::deleteNodeHelper(Node<T>* ptr, T value)
{
	Node<T>* soughtNode = nullRoot, * x, * y;
	while (ptr != this->nullRoot)
	{
		if (ptr->data == value)
		{
			soughtNode = ptr;
		}
		if (ptr->data <= value)
		{
			ptr = ptr->right;
		}
		else 
		{
			ptr = ptr->left;
		}
	}

	if (soughtNode == this->nullRoot)
	{
		cout << "Ёлемент не найден!" << endl;
		return;
	}

	y = soughtNode;
	Color yOriginalColor = y->color;
	if (soughtNode->left == TNULL) 
	{
		x = soughtNode->right;
		rbTransplant(soughtNode, soughtNode->right);
	}
	else if (soughtNode->right == TNULL) 
	{
		x = soughtNode->left;
		rbTransplant(soughtNode, soughtNode->left);
	}
	else 
	{
		y = findMinimum(soughtNode->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->parent == soughtNode) {
			x->parent = y;
		}
		else {
			rbTransplant(y, y->right);
			y->right = soughtNode->right;
			y->right->parent = y;
		}

		rbTransplant(soughtNode, y);
		y->left = soughtNode->left;
		y->left->parent = y;
		y->color = soughtNode->color;
	}
	delete soughtNode;
	if (yOriginalColor == Color::Black)
	{
		fixDelete(x);
	}
}

template<class T>
void RedBlackTree<T>::rbTransplant(Node<T>* u, Node<T>* v)
{
	if (u->parent == nullptr) 
	{
		this->root = v;
	}
	else if (u == u->parent->left) 
	{
		u->parent->left = v;
	}
	else 
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

template<class T>
void RedBlackTree<T>::fixDelete(Node<T>* ptr)
{
	NodePtr s;
	while (ptr != root && ptr->color == 0) {
		if (ptr == ptr->parent->left) {
			s = ptr->parent->right;
			if (s->color == 1) {
				// case 3.1
				s->color = 0;
				ptr->parent->color = 1;
				leftRotate(ptr->parent);
				s = ptr->parent->right;
			}

			if (s->left->color == 0 && s->right->color == 0) {
				// case 3.2
				s->color = 1;
				ptr = ptr->parent;
			}
			else {
				if (s->right->color == 0) {
					// case 3.3
					s->left->color = 0;
					s->color = 1;
					rightRotate(s);
					s = ptr->parent->right;
				}

				// case 3.4
				s->color = ptr->parent->color;
				ptr->parent->color = 0;
				s->right->color = 0;
				leftRotate(ptr->parent);
				ptr = root;
			}
		}
		else {
			s = ptr->parent->left;
			if (s->color == 1) {
				// case 3.1
				s->color = 0;
				ptr->parent->color = 1;
				rightRotate(ptr->parent);
				s = ptr->parent->left;
			}

			if (s->right->color == 0 && s->right->color == 0) {
				// case 3.2
				s->color = 1;
				ptr = ptr->parent;
			}
			else {
				if (s->left->color == 0) {
					// case 3.3
					s->right->color = 0;
					s->color = 1;
					leftRotate(s);
					s = ptr->parent->left;
				}

				// case 3.4
				s->color = ptr->parent->color;
				ptr->parent->color = 0;
				s->left->color = 0;
				rightRotate(ptr->parent);
				ptr = root;
			}
		}
	}
	ptr->color = 0;
}

template<class T>
Node<T>* RedBlackTree<T>::findNode(Node<T>* ptr, T value)
{
	if (value == ptr->data || ptr == this->nullRoot)
	{
		return ptr;
	}
	return (value > ptr->data) ? findNode(ptr->right, value) : findNode(ptr->left, value);
}
