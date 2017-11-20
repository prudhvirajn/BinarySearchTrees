#include <iostream>
#include <cmath>
#include "main.h"
#include "display.cpp"

#define nullptr 0

using namespace std;

int main(){

	binarySearchTree<int> tree;
	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(1);
	tree.Insert(1);
	try{
		tree.Insert(1);
	}catch(exception &err){
		cout << err.what() << endl;
	}
	Node<int> *p = tree.Find(2);
	cout << p->item << endl;

    srand(time(0));
    for(int i = 0; i < 15; i++){
        int temp = rand() % 100;
        tree.Insert(temp);
    }

	display(&tree);

	return 0;
}
