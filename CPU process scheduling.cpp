#include <iostream>
#include <string>
using namespace std;

//in excute: parameter type process or template
//late process, if stack is empty condition

class CPUProcess
{
private:
	int ProcessID;
	string ProcessName;
	double TimeNeeded;
public:
	//constructor
	CPUProcess()
	{
		ProcessID = 0;
		ProcessName = "";
		TimeNeeded = 0;
	}
	CPUProcess(int id, string name, double time)
	{
		ProcessID = id;
		ProcessName = name;
		TimeNeeded = time;
	}
	//setters
	void set_ProcessID(int id)
	{
		ProcessID = id;
	}
	void set_ProcessName(string name)
	{
		ProcessName = name;
	}
	void set_TimeNeeded(double time)
	{
		TimeNeeded = time;
	}

	//getters
	int get_ProcessID()
	{
		return ProcessID;
	}
	string get_ProcessName()
	{
		return ProcessName;
	}
	double get_TimeNeeded()
	{
		return TimeNeeded;
	}

	//printing method
	void printProcessInfo()
	{
		cout << "Process ID: \t" << ProcessID << endl;
		cout << "Process Name: \t" << ProcessName << endl;
		cout << "Time needed: \t" << TimeNeeded << endl;
		cout << "------------------------------" << endl;
	}
};

template <class T>
class ProcessNode
{
public:
	T value;
	ProcessNode<T>* next;
	ProcessNode(T p)
	{
		value = p;
		next = NULL;
	}
};


template<class T>
class StackLL
{
	ProcessNode<T>* top;
public:
	StackLL() {
		top = NULL;
	}
	bool pushProcess(T process) {
		ProcessNode<T>* newnode = new ProcessNode<T>(process);
		if (emptyStack())
		{
			top = newnode;
			return true;
		}
		newnode->next = top;
		top = newnode;
		return true;

	}
	bool stackOfProcesses()
	{
		if (!top)
		{
			cout << "stack is empty" << endl;
			return false;
		}
		ProcessNode<T>* ptr = top;
		while (ptr)
		{
			ptr->value.printProcessInfo();
			ptr = ptr->next;
		}
		return true;
	}
	CPUProcess lateProcess()
	{
		int count = 0;
		ProcessNode<T>* ptr = top;
		if (!emptyStack())
		{
			while (ptr)
			{
				count++;
				ptr = ptr->next;
			}
			cout << "There are " << count << " processes in the stack" << endl;
			return top->value;
		}
		cout << "stack is empty" << endl;

	}
	bool emptyStack()
	{
		if (!top)
			return true;
		return false;
	}
};


template <class T>
class QueueLL
{
private:
	double capacity = 3;
	ProcessNode<T>* front;
	ProcessNode<T>* rear;
public:
	QueueLL()
	{
		front = NULL;
		rear = NULL;

	}

	bool execute(CPUProcess process) // T ( n ) = 7n + 12 ,     O ( n )
	{
		ProcessNode<T>* newnode = new ProcessNode<T>(process); //T(1)
		ProcessNode<T>* ptr = front;//T(1)
		if (front == NULL)//T(1)
		{
			front = newnode;//T(1)
			rear = newnode;//T(1)
			cout << "process added to queue" << endl;//T(1)
			return true;//T(1)
		}
		while (ptr) //T( 5n )
		{
			if (ptr->value.get_ProcessID() == process.get_ProcessID()) //T(1)
			{
				cout << "process already exists" << endl;//T(1)
				return false;//T(1)
			}
			ptr = ptr->next;//T(1)
		}
		ptr = front;//T(1)
		while (ptr->next) //T(2n)
		{
			ptr = ptr->next; //T(1)
		}
		ptr->next = newnode;//T(1)
		rear = ptr->next;//T(1)
		cout << "process added to queue" << endl;//T(1)
		return true;//T(1)
	}
	CPUProcess runProcess(CPUProcess process)
	{
		ProcessNode<T>* ptr = front;
		CPUProcess DelP = front->value;
		if (process == front->value)
		{
			if (process.get_TimeNeeded() <= capacity)
			{
				front = ptr->next;
				delete ptr;
				cout << "Process execution is completed" << endl;
				return DelP;
			}
		}
	}

	void cpuSchedule()
	{
		if (!front)
		{
			cout << "queue is empty" << endl;
			return;
		}
		ProcessNode<T>* ptr = front;
		while (ptr)
		{
			ptr->value.printProcessInfo();
			ptr = ptr->next;
		}
	}

	bool killProcess(StackLL<T> *sll)
		{
		ProcessNode<T>* ptr=front;
		double t = front->value.get_TimeNeeded();
		if (!front)
		{
			cout << "queue is empty" << endl;
			return false;
		}
		if (t > capacity)
		{
			sll->pushProcess(ptr->value);
			front = front->next;
			delete ptr;
			return true;
		}
		return false;
	}

	};


template <class T>
class TNode
{
public:
	T value;
	TNode<T>* Right;
	TNode<T>* Left;
	TNode(T v)
	{
		value = v;
		Right = NULL;
		Left = NULL;
	}
};

template <class T>
class BST
{
public:
	TNode<T>* root;
	int size;
	BST()
	{
		root = NULL;
		size = 0;
	}

	TNode<T>* insert(TNode<T>*& root, T v)
	{
		TNode<T>* Nnode = new TNode<T>(v);
		if (root == NULL)
		{
			root = Nnode;
			size++;
			return root;
		}
		if (v > root->value)
		{
			root->Right = insert(root->Right, v);
		}
		else
		{
			root->Left = insert(root->Left, v);
		}
		return root;
	}

	bool search(TNode<T>* root, int v)
	{
		if (root == NULL)
		{
			return false;
		}
		if (root->value == v)
		{
			return true;
		}
		if (root->value > v)
			return search(root->Left, v);
		if (root->value < v)
			return search(root->Right, v);
	}

	int minValue(TNode<T>* root)
	{
		if (root->Left == NULL)
			return root->value;
		return minValue(root->Left);
	}
	TNode<T>* _delete(TNode<T>* root, T v)
	{
		if (root == NULL)
			return root;
		if (v < root->value)
			root->Left = _delete(root->Left, v);
		else if (v > root->value)
			root->Right = _delete(root->Right, v);
		else
		{
			if (root->Left == NULL and root->Right == NULL)
				return NULL;
			else if (root->Left == NULL)
				return root->Right;
			else if (root->Right == NULL)
				return root->Left;
			int n = minValue(root);
			root->Right = _delete(root->Right, n);
			root->value = n;
		}
		return root;
	}


	void inorder(TNode<T>* root)
	{
		if (root == NULL)
			return;
		inorder(root->Left);
		cout << root->value << " ";
		inorder(root->Right);
	}
	void preorder(TNode<T>* root)
	{
		if (root == NULL)
			return;
		cout << root->value << " ";
		preorder(root->Left);
		preorder(root->Right);
	}

	void postorder(TNode<T>* root)
	{
		if (root == NULL)
			return;
		postorder(root->Left);
		postorder(root->Right);
		cout << root->value << " ";
	}
};


int main()
{
	CPUProcess p1(1, "p1", 10);
	CPUProcess p2(2, "p2", 4);
	CPUProcess p3(3, "p3", 1);
	CPUProcess p4(4, "p4", 5);
	CPUProcess p5(5, "p5", 15);
	QueueLL<CPUProcess> qll;
	qll.execute(p1);
	qll.execute(p2);
	qll.execute(p3);
	qll.execute(p4);
	qll.execute(p5);
	qll.cpuSchedule();
	StackLL<CPUProcess> sll;
	qll.killProcess(&sll);
	qll.killProcess(&sll);
	cout << "--------------------------------------------------------" << endl;
	cout << "stack processes:" << endl<<endl;
	sll.stackOfProcesses();
	sll.lateProcess().printProcessInfo();
	cout << "----------------------BONUS----------------------------------" << endl;
	BST<int>r; r.insert(r.root, 5);
	r.insert(r.root, 3);
	r.insert(r.root, 2);
	r.insert(r.root, 4);
	r.insert(r.root, 1);
	r.insert(r.root, 7);
	r.insert(r.root, 9);
	r.insert(r.root, 8);
	r.insert(r.root, 10);
	r.inorder(r.root);
}
