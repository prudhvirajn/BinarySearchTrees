
#include<iostream>
using namespace std;

class alreadyThere : public exception{
	virtual const char* what() const throw(){
		return "The item already exists";
	}
};

template<typename T>
class Node
{
public:
	T value;
	int h; // The depth of the node in the tree
	Node *left, *right;
};

template<typename T>
class binarySearchTrees
{
private:
	Node <T> *R, *NIL; // The Root is private to restrict direct access to the pointers
	int size;
public:
	binarySearchTrees()
	{
		Init(); // Initialize pointers when constructor is called
	}

	// This public method Search calls for the private method Search, in order not to give user access to the Root
	Node<T>* Find(T val)
	{
		return Find(R, val);
	}

	// The same pattern of restricting access is here
	void Insert(T val)
	{
		R = Insert(R, val);
	}

	void Delete(T val)
	{
		R = Delete(R, val);
	}

	int getSize(){
		return size;
	}

	int getHeight(){
		return R->h + 1;
	}

	Node<T>* getAscendingOrder(){

	}

	// In-Order traversal, prints the elements in ascending order
	void PrintInOrderTraversal(ostream &outputstream)
	{
		PrintInOrderTraversal(outputstream, R);
	}

	// Pre-Order Traversal
	void PrintPreOrderTraversal(ostream &outputstream)
	{
		PrintPreOrderTraversal(outputstream, R);
	}

	// Post-Order Traversal
	void PrintPostOrderTraversal(ostream &outputstream)
	{
		PrintPostOrderTraversal(outputstream, R);
	}

	// When the destructor is called, it invokes the method DeallocMemory which recursively, in a bottom-up style, deallocs the dynamic allocated memory
	~AVL()
	{
		DeallocMemory(R);
	}

private:
	// Initialization of the Tree
	// Create Root and NIL node, in order not to acces unallocated memory
	void Init()
	{
		R = NIL = new Node<T>;
		NIL->h = 0;
		NIL->left = NIL->right = NULL;
		size = 0;
	}

	// Search the value T in subtree with the root in node N, 
	Node<T>* Find(Node<T> *N, T val)
	{
		if (N == NIL) return nullptr;

		if (N->value == val) return N;

		if (val < N->value)
			return Search(N->left, val);
		else
			return Search(N->right, val);
	}

	// After insertion, call balance method, to keep the tree balanced
	Node<T>* Insert(Node<T> *N, T val)
	{
		if (N == NIL)
		{
			N = new Node<T>;
			N->value = val;
			N->left = N->right = NIL;
			N->h = 1;
			size++;
			return N;
		}

		if(val == N->value){
			alreadyThere err;
			throw(err);
		}

		if (val <= N->value) N->left = Insert(N->left, val);
		else N->right = Insert(N->right, val);

		return Balance(N);
	}

	// Delete the value T in the subtree with root in node N
	Node<T>* Delete(Node<T> *N, T val)
	{
		Node<T> *t;
		if (N == NIL) return N;
		if (N->value == val)
		{
			if (N->left == NIL || N->right == NIL)
			{
				if (N->left == NIL) t = N->right;
				else t = N->left;
				delete N;
				size--;
				return t;
			}
			else
			{
				for (t = N->right; t->left != NIL; t = t->left);
				N->value = t->value;
				N->right = Delete(N->right, t->value);
				return Balance(N);
			}
		}

		if (val < N->value) N->left = Delete(N->left, val);
		else N->right = Delete(N->right, val);

		return Balance(N);
	}


	// Updadets the depth of the node N in the tree
	void GetHeight(Node<T> *N)
	{
		N->h = 1 + Max(N->left->h, N->right->h);
	}

	// The Rotate left operation, for balancing the tree
	Node<T>* RotateLeft(Node<T> *N)
	{
		Node<T> *t = N->left;
		N->left = t->right;
		t->right = N;
		GetHeight(N);
		GetHeight(t);

		return t;
	}

	Node<T>* RotateRight(Node<T> *N)
	{
		Node<T> *t = N->right;
		N->right = t->left;
		t->left = N;
		GetHeight(N);
		GetHeight(t);

		return t;
	}

	// Balance the nodes in the way that no two subtrees of a node have their maximum depth with a difference bigger than 1
	Node<T>* Balance(Node<T> *N)
	{
		GetHeight(N);

		if (N->left->h > N->right->h + 1)
		{
			if (N->left->right->h > N->left->left->h)
				N->left = RotateRight(N->left);
			N = RotateLeft(N);
		}
		else
		if (N->right->h > N->left->h + 1)
		{
			if (N->right->left->h > N->right->right->h)
				N->right = RotateLeft(N->right);
			N = RotateRight(N);
		}

		return N;
	}

	void PrintInOrderTraversal(ostream &outputstream, Node<T> *N)
	{
		if (N == NIL) return;
		PrintInOrderTraversal(outputstream, N->left);
		outputstream << N->value << " ";
		PrintInOrderTraversal(outputstream, N->right);
	}

	void PrintPreOrderTraversal(ostream &outputstream, Node<T> *N)
	{
		if (N == NIL) return;
		outputstream << N->value << " ";
		PrintPreOrderTraversal(outputstream, N->left);
		PrintPreOrderTraversal(outputstream, N->right);
	}

	void PrintPostOrderTraversal(ostream &outputstream, Node<T> *N)
	{
		if (N == NIL) return;
		PrintPostOrderTraversal(outputstream, N->left);
		PrintPostOrderTraversal(outputstream, N->right);
		outputstream << N->value << " ";
	}

	// Recursively destroys the tree
	void DeallocMemory(Node<T> *N)
	{
		if (N == NIL) return;
		DeallocMemory(N->left);
		DeallocMemory(N->right);
		delete N;
	}
};