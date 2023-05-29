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
		cout << "�������� ��������:" << endl
			<< "0) ����� �� ���������" << endl
			<< "1) �������� ������� � ������" << endl
			<< "2) ������� ������� �� ������" << endl
			<< "3) ����� �������� � ������" << endl
			<< "4) ����� ������������ �������� � ������" << endl
			<< "5) ����� ������������� �������� � ������" << endl
			<< "6) ����� ������ � �������" << endl
			<< "7) �������� ����������� ������" << endl;

		cin >> action;
		switch (action)
		{
		case Action::Exit:
			break;

		case Action::Insert:
		{
			cout << "������� �������� ��������: ";
			int value;
			cin >> value;

			tree.insert(value);
			cout << "������� ��������!" << endl;
			break;
		}

		case Action::Erase:
		{
			cout << "������� �������� ��������: ";
			int value;
			cin >> value;

			if (tree.erase(value))
			{
				cout << "������� ������!" << endl;
			}
			break;
		}

		case Action::Find:
		{
			cout << "������� �������� ��������: ";
			int value;
			cin >> value;

			cout << (tree.find(value)->data ? "������� ������" : "������ �������� ���!") << endl;
			break;
		}

		case Action::Minimum:
		{
			cout << "�������� ������������ ��������:" << tree.minimum() << endl;
			break;
		}

		case Action::Maximum:
		{
			cout << "�������� ������������� ��������:" << tree.maximum() << endl;
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
			cout << "������ �������� ���!" << endl;
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