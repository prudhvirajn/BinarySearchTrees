#include <iostream>
#include <vector>

using namespace std;

/**
* Error class to indicate item is already there in the list
*/
class alreadyThere : public exception{
	virtual const char* what() const throw(){
		return "The item already exists";
	}
};

/**
* Template Node Struct
*/
template <class T>
struct Node
{
	T value;
	int height; 
	Node *left, *right;
	Node() : left(), right() {}
};

template <class T>
class binarySearchTree{
	private:
		int size;
		Node<T>* root;
		Node<T>* temp;

		/** 
		* Rotates right and returns the new parent
		* @param Pointer to the parent node
		*/
		Node<T>* rightRotate(Node<T>* node){
			Node<T>* left = node->left;
			Node<T>* sub_right = node->left->right;

			left->right = node;
			node->left = sub_right;

			updateHeight(node);
			updateHeight(left);

			return left;
		}

		/**
		* Rotates left and returns the new parent
		* @param Pointer to the parent node
		*/
		Node<T>* leftRotate(Node<T>* node){
			Node<T>* right = node->right;
			Node<T>* sub_left = node->right->left;

			right->left = node;
			node->right = sub_left;

			updateHeight(node);
			updateHeight(right);

			return right;
		}

		/**
		* Updates the height value in the node that is passed
		* @param Pointer to a node
		*/ 
		void updateHeight(Node<T>* node){
			node->height = max(getHeight(node->left), getHeight(node->right))+1;
			return;
		}

		/**
		* Returns the height of the sub tree where the node passed is the root of the sub tree
		* @param Pointer to a node
		*/
		int getHeight(Node<T>* node){
			if(node){
				return node->height;
			}
			return 0;
		}

		/**
		* Returns the balancing factor of the node
		* @param Pointer to a node
		*/
		int getBalance(Node<T>* node){
			return getHeight(node->left) - getHeight(node->right);
		}

		/**
		* Balances the node for insertion
		* @param Pointer to a node
		* @param Value for comparison
		*/
		Node<T>* balanceNode(Node<T>* node, int val){
			// If this node becomes unbalanced, then
		    // there are 4 cases
			int balance = getBalance(node);		 
		    // Left Left Case
		    if (balance > 1 && val < node->left->value)
		        return rightRotate(node);
		 
		    // Right Right Case
		    if (balance < -1 && val > node->right->value)
		        return leftRotate(node);
		 
		    // Left Right Case
		    if (balance > 1 && val > node->left->value)
		    {
		        node->left =  leftRotate(node->left);
		        return rightRotate(node);
		    }
		 
		    // Right Left Case
		    if (balance < -1 && val < node->right->value)
		    {
		        node->right = rightRotate(node->right);
		        return leftRotate(node);
		    }
		}

		/**
		* Accepts a value and then creates and returns a new node
		* to the node is returned, else a null pointer is returned
		* @param value of template class
		*/
		Node<T>* newNode(T val){
			Node<T>* node = new Node<T>();
			node->value = val;
			node->height = 1;
			return node;
		}

		/**
		* Accepts a value and a node to begin, then inserts value depending on node
		* to the node is returned, else a null pointer is returned
		* @param value of template class
		* @param Pointer to a parent node
		*/
		Node<T>* Insert(T val, Node<T>* node){
			//If node is null then creates a new node and returns a pointer to the new node
			if(node == NULL){
				size++;
				return newNode(val);
			}
			if(val < node->value){
				//If value less than node then value is inserted in the left sub tree
				node->left = Insert(val, node->left);
			}else if(val > node->value){
				//If value greater than node then value is inserted in the right sub tree
				node->right = Insert(val, node->right);
			}else{
				//Throws an error because value already exists in the tree
				alreadyThere err;
				throw(err);
			}
			updateHeight(node);
			
		 	balanceNode(node, val);
		    /* return the (unchanged) node pointer */
		    return node;
		}

		/**
		* Accepts and finds the value in the sub tree, if found then a pointer
		* to the node is returned, else a null pointer is returned
		* @param value of template class
		* @param Pointer to a parent node
		*/
		Node<T>* Find(T val, Node<T>* node){
			if(node == NULL)
				return nullptr;
			if(node->value == val){
				return node;
			}
			if(val < node->value){
				return Find(val, node->left);
			}
			return Find(val, node->right);
		}

		/**
		* Empties the sub tree
		* @param Pointer to the parent node of the sub tree
		*/
		void EmptyTree(Node<T>*node){
			if(node == NULL)
				return;
			EmptyTree(node->left);
			EmptyTree(node->right);
			delete node;
			return;
		}

		/**
		* Gets the ascending order of a sub tree and appends it to the vector
		* in that sub tree
		* @param vector passed by reference
		* @param Pointer to a parent node
		*/
		void getAscendingOrder(vector<Node<T>*> &vec, Node<T>* parent){
			if(parent->left != NULL){
				getAscendingOrder(vec, parent->left);
			}
			vec.push_back(parent);
			if(parent->right != NULL){
				getAscendingOrder(vec, parent->right);
			}
			return;
		}

		/**
		* Accepts a node and finds, removes and returns the smallest value
		* in that sub tree
		* @param Pointer to a node of type Node<T>
		*/
		Node<T>* minNode(Node<T>* node){
			while(node->left){
				node = node->left;
			}
			return node;
		}

		/**
		* Removes the node containg the value 
		* and returns the newly ordered sub tree after rebalancing it.
		* @param Value to be removed
		* @param Pointer to a node
		*/
		Node<T>* Remove(T val, Node<T>* node){
			if (node == NULL){
				temp = NULL;
				return node;
			}

			if(val < node->value){
				node->left = Remove(val, node->left);
			}else if(val > node->value){
				node->right = Remove(val, node->right);
			}else{
				temp = node;
				if((node->left == NULL) || (node->right == NULL)){
					Node<T>* ptr = node->left ? node->left : node->right;
					size--;				
					if(ptr){
						node = ptr;
					}else{
						return NULL;							
					}
				}else{
					Node<T>* ptr = minNode(node->right);
					node->value = ptr->value;
					ptr->value = val;
					node->right = Remove(val, node->right);
				}
			}
			updateHeight(node);

			int balance = getBalance(node);

			// If this node becomes unbalanced, then there are 4 cases
 
		    // Left Left Case
		    if (balance > 1 && getBalance(node->left) >= 0)
		        return rightRotate(node);
		 
		    // Left Right Case
		    if (balance > 1 && getBalance(node->left) < 0)
		    {
		        node->left =  leftRotate(node->left);
		        return rightRotate(node);
		    }
		 
		    // Right Right Case
		    if (balance < -1 && getBalance(node->right) <= 0)
		        return leftRotate(node);
		 
		    // Right Left Case
		    if (balance < -1 && getBalance(node->right) > 0)
		    {
		        node->right = rightRotate(node->right);
		        return leftRotate(node);
		    }
		 
		    return node;
		}

	public:
		/**
		* Constructor
		*/
		binarySearchTree(){
			root = NULL;
			temp = NULL;
			size = 0;
		}

		/**
		* Inserts a value in the tree
		* @param Value to be inserted
		*/
		void Insert(T val){
			root = Insert(val, root);
			return;
		}

		/**
		* Accepts and finds the value in the tree, if found then a pointer
		* to the node is returned, else a null pointer is returned
		* @param Value to be found
		*/
		Node<T>* Find(T val){
			return Find(val, root);
		}

		/**
		* Removes a value from the tree
		* @param Value to be found
		*/
		Node<T>* Remove(T val){
			temp = NULL;
			root = Remove(val, root);
			return temp;
		}

		/**
		* Returns the size of the tree
		*/
		int Size(){
			return size;
		}

		/**
		* Returns a constant pointer to the root of the tree
		*/
		const Node<T>* getRoot(){
			return root;
		}

		/**
		* Empties the tree
		*/
		void EmptyTree(){
			if(root == NULL)
				return;
			EmptyTree(root->left);
			EmptyTree(root->right);
			delete root;
			root = NULL;
			return;
		}

		/**
		* Gets the ascending order of Nodes in the tree and returns it as an array
		*/
		Node<T>* getAscendingOrder(){
			vector<Node<T>*> vec;
			getAscendingOrder(vec, root);
			Node<T>* arr;
			arr = new Node<T>[size];
			for(int i = 0; i < vec.size(); i++){
				arr[i] = *vec[i];
			}
			return arr;
		}

		/**
		* Gets the descedning order of Nodes in the tree and returns it as an array
		*/
		Node<T>* getDescendingOrder(){
			Node<T>* arr = getAscendingOrder();
			Node<T>* arr2 = new Node<T>[size];
			for(int i = 0; i < size; i++){
				arr2[i] = arr[size-i-1];
			}
			return arr2;
		}

		/**
		* Returns the height of the tree
		*/
		int getHeight(){
			return getHeight(root);
		}

		/**
		* Destructor
		*/
		~binarySearchTree(){
			EmptyTree();
		}
};