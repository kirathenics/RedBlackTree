#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
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
		left(left),
		right(right),
		parent(parent),
		color(color)
	{}
	~Node() {}

};

template <class T>
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void insert(T value);
	void erase(T value);
	Node<T>* find(T value);
	T minimum();
	T maximum();
	void print();
	void makeImage();
	void clear();

private:
	Node<T>* root;
	Node<T>* nullRoot;

	void rotateLeft(Node<T>* ptr);
	void rotateRight(Node<T>* ptr);

	void fixInsertion(Node<T>* ptr);
	void deleteNode(Node<T>* ptr, T value);
	void moveNode(Node<T>* u, Node<T>* v);
	void fixDelete(Node<T>* ptr);

	Node<T>* findNode(Node<T>* ptr, T value);
	Node<T>* findMinimum(Node<T>* ptr);
	Node<T>* findMaximum(Node<T>* ptr);
	void deleteTree(Node<T>* ptr);

	void printNode(Node<T>* root, string indent, bool last);
	void writeNode(Node<T>* ptr, ofstream& file);
};

template<class T>
inline RedBlackTree<T>::RedBlackTree()
{
	nullRoot = new Node<T>;
	root = nullRoot;
}

template<class T>
inline RedBlackTree<T>::~RedBlackTree()
{
	deleteTree(this->root);
}

template<class T>
inline void RedBlackTree<T>::insert(T value)
{
	Node<T>* newNode = new Node<T>(value, this->nullRoot, this->nullRoot, nullptr, Color::Red);

	Node<T>* parentNode = nullptr, * soughtNode = this->root;
	while (soughtNode != this->nullRoot)
	{
		parentNode = soughtNode;
		if (newNode->data < soughtNode->data)
		{
			soughtNode = soughtNode->left;
		}
		else
		{
			soughtNode = soughtNode->right;
		}
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
inline void RedBlackTree<T>::erase(T value)
{
	deleteNode(this->root, value);
}

template<class T>
inline Node<T>* RedBlackTree<T>::find(T value)
{
	return findNode(this->root, value);
}

template<class T>
inline T RedBlackTree<T>::minimum()
{
	return findMinimum(this->root)->data;
}

template<class T>
inline T RedBlackTree<T>::maximum()
{
	return findMaximum(this->root)->data;
}

template<class T>
inline void RedBlackTree<T>::print()
{
	if (this->root) 
	{
		printNode(this->root, "", true);
	}
}

template<class T>
inline void RedBlackTree<T>::makeImage()
{
	ofstream file("tree.dot");

	file << "digraph BinarySearchTree {\n";
	writeNode(this->root, file);
	file << "}\n";
	file.close();

	system("dot -Tpng tree.dot -o tree.png");
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	cv::Mat img = cv::imread("tree.png", cv::ImreadModes::IMREAD_COLOR);
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display window", img);
	cv::waitKey(0);
}

template<class T>
inline void RedBlackTree<T>::clear()
{
	deleteTree(this->root);
	nullRoot = new Node<T>();
	root = nullRoot;
}

template<class T>
inline void RedBlackTree<T>::rotateLeft(Node<T>* ptr)
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
inline void RedBlackTree<T>::rotateRight(Node<T>* ptr)
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
inline void RedBlackTree<T>::fixInsertion(Node<T>* ptr)
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
					rotateRight(ptr);
				}
				ptr->parent->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				rotateLeft(ptr->parent->parent);
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
					rotateLeft(ptr);
				}
				ptr->parent->color = Color::Black;
				ptr->parent->parent->color = Color::Red;
				rotateRight(ptr->parent->parent);
			}
		}
		if (ptr == this->root) {
			break;
		}
	}
	this->root->color = Color::Black;
}

template<class T>
inline void RedBlackTree<T>::deleteNode(Node<T>* ptr, T value)
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
	if (soughtNode->left == this->nullRoot)
	{
		x = soughtNode->right;
		moveNode(soughtNode, soughtNode->right);
	}
	else if (soughtNode->right == this->nullRoot)
	{
		x = soughtNode->left;
		moveNode(soughtNode, soughtNode->left);
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
			moveNode(y, y->right);
			y->right = soughtNode->right;
			y->right->parent = y;
		}

		moveNode(soughtNode, y);
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
inline void RedBlackTree<T>::moveNode(Node<T>* previousNode, Node<T>* newNode)
{
	if (previousNode->parent == nullptr)
	{
		this->root = newNode;
	}
	else if (previousNode == previousNode->parent->left)
	{
		previousNode->parent->left = newNode;
	}
	else
	{
		previousNode->parent->right = newNode;
	}
	newNode->parent = previousNode->parent;
}

template<class T>
inline void RedBlackTree<T>::fixDelete(Node<T>* ptr)
{
	Node<T>* tempNode;
	while (ptr != root && ptr->color == Color::Black) 
	{
		if (ptr == ptr->parent->left) 
		{
			tempNode = ptr->parent->right;
			if (tempNode->color == Color::Red) 
			{
				tempNode->color = Color::Black;
				ptr->parent->color = Color::Red;
				rotateLeft(ptr->parent);
				tempNode = ptr->parent->right;
			}

			if (tempNode->left->color == Color::Black && tempNode->right->color == Color::Black)
			{
				tempNode->color = Color::Red;
				ptr = ptr->parent;
			}
			else 
			{
				if (tempNode->right->color == Color::Black)
				{
					tempNode->left->color = Color::Black;
					tempNode->color = Color::Red;
					rotateRight(tempNode);
					tempNode = ptr->parent->right;
				}

				tempNode->color = ptr->parent->color;
				ptr->parent->color = Color::Black;
				tempNode->right->color = Color::Black;
				rotateLeft(ptr->parent);
				ptr = root;
			}
		}
		else 
		{
			tempNode = ptr->parent->left;
			if (tempNode->color == Color::Red)
			{
				tempNode->color = Color::Black;
				ptr->parent->color = Color::Red;
				rotateRight(ptr->parent);
				tempNode = ptr->parent->left;
			}

			if (tempNode->right->color == Color::Black)
			{
				tempNode->color = Color::Red;
				ptr = ptr->parent;
			}
			else 
			{
				if (tempNode->left->color == Color::Black)
				{
					tempNode->right->color = Color::Black;
					tempNode->color = Color::Red;
					rotateLeft(tempNode);
					tempNode = ptr->parent->left;
				}

				tempNode->color = ptr->parent->color;
				ptr->parent->color = Color::Black;
				tempNode->left->color = Color::Black;
				rotateRight(ptr->parent);
				ptr = root;
			}
		}
	}
	ptr->color = Color::Black;
}

template<class T>
inline Node<T>* RedBlackTree<T>::findNode(Node<T>* ptr, T value)
{
	if (value == ptr->data || ptr == this->nullRoot)
	{
		return ptr;
	}
	return (value > ptr->data) ? findNode(ptr->right, value) : findNode(ptr->left, value);
}

template<class T>
inline Node<T>* RedBlackTree<T>::findMinimum(Node<T>* ptr)
{
	while (ptr->left != this->nullRoot)
	{
		ptr = ptr->left;
	}
	return ptr;
}

template<class T>
inline Node<T>* RedBlackTree<T>::findMaximum(Node<T>* ptr)
{
	while (ptr->right != this->nullRoot)
	{
		ptr = ptr->right;
	}
	return ptr;
}

template<class T>
inline void RedBlackTree<T>::deleteTree(Node<T>* ptr)
{
	if (ptr == this->nullRoot) return;

	deleteTree(ptr->left);
	deleteTree(ptr->right);

	//cout << "\n Deleting node: " << ptr->data;
	delete ptr;
}

template<class T>
inline void RedBlackTree<T>::printNode(Node<T>* root, string indent, bool last)
{
	if (root != this->nullRoot) 
	{
		cout << indent;
		if (last) 
		{
			cout << "R----";
			indent += "     ";
		}
		else 
		{
			cout << "L----";
			indent += "|    ";
		}

		string rootColor;
		if (root->color == Color::Red) rootColor = "RED";
		else rootColor = "BLACK";
		cout << root->data << "(" << rootColor << ")" << endl;
		printNode(root->left, indent, false);
		printNode(root->right, indent, true);
	}
}

template<class T>
inline void RedBlackTree<T>::writeNode(Node<T>* ptr, ofstream& file)
{
	if (ptr == this->nullRoot) return;

	string nodeColor;
	if (ptr->color == Color::Red) nodeColor = "red";
	else nodeColor = "black";
	file << "\"" << ptr->data << "\" [color=" << nodeColor << "]" << endl;
	if (ptr->left != this->nullRoot) {
		file << "\"" << ptr->data << "\" -> \"" << ptr->left->data << "\"\n";
		writeNode(ptr->left, file);
	}

	if (ptr->right != this->nullRoot) {
		file << "\"" << ptr->data << "\" -> \"" << ptr->right->data << "\"\n";
		writeNode(ptr->right, file);
	}
}
