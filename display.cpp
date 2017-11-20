#include <cmath>
#include <iomanip>
#include <vector>

void getLine(const Node<int> *root, int depth, vector<int>& vals){
    int placeholder = -1;
    if(depth <= 1 && root != nullptr){
        vals.push_back(root->value);
        return;
    }
    if(root->left != nullptr){
        getLine(root->left, depth-1, vals);
    } else if(depth-1 <= 1){
        vals.push_back(placeholder);
    } else {
        Node<int> temp;
        getLine(&temp, depth-1, vals);
    }

    if(root->right != nullptr){
        getLine(root->right, depth-1, vals);
    } else if(depth-1 <= 1){
        vals.push_back(placeholder);
    } else {
        Node<int> temp;
        getLine(&temp, depth-1, vals);
    }

}

void printRow(const Node<int> *p, const int height, int depth){
    int placeholder = -1;
    vector<int> vec;
    getLine(p, depth, vec);

    int indent = pow(2, height-depth) - 1;
    for(int i = 0; i < indent; i++) cout << "  ";
    int inner_spacing = pow(2, height-depth+1) - 1;
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] != placeholder){
            cout << setw(2) << vec[i];
        } else {
            cout << "  ";
        }
        for(int i = 0; i < inner_spacing; i++) cout << "  ";
    }
    cout << endl;
}

void display(binarySearchTree<int>* tree){
    int height = tree->getHeight();
    cout << "Got height = " << height << endl;
    for (int i = 1; i <= height; i++){
        printRow(tree->getRoot(), height, i);
    }
}
