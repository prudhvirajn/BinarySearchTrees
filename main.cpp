#include <iostream>
#include <cmath>
#include "binarySearchTrees.h"
//#include "display.cpp"

#define nullptr 0

using namespace std;

int main(){

	binarySearchTree<int> tree;
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(1);
	Node<int>* arr = tree.getDescendingOrder();
	for(int i = 0; i < tree.Size(); i++){
		cout << arr[i].value << endl;
	}
	try{
		tree.Insert(1);
	}catch(exception &err){
		cout << err.what() << endl;
	}
	Node<int> *p = tree.Find(2);
	cout << p->value << endl;
	p = tree.Find(2);
	cout << tree.getHeight() << endl;
	if(p == nullptr){
		cout << "Not found" << endl;
	}
	return 0;
}
