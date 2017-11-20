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
};

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
		int size, height;
		Node<T>* root;

	public:
		binarySearchTree() : size(0), height(0), root() {}

		/**Accepts in value and inserts in the tree if the value does not exist**/
		void insert(T value){
			//If tree is empty then add at the root
			if(root == NULL){
				//cout << "Creating a new tree" << endl;
				root = new Node<T>;
				root->item = value;
				size++;
				return;
			}

			Node<T>* ptr = root;
			int depth = 1; // track the depth of the new node
			while(true){
				if(value == ptr->item){
					alreadyThere err;
					throw(err);
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
				ptr->rnode = new Node<T>;
				ptr->rnode->item = value;
			}else{
				ptr->lnode = new Node<T>;
				ptr->lnode->item = value;
			}
			size++;
			balance();
		}

		/**Accepts a value and finds it in the binary search tree.
		If found then returns pointer to that node, else return null pointer.**/
		Node<T>* find(T value){
			if(root == NULL){
				return nullptr;
			}
			Node<T>* ptr = root;
			if(value == ptr->item){
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

		// fail

		// void rotateLeft(Node<T>** ptr){
		// 	//If there is no node at the given pointer
		// 	if(*ptr == NULL)
		// 		return;
		// 	//If the node has no right node then return
		// 	if((*ptr)->rnode == NULL)
		// 		return;
		// 	// store rnode as temp
		// 	Node<T>* temp = (*ptr)->rnode;
		// 	// make rnode of current equal to lnode of rnode
		// 	(*ptr)->rnode = (*ptr)->rnode->lnode;
		// 	// make lnode of rnode equal to current
		// 	temp->lnode = *ptr;
		// 	// make current value equal to temp
		// 	*ptr = temp;
		// }
		//
		// void rotateRight(Node<T>** ptr){
		// 	//If there is no node at the given pointer
		// 	if(*ptr == NULL)
		// 		return;
		// 	//If the node has no right node then return
		// 	if((*ptr)->lnode == NULL)
		// 		return;
		// 	// store lnode as temp
		// 	Node<T>* temp = (*ptr)->lnode;
		// 	// make lnode of current equal to rnode of lnode
		// 	(*ptr)->lnode = (*ptr)->lnode->rnode;
		// 	// make rnode of lnode equal to current
		// 	temp->rnode = *ptr;
		// 	// make current value equal to temp
		// 	*ptr = temp;
		// }

			/* This function traverse the skewed binary tree and
		stores its nodes pointers in vector nodes[] */
		void storeBSTNodes(Node<T>* root, vector<Node<T>*> &nodes){
			// Base case
			if (root==NULL)
			    return;
			// Store nodes in Inorder (which is sorted
			// order for BST)
			storeBSTNodes(root->lnode, nodes);
			nodes.push_back(root);
			storeBSTNodes(root->rnode, nodes);
		}
		/* Recursive function to construct binary tree */
		Node<T>* buildTreeUtil(vector<Node<T>*> &nodes, int start, int end){
			// base case
			if (start > end)
			    return NULL;
			/* Get the middle element and make it root */
			int mid = (start + end)/2;
			Node<T>* root = nodes[mid];

			/* Using index in Inorder traversal, construct
			   left and right subtress */
			root->lnode = buildTreeUtil(nodes, start, mid-1);
			root->rnode = buildTreeUtil(nodes, mid+1, end);

			return root;
		}

		// This functions converts an unbalanced BST to
		// a balanced BST
		void balance(){
			// Store nodes of given BST in sorted order
			vector<Node<T>*> nodes;
			storeBSTNodes(root, nodes);

			// Constucts BST from nodes[]
			int n = nodes.size();
			root = buildTreeUtil(nodes, 0, n-1);
		}

		void deleteItem(T value){
			Node<T>* ptr = this->find(value);
			if(ptr){
				if(ptr->lnode){
					*ptr = *ptr->lnode;
					delete ptr->lnode;
					ptr->lnode = NULL;
				} else if(ptr->rnode){
					*ptr = *ptr->rnode;
					delete ptr->rnode;
					ptr->rnode = NULL;
				} else {
					delete ptr;
					ptr = NULL;
				}
			}else{
				notFound err;
				throw(err);
			}
			return;
		}

		int getHeight(){
			return height_helper(root);
		}

		int height_helper(Node<T>* ptr){
			if(!ptr) return 0;
			return max(1 + height_helper(ptr->lnode), 1 + height_helper(ptr->rnode));
		}

		Node<T>** getRoot(){
			return &root;
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

		~binarySearchTree(){
			emptyTree();
		}
};

#include "display.cpp"

int main(){

	binarySearchTree<int> tree;

    // srand(time(0));
    // for(int i = 0; i < 10; i++){
    //     int temp = rand() % 20;
	// 	try{
	// 		tree.insert(temp);
	// 	}catch(exception &err){
	// 		cout << err.what() << endl;
	// 	}
    // }

	tree.insert(10);
	tree.insert(1);
	tree.insert(0);
	tree.insert(17);
	tree.insert(5);
	tree.insert(14);
	tree.insert(19);


	tree.deleteItem(0);


	display(&tree);


	// cout << "Size: " << tree.getSize() << endl;
	// display(&tree);
	//
	// tree.emptyTree();
	// cout << "Size: " << tree.getSize() << endl;
	// if(tree.getRoot() == NULL){
	// 	cout << "Success" << endl;
	// }
}
