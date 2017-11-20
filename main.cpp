#include <iostream>
#include <cmath>
#include "binarySearchTrees.h"
#include "display.cpp"

#define nullptr 0

using namespace std;

int main(){

	binarySearchTree<int> tree;
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(1);
	display(&tree);
	try{
		tree.Insert(1);
	}catch(exception &err){
		cout << err.what() << endl;
	}
	Node<int> *p = tree.Find(2);
	cout << p->value << endl;
	p = tree.Remove(2);
	Node<int>* ptr = tree.getAscendingOrder();
	for(int i = 0; i < tree.Size(); i++){
		cout << ptr[i].value << "\t";
	}
	cout << endl;
	Node<int> *c = tree.Remove(1);
	p = tree.Find(2);
	ptr = tree.getAscendingOrder();
	for(int i = 0; i < tree.Size(); i++){
		cout << ptr[i].value << "\t";
	}
	cout << endl;
	cout << tree.getHeight() << endl;
	if(p == nullptr){
		cout << "Not found" << endl;
	}
	display(&tree);
	return 0;
}
