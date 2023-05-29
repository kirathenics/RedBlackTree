#include "RedBlackTree.h"

enum Action
{
	Exit,
	Insert,
	Erase,
	Find, 
	Minimum,
	Maximum,
	Print,
	Show
};

int main()
{
	setlocale(0, "");

	RedBlackTree<int> tree;
	int action = 1;
	while (action)
	{
		cout << "Выберите действие:" << endl
			<< "0) Выйти из программы" << endl
			<< "1) Добавить элемент в дерево" << endl
			<< "2) Удалить элемент из дерева" << endl
			<< "3) Поиск элемента в дереве" << endl
			<< "4) Поиск минимального элемента в дереве" << endl
			<< "5) Поиск максимального элемента в дереве" << endl
			<< "6) Вывод дерева в консоль" << endl
			<< "7) Показать изображение дерева" << endl;

		cin >> action;
		switch (action)
		{
		case Action::Exit:
			break;

		case Action::Insert:
		{
			cout << "Введите значение элемента: ";
			int value;
			cin >> value;

			tree.insert(value);
			cout << "Элемент добавлен!" << endl;
			break;
		}

		case Action::Erase:
		{
			cout << "Введите значение элемента: ";
			int value;
			cin >> value;

			if (tree.erase(value))
			{
				cout << "Элемент удален!" << endl;
			}
			break;
		}

		case Action::Find:
		{
			cout << "Введите значение элемента: ";
			int value;
			cin >> value;

			cout << (tree.find(value)->data ? "Элемент найден" : "Такого элемента нет!") << endl;
			break;
		}

		case Action::Minimum:
		{
			cout << "Значение минимального элемента:" << tree.minimum() << endl;
			break;
		}

		case Action::Maximum:
		{
			cout << "Значение максимального элемента:" << tree.maximum() << endl;
			break;
		}

		case Action::Print:
		{
			tree.print();
			break;
		}

		case Action::Show:
		{
			tree.makeImage();
			break;
		}

		default:
			cout << "Такого действия нет!" << endl;
			break;
		}
		cout << endl;
	}
	/*RedBlackTree<int> bst;
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
	bst.makeImage();*/
	return 0;
}