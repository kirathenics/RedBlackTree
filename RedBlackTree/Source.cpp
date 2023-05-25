#include <iostream>
using namespace std;

enum class Color 
{
	Black,
	Red,
};

template <class T>
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

private:

	template <class T>
	class Node
	{
	public:
		T data;
		Node* left, * right, * parent;
		Color color; //= Color::Black;

		Node() : data(T()), left(nullptr), right(nullptr), parent(nullptr), color(Color::Black)
		{}
		Node(T value) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(Color::Black)
		{}
		~Node();

	};

};


int main()
{

	return 0;
}