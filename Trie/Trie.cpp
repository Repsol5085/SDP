#include<iostream>
using namespace std;
struct Node
{
	Node* parent;
	Node* children[26];
	bool end;
	int value;
	Node(Node* _parent = NULL, bool _end = false, int _value = -1)
	{
		parent = _parent;
		end = _end;
		value = _value;
		for (int i = 0; i < 26; i++)
		{
			children[i] = new Node();
		}
	}
};

class Trie
{
	Node* root;


	void copyHelp(Node*& _root, Node* parent,Node*otherRoot)
	{
		if (otherRoot == NULL)
			_root = NULL;
		else
		{
			_root = new Node;
			_root->value = otherRoot->value;
			_root->end = otherRoot->end;
			_root->parent = parent;
			for (int i = 0; i < 26; i++)
			{
				copyHelp(_root->children[i],_root, otherRoot->children[i]);
			}
		}
	}
	void copy(const Trie& other)
	{
		copyHelp(root,NULL, other.root);
	}
	void delHelp(Node*& _root)
	{
		if (_root != NULL)
		{
			for (int i = 0; i < 26; i++)
			{
				delHelp(_root->children[i]);
			}
			delete _root;
			_root = NULL;
		}
	}
	void del()
	{
		delHelp(root);
	}
public:
	Trie()
	{
		root = NULL;
	}
	Trie(const Trie& other)
	{
		copy(other);
	}
	~Trie()
	{
		del();
	}
	Trie& operator=(const Trie& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	int& operator[](const char* word)
	{
		Node*p=root;
		//iterator index e word [i] - 'a' ;
		for (int i = 0; word[i] != '\0'; i++)
		{
			int index = word[i] - 'a';
			if (p->children[index] == NULL)
				p->children[index] = new Node(p);
			p = p->children[index];
		}
		p->end = true;
		return p->value;//["hello"] = 13 vrushta -1 i zamenq -1 s 13;
	}
	bool member(const char* word)
	{
		Node* p = root;
		for (int i = 0; word[i]!= '\0'; i++)
		{
			
		}
	}
};

int main()
{
    return 0;
}

