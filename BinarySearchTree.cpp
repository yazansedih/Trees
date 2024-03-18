
#include <iostream>
#include <cstring>

using namespace std;

const int SIZE = 26;

struct BinaryTree {
    int data;
    BinaryTree* left = nullptr;
    BinaryTree* right = nullptr;
};

class BST {

private:
    BinaryTree* root;

    void insertNode(BinaryTree* &node, int key){
        if (node == nullptr) {
            node = new BinaryTree;
            node->data = key;     
        } 
        else if (key <= node->data) {
            insertNode(node->left, key);
        }
        else if (key > node->data) {
            insertNode(node->right, key);
        }
        return;
    }



    // void removeNode(BinaryTree* &node, int key){
    //     BinaryTree* pre = node;

    //     if(node == nullptr) return;

    //     while(key < node->data){
    //         // pre = node;
    //         node = node->left;

    //     }
    //     while(key > node->data){
    //         // pre = node;
    //         node = node->right;
    //     }
  
    //     BinaryTree* successor = nullptr;
    //     bool left = false;

    //     if(node->left != nullptr){
    //         successor = maxNode(node->left);
    //         left = true;
    //     }
    //     else if(node->right != nullptr){
    //         successor = minNode(node->right);
    //     }
    //     else {
    //         successor = nullptr;
    //         delete node;
    //         node = successor;
    //     }

    //     if(successor != nullptr) {
    //         node = successor;
    //         delete successor;
    //         successor = nullptr;
    //     }
    // }
    void removeNode(BinaryTree* &node, int key) {
        BinaryTree* current = node;
        BinaryTree* parent = nullptr;

        if (current == nullptr) {
            return;
        }

        // Traverse the tree to find the node with the given key
        while (current != nullptr && key != current->data) {
            parent = current;
            if (key < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // Node with the key is found, now handle deletion
        if (current->left == nullptr) {
            // Node with one child or no child (same logic as before)
            BinaryTree* temp = current->right;
            delete current;
            if (parent == nullptr) {
                node = temp;
            } else if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        } else if (current->right == nullptr) {
            // Node with one child or no child (same logic as before)
            BinaryTree* temp = current->left;
            delete current;
            if (parent == nullptr) {
                node = temp;
            } else if (parent->left == current) {
                parent->left = temp;
            } else {
                parent->right = temp;
            }
        } else {
            // Node with two children
            BinaryTree* successor = minNode(current->right);
            current->data = successor->data;
            removeNode(current->right, successor->data);
        }
    }




    bool searchNode(BinaryTree* node,int key){

        return true;
    }

    int height(BinaryTree *p);

    int nodeCount(BinaryTree *p);
    int leavesCount(BinaryTree *p);


    BinaryTree* maxNode(BinaryTree* node){
        while(node->right != NULL){
            node = node->right;
        }
        cout << node->data << endl;
        return node;
    }

    BinaryTree* minNode(BinaryTree* node){
        while(node->left != NULL){
            node = node->left;
        }
        cout << node->data << endl;
        return node;
    }

    void inorder(BinaryTree *p){
        if(p != NULL)
        {
            inorder(p->left);
            cout<<p->data<<" ";
            inorder(p->right);
        }
    }
    void preorder(BinaryTree *p);
    void postorder(BinaryTree *p);

    void list();
    
public:

    BST() { root = nullptr;}

	void insert(int key){
        insertNode(root, key);
    }
    void remove(int key){
        removeNode(root, key);
    }
    bool search(int);
	

    bool isEmpty();


	void inorderTraversal(){
        inorder(root);
        cout << endl;
    }
	void preorderTraversal();
	void postorderTraversal();
	int treeHeight();
	int treeNodeCount();
	int treeLeavesCount();
    void printList(){

    }

};


int main(){

    cout << "Hello\n";
    BST tree;

    tree.printList();
    while(1){ 
        int value;
        char command[20];
        cin >> command;

        if (strcmp(command,"insert") == 0)
        {
            cin >> value;
            tree.insert(value);
            tree.inorderTraversal();
        } 
        else if (strcmp(command,"delete") == 0)
        {
            cin >> value;
            tree.remove(value);
            tree.inorderTraversal();
        } 
        
    }



    return 0;
}