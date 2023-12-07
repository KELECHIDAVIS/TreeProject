#include <iostream>
#include "Node.h"
#include <queue>
using namespace std;  

Node* createNode ( int data ); 


//balance and rotation functions 
int calcBalance(Node* root); 
int height (Node* root ); 
Node* balance(Node * root ); 
Node* findPredecessor(Node* root); 
Node* llRotation(Node* root); 
Node* lrRotation(Node* root); 
Node* rrRotation(Node* root); 
Node* rlRotation(Node* root); 
Node* insert(Node* root, int  data); 
void deleteNode (Node* &root, int data); 
// preorder , postorder, level order, in order traversal (11/27 lec)
void printLevelOrder(Node* root); //breadth first 
void printInOrder(Node* root ); 
void printPreOrder(Node* root ); 
void printPostOrder(Node* root ); 


int main () 
{
    Node *root                = createNode(8);
    root->left                = createNode(4);
    root->right               = createNode(12);
    root->left->left          = createNode(2);
    root->left->right         = createNode(6);
    root->right->left         = createNode(10);
    root->right->right        = createNode(14);
    root->left->left->left    = createNode(1);
    root->left->left->right   = createNode(3);
    root->left->right->left   = createNode(5);
    root->left->right->right  = createNode(7);     
    root->right->left->left   = createNode(9);
    root->right->left->right  = createNode(11);
    root->right->right->left  = createNode(13);
    root->right->right->right = createNode(15);     

    cout<<"Printing In Level Order: " ;  
    printLevelOrder(root); 
    cout<<endl; 

    cout<<"Printing In Pre-Order: " ;  
    printPreOrder(root); 
    cout<<endl; 

    cout<<"Printing In In-Order: " ;  
    printInOrder(root); 
    cout<<endl; 

    cout<<"Printing In Post-Order: " ;  
    printPostOrder(root); 
    cout<<endl; 


    cout<<"Insert "<< 20<<endl ;
    insert(root , 20); 
    cout<< "Printing Level After Insertion: "; 
    printLevelOrder(root); 


    cout<<endl<<"Delete "<< 15 <<endl ;
    deleteNode(root , 15); 
    cout<< "Printing Level After Deletion: "; 
    printLevelOrder(root); 

    return 0 ; 
}

Node* llRotation(Node* root)
{
    Node *temp;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}
Node* lrRotation(Node* root)
{
    Node *temp;
    temp = root->left;
    root->left = rrRotation (temp);
    return llRotation (root);
}
Node* rrRotation(Node* root)
{
    Node* temp;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
Node* rlRotation(Node* root)
{
    Node *temp;
    temp = root->right;
    root->right = llRotation (temp);
    return rrRotation (root);
}

Node* createNode ( int data )
{
    Node* newNode = new Node(); 
    newNode->data = data ; 
    return newNode ; 
}
int height ( Node* root )
{
    int h = 0;
    if (root != NULL){
        int l_height = height (root->left);
        int r_height = height (root->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int calcBalance(Node* root )
{
    return height(root->left ) - height(root->right);  
}

Node* insert(Node* root , int data )    {
    if (root == NULL){
        root = new Node;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        return root;
    }else if (data < root->data){
        root->left = insert(root->left, data);
        root = balance (root);
    }else if (data >= root->data){
        root->right = insert(root->right, data);
        root = balance (root);
    }
    return root;
}

Node* balance(Node* root)
{
    int balanceFactor = calcBalance (root);
    if (balanceFactor > 1){
        if (calcBalance (root->left) > 0)
            root = llRotation (root);
        else
            root = lrRotation (root);
    }else if (balanceFactor < -1){
        if (calcBalance (root->right) > 0)
            root = rlRotation (root);
        else
            root = rrRotation (root);
    }
    return root;
}

Node* findPredecessor(Node* root)
{
    while (root->right != nullptr) {
		root = root->right;
	}
	return root;
}
//replace the node with it's inorder predecessor 
void deleteNode (Node* &root, int data)
{
    // base case: the key is not found in the tree
	if (root == nullptr) {
		return ;
	}

	// if the given key is less than the root node, recur for the left subtree
	if (data < root->data) {
		deleteNode(root->left, data);
	}

	// if the given key is more than the root node, recur for the right subtree
	else if (data > root->data) {
		deleteNode(root->right, data);
	}

	// key found
	else {
		// Case 1: node to be deleted has no children (it is a leaf node)
		if (root->left == nullptr && root->right == nullptr)
		{
			// deallocate the memory and update root to null
			delete root;
			root = nullptr;
		}

		// Case 2: node to be deleted has two children
		else if (root->left && root->right)
		{
			// find its inorder predecessor node
			Node* predecessor = findPredecessor(root->left);

			// copy value of the predecessor to the current node
			root->data = predecessor->data;

			// recursively delete the predecessor. Note that the
			// predecessor will have at most one child (left child)
			deleteNode(root->left, predecessor->data);
		}

		// Case 3: node to be deleted has only one child
		else {
			// choose a child node
			Node* child = (root->left)? root->left: root->right;
			Node* curr = root;

			root = child;

			// deallocate the memory
			delete curr;
		}
	}
}

void printPreOrder(Node* root )
{
    if(root == nullptr)
        return; 

    cout<<root->data<<" "; // visit node 

    printPreOrder(root->left); //left

    printPreOrder(root->right); //right 

} 
void printInOrder(Node* root )
{
    if(root == nullptr)
        return; 


    printInOrder(root->left); //left

    cout<<root->data<<" "; // visit node 

    printInOrder(root->right); //right 

}  
void printPostOrder(Node* root )
{
    if(root == nullptr)
        return; 


    printPostOrder(root->left); //left
    printPostOrder(root->right); //right 
    cout<<root->data<<" "; // visit node 
}

void printLevelOrder(Node* root)
{
    queue<Node*> nodeQueue; 

    nodeQueue.push(root); 

    while(!nodeQueue.empty())
    {
        Node* current = nodeQueue.front(); 
        nodeQueue.pop(); 

        cout<<current->data<<" "; 

        // add children  
        if(current->left)
            nodeQueue.push(current->left); 
        if(current->right)
            nodeQueue.push(current->right); 

    }
}