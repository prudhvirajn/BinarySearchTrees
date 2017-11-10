#include <iostream>

using namespace std;

template <class T>
struct Node{
	T item;
	Node* lnode;
	Node* rnode;
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

		void insert(T value){
			//If tree is empty then add at the root
			if(root == NULL){
				//cout << "Creating a new tree" << endl;
				root = new Node<T>();
				root->item = value;
				root->lnode = NULL;
				root->rnode = NULL;
				size++;
				return;
			}

			Node<T>* ptr = root;

			while(1){
				if(value == ptr->item){
					throw("This value already exists in the binary search tree");
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

			//If only the root exists in the tree
			if(value > ptr->item){
				//cout << "Creating the first right node" << endl;
				ptr->rnode = new Node<T>();
				ptr->rnode->item = value;
				ptr->rnode->lnode = NULL;
				ptr->rnode->rnode = NULL;
				size++;
			}else{
				//cout << "Creating the first left node" << endl;
				ptr->lnode = new Node<T>();
				ptr->lnode->item = value;
				ptr->lnode->lnode = NULL;
				ptr->lnode->rnode = NULL;
				size++;
			}
			return;
		}

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
};


int main(){
	binarySearchTree<int> tree;
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	//tree.insert(1);
	Node<int> *p = tree.find(2);
	cout << p->item << endl;
	return 0;
}