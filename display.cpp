#include <cmath>
#include <iomanip>
#include <vector>

void getLine(const Node<int> *root, int depth, vector<int>& vals){
    int placeholder = -1;
    if(depth <= 1 && root != nullptr){
        vals.push_back(root->item);
        return;
    }
    if(root->lnode != nullptr){
        getLine(root->lnode, depth-1, vals);
    } else if(depth-1 <= 1){
        vals.push_back(placeholder);
    } else {
        Node<int> temp;
        getLine(&temp, depth-1, vals);
    }

    if(root->rnode != nullptr){
        getLine(root->rnode, depth-1, vals);
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

    // int indent = pow(2, height-depth);
    // for(int i = 0; i < indent; i++) cout << "  ";
    // bool toggle = true; // start with left
    // if(vec.size() > 1){
    //     for(int v : vec){
    //         if(toggle)
    //             cout << "/ ";
    //         else
    //             cout << " \\";
    //         toggle = !toggle;
    //     }
    //     cout << endl;
    // }

    int indent = pow(2, height-depth) - 1;
    for(int i = 0; i < indent; i++) cout << "  ";
    int inner_spacing = pow(2, height-depth+1) - 1;
    for(int v : vec){
        if(v != placeholder){
            cout << setw(2) << v;
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
