#include<iostream>
#include<cstring>
#include<assert.h>
using namespace std;

template<typename T>
struct Box
{
	T data;
	Box<T>* next;
	Box()
	{
		next = NULL;
	}
};

template<typename T>
class Stack
{
	Box<T>* top;
public:
	Stack()
	{
		top = NULL;
	}
	Stack(Box<T>* _top)
	{
		top = _top;
	}
	void push(T elem)
	{
		Box<T>* temp = new Box<T>;
		temp->data = elem;
		temp->next = top;
		top = temp;
	}
	void pop()
	{
		Box<T>* temp;
		temp = top;
		top = top->next;
		delete temp;
	}
	bool empty()
	{
		if (top == NULL)
			return true;
		return false;
	}
	void copy(const Stack<T>& other)
	{
		if (!empty())
		{
			top = new Box<T>;
			top->data = other.top->data;
			Box<T>* newcrr = top;
			Box<T>* crr = other.top->next;
			while (crr != NULL)
			{
				Box<T>* p = new Box<T>;
				p->data = crr->data;
				crr = crr->next;
				newcrr->next = p;
			}
		}
		else cout << "Nothing to copy \n";
	}
	Stack(const Stack<T>& other)
	{
		copy(other);
	}
	void del()
	{
		if (!empty())
		{
			while (top->next != NULL)
			{
				Box<T>* temp = top;
				top = top->next;
				delete temp;
			}
			delete top;
		}
	}
	~Stack()
	{
		del();
	}
	Stack<T>& operator=(const Stack<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	T topOfStack()
	{
		if (!empty())
		{
			return top->data;
		}
		assert(false);
	}
};

int checkPriority(char sym)
{
	if (sym == '+' || sym == '-')
		return 1;
	if (sym == '*' || sym == '/')
		return 2;
	if (sym == '(')
		return 0;
	else cout << "Invalid Operator!" << endl;
}
void reverser(char* not)//not==Notation
{
	Stack<char> stk;
	char* revnot = new char[strlen(not) + 1];
	int i = 0;
	int j = 0;
	while (not[i] != '\0')
	{
		if (not[i] == '(')
			stk.push(not[i]);
		if (not[i] >= '0' && not[i] <= '9')
		{
			revnot[j] = not[i];
			j++;
		}
		if (not[i] >= '*' && not[i] <= '/')
		{
			int prOfTopOfStack;
			int prOfStringEl;
			if (!stk.empty())
			{
				prOfTopOfStack = checkPriority(stk.topOfStack());
				prOfStringEl = checkPriority(not[i]);
				if (prOfTopOfStack < prOfStringEl)
					stk.push(not[i]);
				else
					while (checkPriority(stk.topOfStack()) >= checkPriority(not[i]))
					{
						revnot[j] = stk.topOfStack();
						j++;
						stk.pop();
					}
			}
			else stk.push(not[i]);
		}
		if (not[i] == ')')
		{
			while (stk.topOfStack() != '(')
			{
				revnot[j] = stk.topOfStack();
				j++;
				stk.pop();
			}
			stk.pop();
		}
		i++;
	}
	while (!stk.empty())
	{
		revnot[j++] = stk.topOfStack();
		stk.pop();
	}
	revnot[j] = '\0';
	cout << revnot;
}

int main()
{
	char a[100];
	cin >> a;
	reverser(a);
	cout << endl;

	system("pause");
    return 0;
}