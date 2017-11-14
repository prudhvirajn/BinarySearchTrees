#include <iostream>
#include <cmath>

using namespace std;

class alreadyThere : public exception{
	virtual const char* what() const throw(){
		return "The item already exists";
	}
};

class notFound : public exception{
	virtual const char* what() const throw(){
		return "The value was not found";
	}
}

//Node template class to store values and pointer to the left and right sub trees
template <class T>
struct Node{
	T item;
	Node* lnode;
	Node* rnode;
	Node() : lnode(), rnode() {}
};


template <class T>
class binarySearchTree{
	private:
		int size;
		Node<T>* root;

	public:
		binarySearchTree(){
			size = 0;
			root = NULL;
		}

		/**Accepts in value and inserts in the tree if the value does not exist**/
		void insert(T value){
			//If tree is empty then add at the root
			if(root == NULL){
				//cout << "Creating a new tree" << endl;
				root = new Node<T>();
				root->item = value;
				size++;
				return;
			}

			Node<T>* ptr = root;

			while(1){
				if(value == ptr->item){
<<<<<<< HEAD
					alreadyThere err;
					throw(err);
=======
					// throw("This value already exists in the binary search tree");
					return;
>>>>>>> 2d659c099af9d41219aed66a26c1f6471067367c
				}else if(value < ptr->item){
					if(ptr->lnode){
						ptr = ptr->lnode;
					}else{
						break;
					}
				}else{
					if(ptr->rnode){
						ptr = ptr->rnode;
					}else{
						break;
					}
				}
			}

			if(value > ptr->item){
				ptr->rnode = new Node<T>();
				ptr->rnode->item = value;
			}else{
				ptr->lnode = new Node<T>();
				ptr->lnode->item = value;
			}
			size++;
		}

		/**Accepts a value and finds it in the binary search tree.
		If found then returns pointer to that node, else return null pointer.**/ 
		Node<T>* find(T value){
			//If tree is empty then add at the root
			if(root == NULL){
				return nullptr;
			}

			Node<T>* ptr = root;
			if(value == ptr->item){
				//cout << "Found item" << endl;
				return ptr;
			}

			//If tree is not empty then traverse until you find the appropiate terminating node
			while(ptr->lnode || ptr->rnode){
				if(value == ptr->item){
					return ptr;
				}else if(value > ptr->item){
					if(ptr->rnode){
						ptr = ptr->rnode;
					}else{
						return nullptr;
					}
				}else{
					if(ptr->lnode){
						ptr = ptr->lnode;
					}else{
						return nullptr;
					}
				}
			}
			if(ptr->item == value){
				return ptr;
			}
			return nullptr;
		}

<<<<<<< HEAD
		void deleteItem(T value){
			Node<T>* ptr = this->find(value);
			if(ptr){
				//Do Something
			}else{
				notFound err;
				throw(err);
			}
			return;
=======
		int getHeight(){
			return log2(size) + 1;
		}

		Node<T>* getRoot(){
			return root;
>>>>>>> 2d659c099af9d41219aed66a26c1f6471067367c
		}
};

#include "display.cpp"

int main(){
	binarySearchTree<int> tree;
<<<<<<< HEAD
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	tree.insert(1);
	try{
		tree.insert(1);
	}catch(exception &err){
		cout << err.what() << endl;
	}
	Node<int> *p = tree.find(2);
	cout << p->item << endl;
=======
    srand(time(0));
    for(int i = 0; i < 15; i++){
        int temp = rand() % 100;
        tree.insert(temp);
    }

	display(&tree);
	// binarySearchTree<int> tree;
	// tree.insert(2);
	// tree.insert(3);
	// tree.insert(1);
	// tree.insert(1);
	// Node<int> *p = tree.find(2);
	// cout << p->item << endl;


>>>>>>> 2d659c099af9d41219aed66a26c1f6471067367c
	return 0;
}
