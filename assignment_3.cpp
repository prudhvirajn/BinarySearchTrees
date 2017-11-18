#include <iostream>
#include <cmath>

#define nullptr 0

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
};

//Node template class to store values and pointer to the left and right sub trees
template <class T>
struct Node{
	T item;
	Node* lnode;
	Node* rnode;
	int balanceFactor;
	Node() : lnode(), rnode() {}
};


template <class T>
class binarySearchTree{
	private:
		int size, height;
		Node<T>* root;

	public:
		binarySearchTree(){
			size = 0;
			height = 0;
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
				height++;
				return;
			}

			Node<T>* ptr = root;
			int depth = 1; // track the depth of the new node
			while(true){
				if(value == ptr->item){
					alreadyThere err;
					throw(err);
					// throw("This value already exists in the binary search tree");
					// alreadyThere err;
					// throw(err);
					return;
				}else if(value < ptr->item){
					if(ptr->lnode){
						ptr = ptr->lnode;
						depth++;
					}else{
						break;
					}
				}else{
					if(ptr->rnode){
						ptr = ptr->rnode;
						depth++;
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
			depth++;
			if(height < depth) height = depth;
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
		
		void rotateLeft(Node<T>* ptr){
			//If there is no node at the given pointer
			if(ptr == NULL) 
				return;
			//If the node is a leaf node then return
			if(ptr->rnode == NULL && ptr->lnode == NULL)
				return;
			//If 
			
		}
	

		void deleteItem(T value){
			Node<T>* ptr = this->find(value);
			if(ptr){
				//Do Something
			}else{
				notFound err;
				throw(err);
			}
			return;
		}

		int getHeight(){
			return height;
		}

		Node<T>* getRoot(){
			return root;
		}

		int getSize(){
			return size;
		}
		
		void emptyTree(){
			if(root == NULL)
				return;
			Node<T>* left = root->lnode;
			Node<T>* right = root->rnode;
			delete root;
			root = NULL;
			size--;
			emptyTreeHelper(left);
			emptyTreeHelper(right);
			return;
		}
		
		void emptyTreeHelper(Node<T>* head){
			if(head == NULL)
				return;
			Node<T>* left = head->lnode;
			Node<T>* right = head->rnode;
			delete head;
			size--;
			emptyTreeHelper(left);
			emptyTreeHelper(right);
			return;
		}
};

#include "display.cpp"

int main(){

	binarySearchTree<int> tree;
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

    srand(time(0));
    for(int i = 0; i < 15; i++){
        int temp = rand() % 100;
        tree.insert(temp);
    }

	display(&tree);
	// binarySearchTree<int> tree;

	 binarySearchTree<int> tree;

	// tree.insert(2);
	// tree.insert(3);
	// tree.insert(1);
	// tree.insert(1);

    srand(time(0));
	for(int i = 0; i < 15; i++){
        int temp = rand() % 30;
        tree.insert(temp);
        cout << " " << temp;
    }
    cout << endl;


	cout << "Size: " << tree.getSize() << endl;
	display(&tree);
	
	tree.emptyTree();
	cout << "Size: " << tree.getSize() << endl;
	if(tree.getRoot() == NULL){
		cout << "Success" << endl;
	}
	//Node<int> *p = tree.find(pdiddy);
	//cout << p->item << endl;

	return 0;
}
