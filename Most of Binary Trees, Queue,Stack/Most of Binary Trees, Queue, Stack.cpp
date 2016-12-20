#include<iostream>
#include"assert.h"
#include<queue>
#include<string>
#include<vector>
#include<cstring>
#include<fstream>
#include<stack>
#include<list>
#include<iomanip>
#include<cmath>
using namespace std;

struct Interval
{
	double a;
	double b;
	double length()
	{
		return abs(abs(b) - abs(a));
	}
};

template<typename T>
class Queue
{
	stack<T> stk1;//for push
	stack<T> stk2;//for pop

	void switchStacks(stack<T>& st1, stack<T>& st2)
	{
		while (!st2.empty())
		{
			T temp = st2.top();
			st1.push(temp);
			st2.pop();
		}
	}
	void copy(const Queue<T>& other)
	{
		stk1 = other.stk1;
		stk2 = other.stk2;
	}
	void del()
	{
		while (!stk1.empty())
			stk1.pop();
		while (!stk2.empty())
			stk2.pop();
	}
public:
	void pop()
	{
		if (stk2.empty())
			switchStacks(stk2, stk1);
		stk2.pop();
	}

	void push(T elem)
	{
		if (stk1.empty())
			switchStacks(stk1, stk2);
		stk1.push(elem);
	}
	T front()
	{
		if (stk2.empty())
			switchStacks(stk2, stk1);
		return stk2.top();
	}
	T back()
	{
		if (stk1.empty())
			switchStacks(stk1, stk2);
		return stk1.top();
	}
	bool empty()
	{
		if (stk1.empty() && stk2.empty())
			return true;
		return false;
	}
	Queue() :stk1(), stk2() {}
	Queue(const Queue<T>& other)
	{
		copy(other);
	}
	Queue& operator=(const Queue<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~Queue()
	{
		del();
	}
};

template<typename T>
struct Node
{
	T data;
	Node<T> *left, *right;
	Node()
	{
		left = NULL;
		right = NULL;
	}
	Node(T _data, Node<T>* _left, Node<T>* _right)
	{
		data = _data;
		left = _left;
		right = _right;
	}
};

template<typename T>
class BinTree
{
	Node<T> *root;

private:
	void copyHelper(Node<T>*& _root, Node<T>* otherRoot)
	{
		if (otherRoot == NULL)
			_root = NULL;
		else
		{
			_root = new Node<T>;
			_root->data = otherRoot->data;
			copyHelper(_root->left, otherRoot->left);
			copyHelper(_root->right, otherRoot->right);
		}
	}
	void delHelper(Node<T>*& _root)
	{
		if (_root != NULL)
		{
			delHelper(_root->left);
			delHelper(_root->right);
			delete _root;
		}
		_root = NULL;
	}
	int countHelper(Node<T>*& _root)
	{
		if (_root == NULL)
			return 0;
		else
			return countHelper(_root->left) + countHelper(_root->right) + 1;
	}
	int countEvenHelper(Node<T>*&_root)
	{
		if (_root == NULL)
			return 0;
		else
			if (_root->data % 2 == 0)
				return countEvenHelper(_root->left) + countEvenHelper(_root->right) + 1;
			else
				return countEvenHelper(_root->left) + countEvenHelper(_root->right);

	}
	int searchCountHelper(bool(*pred)(const T&), Node<T>*& _root)
	{
		if (_root == NULL)
			return 0;
		if (pred(_root->data))
			return searchCountHelper(pred, _root->left) + searchCountHelper(pred, _root->right) + 1;
		else
			return searchCountHelper(pred, _root->left) + searchCountHelper(pred, _root->right);
	}
	void unsortedAddHelper(T element)
	{
		Node<T>* newLeaf = closestFreeSpot();
		newLeaf = new Node<T>;
		newLeaf->data = element;

	}
	void addHelper(T element, Node<T>*& _root)
	{
		if (_root == NULL)
		{
			_root = new Node<T>;
			_root->data = element;
			return;
		}
		if (_root->data == element)
			cout << "Element already exists in tree!" << endl;
		if (_root->data > element)
			addHelper(element, _root->left);
		if (_root->data < element)
			addHelper(element, _root->right);
	}
	int heightHelper(Node<T>*&_root)
	{
		if (_root == NULL)
			return 0;
		else
			if (heightHelper(_root->left) > heightHelper(_root->right))
				return heightHelper(_root->left) + 1;
			else
				return heightHelper(_root->right) + 1;
	}
	Node<T>*& closestFreeSpotHelper(Node<T>*&_root)
	{
		if (_root == NULL)
			return _root;
		else
			if (minHeight(_root->left) < minHeight(_root->right))
				return closestFreeSpotHelper(_root->left);
			else
				return closestFreeSpotHelper(_root->right);
	}
	void sortHelper(Node<T>*& root1, Node<T>*&root2)//not working really...
	{
		if (root1->data > root2->data)
		{
			T d = root2->data;
			root2->data = root1->data;
			root1->data = d;
		}
		if (root1 == NULL || root2 == NULL)
			return;
		sortHelper(root1->left, root1->right);
		sortHelper(root2->left, root2->right);
		sortHelper(root1->left, root2->left);
		sortHelper(root1->right, root2->right);
		sortHelper(root1->left, root2->right);
		sortHelper(root1->right, root2->left);

	}
	void printHelper(Node<T>*&_root, ostream& out)
	{
		if (_root == NULL)
			return;
		printHelper(_root->left, out);
		out << _root->data << " ";
		printHelper(_root->right, out);
	}
	void printBFSHelper(Node<T>*&_root)const
	{
		queue<Node<T>*> q;
		if (_root != NULL)
			q.push(_root);
		while (!q.empty())
		{
			Node<T>*temp = q.front();
			cout << temp->data << " ";
			if (temp->left != NULL)
				q.push(temp->left);
			if (temp->right != NULL)
				q.push(temp->right);
			q.pop();
		}
		cout << endl;
	}
	int countLeavesHelper(Node<T>*& _root, int number)
	{
		if (_root == NULL)
			return 0;
		if (_root->left == NULL&&_root->right == NULL)
			return 1;
		else
			return countLeavesHelper(_root->left) + countLeavesHelper(_root->right);
	}
	T maxLeafHelper(Node<T>*&_root)
	{
		if (_root->left == NULL&&_root->right == NULL)
			return _root->data;
		if (_root->left != NULL&&_root->right == NULL)
			return maxLeafHelper(_root->left);
		if (_root->left == NULL&&_root->right != NULL)
			return maxLeafHelper(_root->right);
		if (_root->leaf != NULL&&_root->right != NULL)
		{
			if (maxLeafHelper(_root->left) > maxLeafHelper(_root->right))
				return maxLeafHelper(_root->left);
			else
				return maxLeafHelper(_root->right);
		}
	}
	T& getElementAtHelper(Node<T>*&_root, const char* s, int i)
	{
		if (s[i] == '\0')
			return _root->data;
		if (s[i] == 'L')
		{
			i++;
			return getElementAtHelper(_root->left, s, i);
		}
		if (s[i] == 'R')
		{
			i++;
			return getElementAtHelper(_root->right, s, i);
		}
		if (_root == NULL&& s[i] != '\0')
			assert(false);
	}
	void removeHelper(Node<T>*&_root, T element)
	{
		if (!member(element))
			return;
		if (_root->data == element&&_root->left == NULL&&_root->right == NULL)
		{
			delete _root;
			_root = NULL;
		}
		else if (_root->data == element&&_root->left == NULL)
		{
			Node<T>* temp = _root;
			_root = _root->right;
			delete temp;
		}
		else if (_root->data == element&&_root->right == NULL)
		{
			Node<T>* temp = _root;
			_root = _root->left;
			delete temp;
		}
		else if (_root->data == element)
		{
			_root->data = minElem(_root->right);
			removeHelper(_root->right, _root->data);
		}
		else if (_root->data > element)
		{
			removeHelper(_root->left, element);
		}
		else if (_root->data < element)
		{
			removeHelper(_root->right, element);
		}

	}
	bool memberHelper(Node<T>*&_root, T element)
	{
		if (_root == NULL)
			return false;
		if (_root->data == element)
			return true;
		return memberHelper(_root->left, element) || memberHelper(_root->right, element);
	}
	bool mirrorHelper(Node<T>*& lroot, Node<T>*& rroot)
	{
		if (lroot == NULL&&rroot == NULL)
			return true;
		if ((lroot != NULL && rroot == NULL) || (lroot == NULL && rroot != NULL))
			return false;
		if (lroot != NULL && rroot != NULL)
			return mirrrorHelper(lroot->left, rroot->right) && mirrorHelper(lroot->right, rroot->left);

	}
	T closestParentHelper(Node<T>*& _root, Node<T>*& l1, Node<T>*&l2)
	{
		if (memberHelper(_root->left, l1->data) && memberHelper(_root->right, l2->data) ||
			memberHelper(_root->left, l2->data) && memberHelper(_root->right, l1->data))
			return _root->data;
		else if (memberHelper(_root->left, l2->data) && memberHelper(_root->left, l2->data))
			return memberHelper(_root->left, l1, l2);
		else if (memberHelper(_root->right, l2->data) && memberHelper(_root->right, l2->data))
			return memberHelper(_root->right, l1, l2);
	}
	void findPathHelper(Node<T>*& _root, Node<T>*& leaf, string str)
	{
		if (_root == leaf)
			return;
		if (memberHelper(_root->left, leaf->data))
		{
			str.push_back('L');
			findPathHelper(_root->left, leaf, str);
		}
		else if (memberHelper(_root->right, leaf->data))
		{
			str.push_back('R');
			findPathHelper(_root->right, leaf, str);
		}
	}
	void levelHelper(Node<T>*&_root, int level, queue<T> queue)
	{
		if (level == 0)
			queue.push(_root->data);
		else
		{
			level--;
			levelHelper(_root->right, level, queue);
			levelHelper(_root->left, level, queue);
		}
	}
	bool isomorphicHelper(Node<T>*& _root1, Node<T>*& _root2)
	{
		if (_root1 == NULL&&_root2 == NULL)
			return true;
		if ((_root1 != NULL&&_root2 == NULL) ||
			(_root1 == NULL&&_root2 != NULL))
			return false;
		return isomorphicHelper(_root1->left, _root2->left) && isomorphicHelper(_root1->right, _root2->right);
	}
	void isBOTHelper(Node<T>*& _root, vector<T> vector)
	{
		if (_root == NULL)
			return;
		isBOTHelper(_root->left, vector);
		vector.push_back(_root->data);
		isBOTHelper(_root->right, vector);
	}
	int sumVHelper(Node<T>*& _root, int sum)
	{
		if (_root->data >= '*' _root->data <= '/')
		{
			switch (_root->data)
			{
			case'*': sum = sumVHelper(_root->left, sum)	* sumVHelper(_root->right, sum); break;
			case'+': sum = sumVHelper(_root->left, sum) + sumVHelper(_root->right, sum); break;
			case'-': sum = sumVHelper(_root->left, sum) - sumVHelper(_root->right, sum); break;
			case'/': sum = sumVHelper(_root->left, sum) - sumVHelper(_root->right, sum); break;
			}
			return _root->data;
		}
		else if (_root->left == NULL&&_root->right == NULL)
			return _root->data;
	}
	void listLeavesHelper(Node<T>*&_root, vector<T>& vector)
	{
		if (_root->left == NULL&&_root->right == NULL)
			vector.push_back(_root->data);
		else
		{
			listLeavesHelper(_root->left, vector);
			listLeavesHelper(_root->right, vector);
		}
	}
	void prettyPrintHelper(Node<T>*&_root, int depth)
	{
		if (_root == NULL)
			return;
		prettyPrintHelper(_root->right, depth + 1);
		cout << setw(depth * 4) << " " << _root->data << endl;
		prettyPrintHelper(_root->left, depth + 1);
	}
	bool check_treeHelper(int level, string& str)
	{
		string str1 = atlevel(level);
		if (str.compare(str1) == 0)
			return true;
		return false;

	}
	int height1H(Node<T>*& _root)
	{
		if (_root == NULL)
			return 0;
		else
			if (height1H(_root->left) > height1H(_root->right))
			{
				return height1H(_root->left) + 1;
			}
			else
				return height1H(_root->right) + 1;

	}
	void atLevelHelper(Node<T>*&_root, int level, string& string)
	{
		if (_root == NULL)
			return;
		if (level == 0)
			string += _root->data;
		else
		{
			level--;
			atLevelHelper(_root->left, level, string);
			atLevelHelper(_root->right, level, string);
		}
	}
	string checkPathsMirrorHelper(Node<T>*&_root, string& str, int i)
	{
		assert(_root != NULL);
		if (str.empty())
			return _root->data;
		else
		{
			if (str[i] == 'R')
			{
				i++;
				return checkPathsMirrorHelper(_root->right, str, str1, i);
			}
			else if (str[i] == 'L')
			{
				i++;
				return checkPathsMirrorHelper(_root->left, str, str1, i);
			}
		}
	}

private:
	void copy(const BinTree<T>& other)
	{
		copyHelper(root, other.root);
	}
	void del()
	{
		delHelper(root);
	}
	int minHeight(Node<T>*&_root)
	{
		if (_root == NULL)
			return 0;
		else
			if (minHeight(_root->left) < minHeight(_root->right))
				return minHeight(_root->left) + 1;
			else
				return minHeight(_root->right) + 1;

	}
	Node<T>*& closestFreeSpot()
	{
		return closestFreeSpotHelper(root);
	}
	static void deleted(const T& x, Node<T>*& _root)
	{
		if (_root->data == x && _root->left != NULL && _root->right != NULL)
		{
			_root->data = minElem(_root);
			deleted(minElem(_root), _root);
		}
		else if (_root->data == x && _root->left == NULL && _root->right == NULL)
		{
			delete _root;
			_root = NULL;
		}
		else if (_root->data == x && _root->left != NULL && _root->right == NULL)
		{
			Node<T>* temp = _root;
			_root = _root->left;
			delete temp;
		}
		else if (_root->data == x && _root->left == NULL && _root->right != NULL)
		{
			Node<T>* temp = _root;
			_root = _root->right;
			delete temp;
		}
		else if (_root->data < x)
		{
			deleted(x, _root->right);
		}
		else if (_root->data > x)
		{
			deleted(x, _root->left);
		}
	}
	bool checkQueues(queue<T> q1, queue<T> q2)
	{
		int counter = 0;
		while (!q1.empty())
		{
			queue<T> q3 = q2;
			while (!q3.empty())
			{
				if (q1.front() == q3.front())
				{
					counter++;
					break;
				}
				q3.pop();
			}
			q1.pop();
		}
		if (q1.size() == counter)
			return true;
		else return false;
	}
public:
	BinTree()
	{
		root = NULL;
	}
	BinTree(const BinTree<T>& other)
	{
		copy(other);
	}
	BinTree& operator=(const BinTree<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~BinTree() {
		del();
	}
	int count()
	{
		return countHelper(root);
	}
	int countEven()
	{
		return countEvenHelper(root);
	}
	int searchCount(bool(*pred)(const T&))
	{
		return searchCountHelper(pred, root);
	}
	void unsortedAdd(T element)
	{
		unsortedAddHelper(element);
	}
	void add(T element)
	{
		addHelper(element, root);
	}
	int height()
	{
		return heightHelper(root);
	}
	void sort()
	{
		sortHelper(root->left, root->right);
	}
	T minElem(Node<T>*&_root)const
	{
		assert(_root != NULL);
		Node<T>*crr = _root;
		while (crr->left != NULL)
			crr = crr->left;
		return crr->data;
	}
	T maxElem(Node<T>*&_root)const
	{
		assert(_root != NULL);
		Node<T>*crr = _root;
		while (crr->right != NULL)
			crr = crr->right;
		return crr->data;
	}
	void print()
	{
		printHelper(root, cout);
	}
	void printBFS()
	{
		printBFSHelper(root);
	}
	int countLeaves()
	{
		return countLeavesHelper(root);
	}
	T maxLeaf()
	{
		return maxLeafHelper(root);
	}
	T& getElementAt(const char* s)
	{
		return getElementAtHelper(root, s, 0);
	}
	void remove(T element)
	{
		if (memeber(element))
			removeHelper(root, element);
		else
			cout << "This element is not in the tree!" << endl;
	}
	bool member(T element)
	{
		return memberHelper(root, element);
	}
	bool mirror()
	{
		if (root == NULL)
			return false;
		return mirrorHelper(root->left, root->right);
	}
	T closestCommonParent(Node<T>*& leaf1, Node<T>*& leaf2)
	{
		return closestParentHelper(root, leaf1, leaf2);
	}
	Node<T>*& getRoot()
	{
		return root;
	}
	string findPath(Node<T>*& leaf)
	{
		string str;
		findPathHelper(root, leaf, str);
		return str;

	}
	queue<T> level(int level)
	{
		queue<T> queue;
		levelHelper(_root, level, queue);
		return queue;
	}
	bool levelCheck(queue<T> q, int level)
	{
		queue<T> q1 = level(level);
		while (!q1.empty() && !q.empty())
		{
			if (q.front() != q1.front())
				return false;
			q.pop();
			q1.pop();
		}
		if (!q.empty() && q1.empty() ||
			q.empty() && !q1.empty())
			return false;
		return true;
	}
	void readFromBin(char* fileName)
	{
		ifstream f;
		int i;
		f.open(fileName, ios::binary);
		while (f.read((char*)&i, sizeof(i)))
		{
			this->add(i);
		}
		f.close();
	}
	void writeToTextFile(char* fileName)
	{
		ofstream f;
		f.open(fileName);
		printHelper(root, f);
	}
	bool check2Levels(int lvl1, int lvl2)
	{
		queue<T> q1 = level(lvl1);
		queue<T> q2 = level(lvl2);
		int counter = 0;
		while (!q1.empty())
		{
			queue<T> q3 = q2;
			while (!q3.empty())
			{
				if (q3.front() == q1.front())
				{
					counter++;
					break;
				}
				else q3.pop();
			}
			q1.pop();
		}
		if (counter == q1.size)
			return true;
		else return false;
	}
	bool isomorphic(BinTree<T> tree)
	{
		return isomorphicHelper(root, tree.root);
	}
	BinTree<T> deleteBOT(const T& x)const
	{
		BinTree<T> newTree = new BinTree<T>(this);
		newTree.deleted(x, newTree.root);
		return newTree;
	}
	bool checkSimilarLevels()
	{
		int overall = 0;
		int counterI = 0;
		int counterJ = 0;
		for (int i = 0; i < height() - 1; i++)
		{
			queue<T> qi = level(i);
			for (int j = i + 1; j < height(); j++)
			{
				queue<T> qj = level(j);
				if (checkQueues(qi, qj) && checkQueues(qj, qi))
				{
					counterI++;
					counterJ++;
				}
				if (counterJ == qj.size())
					overall++;
			}
			if (counterI == qi.size())
			{
				overall++;
			}
		}
		if (counterJ + counterI == overall)
			return true;
		return false;
	}
	bool isBOT()
	{
		vector<T>vec;
		int counter = 0;
		isBOTHelper(root, vec);
		int vectorSize = vec.size();
		for (int i = 0; i < vec.size() - 1; i++)
		{
			T el1 = vec.back();
			vec.pop_back();
			T el2 = vec.back();
			if (el1 > el2)
				counter++;
		}
		if (counter == vectorSize)
			return true;
		return false;
	}
	int sumV()
	{
		int sum = 0;
		sum = sumVHelper(root, sum);
		return sum;

	}
	vector<T> listLeaves()
	{
		vector<T> vector;
		listLeavesHelper(root, vector);
		return vector;
	}
	void prettyPrint()
	{
		prettyPrintHelper(root, 0);
	}
	void createTree(Node<T>*& pos) const
	{
		T x;
		char c;
		cout << "root: "; cin >> x;
		pos = new Node<T>;
		assert(pos != NULL);
		pos->data = x;
		pos->left = NULL;
		pos->right = NULL;
		cout << "Left Tree of: " << x << " y/n? ";
		cin >> c;
		if (c == 'y') createTree(pos->left);
		cout << "Right Tree of: " << x << " y/n? ";
		cin >> c;
		if (c == 'y') createTree(pos->right);
	}
	int height1()
	{
		return height1H(root);
	}
	string atlevel(int level)
	{
		string str;
		atLevelHelper(root, level, str);
		return str;
	}
	bool check_tree()
	{
		string str;
		for (int i = 0; i < root->data.size(); i++)
		{
			str.push_back(root->data[i]);
		}
		for (int i = 1; i < height1(); i++)
		{
			if (!check_treeHelper(i, str))
				return false;

		}
		return true;
	}
	void createTreeMine(Node<T>*& pos)const
	{

		T data;
		char c;
		cout << "Root : ";
		cin >> data;
		pos = new Node<T>;
		pos->data = data;
		pos->left = NULL;
		pos->right = NULL;
		cout << "Left tree of " << data << " ?[Y/N]  ";
		cin >> c;
		if (c == 'y' || c == 'Y')
			createTreeMine(pos->left);
		if (c == 'n' || c == 'N')
			return;
		cout << "Right tree of " << x << " ?[Y/N]  ";
		cin >> c;
		if (c == 'y' || c == 'Y')
			createTreeMine(pos->right);
		if (c == 'n' || c == 'N')
			return;
	}
	bool checkPathsMirror(string str1, string str2)
	{
		string strOne = checkPathsMirrorHelper(root, str1, 0);
		string strTwo = checkPathsMirrorHelper(root, str2, 0);
		int counter = 0;
		for (int i = 0; i < strOne.size(); i++)
		{
			j = strTwo.size() - i;
			if (strOne[i] == strTwo[j])
				counter++;
		}
		if (counter == strOne.size())
			return true;
		return false;


	}
	bool mirrorPath(BinTree<T>& other)
	{
		list<T> crrPathThis = NULL;
		list<list<T>> allPathsThis = NULL;
		list<T>crrPathOther = NULL;
		list<list<T>> allPathsOther = NULL;
		findAllPaths(root, crrPathThis, allPathsThis);
		other.findAllPaths(other.root, crrPathOther, allPathsOther);
		for (list<list<T>>::const_iterator it1 = allPathsThis.cbegin(); it1 != allPathsThis.cend(); it1++)
		{
			for (list<list<T>>::const_iterator it2 = allPathsOther.cbegin(); it2 != allPathsOther.cend(); it2++)
			{
				list<T>::const_iterator it3 = (*it1).cbegin();
				list<T>::const_reverse_iterator it4 = (*it2).cbegin();
				while (it3 != (*it1).cend() && it4 != (*it2).cend() && *it3 == *it4)
				{
					it3++;
					it4++;
				}
				if (it3 == (*it1).cend() && it4 == (*it2).cend())
					return true;
			}
		}
		return false;
	}
	void findAllPaths(Node<T>*&_root, list<T>& crrPath, list<list<T>>& allPaths)
	{
		if (_root == NULL)
			return;
		crrPath.push_back(_root->data);
		if (_root->left == NULL&&_root->right == NULL)
			allPaths.push_back(crrPath);
		else
		{
			findAllPaths(_root->left, crrPath, allPaths);
			findAllPaths(_root->right, crrPath, allPaths);
		}
		crrPath.pop_back();
	}
	string readFromFile(char* fname)
	{
		ifstream f;
		string str;
		f.open(fname);
		char c;
		while (f)
		{
			f >> c;
			str.push_back(c);
		}
		f.close();
		return str;
	}
	bool sentenceOnLevel(BinTree<T>t, int k, char* fname)
	{
		string str = atlevel(k);
		string strFile = readFromFile(fname);
		int counter = 0;
		int i = 0;
		int j = 0;
		while (i < str.size() && j<strFile.size())
		{
			if (str[i] == strFile[j])
			{
				counter++;
				i++;
				j++;
			}
			else
			{
				counter = 0;
				j++;
				i = 0;
			}
		}
		if (counter == str.size())
			return true;
		return false;

	}

	//zzs-ta 
	//1)
	void listLeaves2H(Node<T>*& _root, vector<T>& list)
	{
		if (_root == NULL)
			return;
		if (_root->left == NULL&&_root->right == NULL)
			list.push_back(_root->data);
		else
		{
			listLeaves2H(_root->left, list);
			listLeaves2H(_root->right, list);
		}
	}
	vector<T> listLeaves2()
	{
		vector<T> vec;
		listLeaves2H(root, vec);
		return vec;
	}
	//2)
	bool member2H(Node<T>*&_root, const T& x)
	{
		if (_root->data == x)
			return true;
		if (_root == NULL)
			return false;
		return member2H(_root->left, x) || member2H(_root->right, x);
	}
	bool member2(const T& x)
	{
		return member2H(root, x);
	}
	void findTrace2H(Node<T>*&_root, const T& x, string& trace)
	{

		if (_root->data == x)
			return;
		if (member2H(_root->left, x))
		{
			trace.push_back('L');
			findTrace2H(_root->left, x, trace);
		}
		if (member2H(_root->right, x))
		{
			trace.push_back('R');
			findTrace2H(_root->right, x);
		}
	}
	string findTrace2(const T& x)
	{
		string trace;
		if (member2(x))
		{
			findTrace2H(root, x, trace);
		}
		else
			trace.push_back('_');
		return trace;
	}
	//3)
	void prettyPrint2H(Node<T>*&_root, int level)
	{
		if (_root == NULL)
			return;
		prettyPrint2H(_root->left, level + 1);
		cout << setw(level * 4) << " " << _root->data << endl;
		prettyPrint2H(_root->right, level + 1);
	}
	void prettyPrint2()
	{
		prettyPrint2H(root, 0);
	}
	//4)
	void schemeCreateHelper(Node<T>*&_root, char* str, int& i)
	{
		int el = 0;
		if (str[i] == '\0')
			return;
		if (str[i] == '(')
		{
			i++;
			if (str[i] == ' ')
			{
				i++;
				_root = NULL;
			}
			else
			{
				int a = 0;
				while (str[i] != ' ')
				{
					a = a * 10 + (str[i] - '0');
					i++;
				}
				_root = new Node<T>;
				_root->data = a;
				i++;
				schemeCreateHelper(_root->right, str, i);

				schemeCreateHelper(_root->left, str, i);
			}
		}
		if (str[i] == ')')
		{
			i++;
		}
	}
	void schemeCreate(char* x)
	{//(10 (20 (25 ( )( ))(15 ( )( )))(5 ( )( ))) 
		static int donttouchme = 0;
		schemeCreateHelper(root, x, donttouchme);

	}
	//4.5)
	void bFS()
	{
		bfsHs(root, cout);
		cout << endl;
	}
	void bfsHs(Node<T>*& _root, ostream& out)
	{
		queue<Node<T>*> q;
		if (_root != NULL)
			q.push(_root);
		while (!q.empty())
		{
			Node<T>* temp = q.front();
			out << temp->data << " ";
			if (temp->left != NULL)
				q.push(temp->left);
			if (temp->right != NULL)
				q.push(temp->right);
			q.pop();
		}
	}
	//5)
	T& opHelper(Node<T>*& _root, int i)
	{
		if (i == 0)
			return _root->data;
		else
		{
			i--;
			opHelper(_root->left);
			i--;
			opHelper(_root->right);
		}


	}
	T& operator[](int i)
	{
		static int j = i;
		return opHelper(root, i);
	}

	//HOMEWORK 
	//Task 2
	void switchLRHelper(Node<T>*&_root, Node<T>*& other)
	{
		if (other == NULL)
			return;
		else
		{
			_root = new Node<T>;
			_root->data = other->data*(-1);
			switchLRHelper(_root->left, other->right);
			switchLRHelper(_root->right, other->left);
		}
	}
	void minus1(Node<T>*&_root)
	{
		if (_root == NULL)
			return;
		else
		{
			_root->data = _root->data*(-1);
			minus1(_root->left);
			minus1(_root->right);
		}
	}
	void switchNodes(Node<T>*&_root)
	{
		if (_root == NULL || _root->left == NULL&&_root->right == NULL)
			return;
		if (_root->left != NULL&&_root->right == NULL)
		{
			_root->right = _root->left;
			switchNodes(_root->left);
			_root->left = NULL;
		}
		else if (_root->left == NULL&&_root->right != NULL)
		{
			_root->left = _root->right;
			switchNodes(_root->right);
			_root->right = NULL;
		}
		else if (_root->left != NULL&&_root->right != NULL)
		{
			Node<T>* temp = _root->right;
			_root->right = _root->left;
			_root->left = temp;
			switchNodes(_root->left);
			switchNodes(_root->right);
		}
	}
	void switchNodes()
	{
		switchNodes(root);
		minus1(root);
	}
	void switchLR()
	{
		BinTree<T> t(*this);
		del();
		switchLRHelper(root, t.root);
		t.del();
	}
	//Task 3
	void sumTreeH(Node<T>*&_root, int& number)
	{
		if (_root == NULL)
			return;
		else
		{
			sumTreeH(_root->right, number);
			number *= 10;
			number += _root->data;
			sumTreeH(_root->left, number);
		}
	}
	int sumTree()
	{
		int number = 0;
		sumTreeH(root, number);
		return number;
	}
	//Task 1
	void addIntTreeH(Node<Interval>*&_root, Interval x)
	{
		if (_root == NULL)
		{
			_root = new Node<Interval>;
			_root->data = x;
			return;
		}
		if (_root->data.length() > x.length())
			addIntTreeH(_root->left, x);
		else
			addIntTreeH(_root->right, x);

	}
	void addIntTree(Interval x)
	{
		addIntTreeH(root, x);
	}
	void huge(Node<Interval>*&_root, Interval& supSet)
	{
		if (_root == NULL)
			return;

		if (_root->data.a < supSet.a)
			supSet.a = _root->data.a;
		if (_root->data.b > supSet.b)
			supSet.b = _root->data.a;
		huge(_root->left, supSet);
		huge(_root->right, supSet);
	}
	Interval huuuge()
	{
		Interval x = root->data;
		huge(root, x);
		return x;
	}

	/*
	4)
	Да се дефинира функция
	bool sequenceOnLevel ([подходящ тип]t, int k, char *fname),
	която за дадено ниво k от двоичното дърво t проверява дали
	елементите на нивото k в t, четени от ляво на дясно, образуват
	редица над файла с име fname.
	*/
	/*
	TO DO LIST :
	5)
	Нека е дадено двоично дърво с елементи от тип char, за което е изпълнено,
	че:
	• Дървото е непразно • Всеки от възлите му има точно 2 или 0 наследника
	• Елементите с 2 наследника съдържат един от символите +,−, ∗ и /
	• Елементите с 0 наследника съдържат цифра Да се дефинира функция,
	която връща стойността на аритметичния израз, съответен на дървото.
	Например, стойността на израза, съответен на дървото от фигура 2, е 21.
	10)
	Да се дефинира оператор T& BTree<T>::operator[](int i),
	който намира i-тият пореден елемент на дървото при обхождане коренляво-дясно.
	Пример: За дървото от фигура 1, елементът с пореден номер 0 е 15, с номер 1 е 5,
	с номер 2 е 20 и т.н.
	11)
	Даседефинираметодvector<T> BTree<T>::level (int k),който намира и връща вектор,
	съдържащ стойностите на всички елементи на дървото, които са на ниво k
	(т.е. има път от корена до тях с дължина в брой върхове k).
	*/
};

int sumTrees(Node<int>*& root1, Node<char>*& root2)
{
	int result = 0;
	if (root1 == NULL)
		return 0;
	switch (root2->data)
	{
	case'+': result = result + root1->data; break;
	case'-': result = result - root1->data; break;
	case'*': result = result * root1->data; break;
	case'/': result = result / root1->data; break;
	}
	return result + sumTrees(root1->left, root2->right) + sumTrees(root1->right, root2->right);
}

int binOperations(char* str)
{
	stack<char> stk;
	int i = 0;
	int result = 0;
	stack<int> num;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			stk.push(str[i]);
			//cout << "step ( " << endl;
		}
		else if (str[i] >= '0'&&str[i] <= '9')
		{
			num.push(str[i] - '0');
			//cout << "step num " << endl;
		}
		else if (str[i] == '$' || str[i] == '@')
		{
			stk.push(str[i]);
			//cout << "step sym " << endl;
		}
		else if (str[i] == ')')
		{
			int b = num.top();
			num.pop();
			int a = num.top();
			num.pop();
			char c = stk.top();
			stk.pop();
			stk.pop();
			//cout << "step ) " << endl;
			if (c == '$')
			{
				if (a > b)
					a = b;
				//	cout << "step $ " <<a<< endl;
				num.push(a);
			}
			if (c == '@')
			{
				int h = (a + b) % 10;
				num.push(h);
				//	cout << "step @ " <<h<< endl;
			}
		}
		i++;
	}
	if (stk.empty() && !num.empty())
	{
		result = num.top();
		num.pop();
		return result;
	}
	else
		assert(false);
}

int findpH(int n, int p)
{
	queue<int> q;
	q.push(n);
	int i = 0;
	while (i != p)
	{
		if (i % 2 == 0)
		{
			int n1 = q.front();
			n1 += 1;
			q.push(n1);
			i++;
		}
		else if (i % 2 == 1)
		{
			int n1 = q.front();
			n1 *= 2;
			q.push(n1);
			q.pop();
			i++;
		}

	}
	return q.back();
}

void treeOverlay(BinTree<int> tree1, BinTree<char>tree2)
{
	cout << "Result = " << sumTrees(tree1.getRoot(), tree2.getRoot()) << endl;
}

int main()
{
	system("pause");
	return 0;
}