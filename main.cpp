#include <iostream>
#include "Node.h"
#include <queue>
using namespace std;  

Node* createNode ( int data ); 
Node* insert(Node* root, int  data); 
Node* deleteNode (Node* root, int data); 


// preorder , postorder, level order, in order traversal (11/27 lec)
void printLevelOrder(Node* root); //breadth first 
void printInOrder(Node* root ); 
void printPreOrder(Node* root ); 
void printPostOrder(Node* root ); 


int main () 
{
    cout <<"First"<<endl; 

    return 0 ; 
}

Node* createNode ( int data )
{
    Node* newNode = new Node(); 
    newNode->data = data ; 
    return newNode ; 
}

Node* insert(Node* root, int  data)
{
    if(root == nullptr)
        return createNode(data); 
    
    if(data>=root->data)
    {
        root->right = insert(root->right, data); 
    }else{
        root->left = insert(root->left, data ) ; 
    }
    return root; 
}

//replace the node with it's inorder predecessor 
Node* deleteNode (Node* root, int data)
{
    // im going to use the binary search deletion function 

    if( root == nullptr) 
        return root ; 

    return root;  
}

void printPreOrder(Node* root )
{
    if(root == nullptr)
        return; 

    cout<<root->data<<" "<<endl; // visit node 

    printPreOrder(root->left); //left

    printPreOrder(root->right); //right 

} 
void printInOrder(Node* root )
{
    if(root == nullptr)
        return; 


    printPreOrder(root->left); //left

    cout<<root->data<<" "<<endl; // visit node 

    printPreOrder(root->right); //right 

}  
void printPostOrder(Node* root )
{
    if(root == nullptr)
        return; 


    printPreOrder(root->left); //left
    printPreOrder(root->right); //right 
    cout<<root->data<<" "<<endl; // visit node 
}

void printLevelOrder(Node* root)
{
    queue<Node*> nodeQueue; 

    nodeQueue.push(root); 

    while(!nodeQueue.empty())
    {
        Node* current = nodeQueue.front(); 
        nodeQueue.pop(); 

        cout<<current->data<<endl; 

        // add children  
        if(current->left)
            nodeQueue.push(current->left); 
        if(current->right)
            nodeQueue.push(current->right); 

    }
}