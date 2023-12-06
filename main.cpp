#include <iostream>
#include "Node.h"

Node* createNode ( int data ); 
Node* insert(Node* root, int  data); 
void deleteNode (Node* root, int data); 


// preorder , postorder, level order, in order traversal (11/27 lec)
void printBFS(Node* root); // level traversal 
void printDFS(Node* root); // depth traversal 


int main () 
{


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

void deleteNode (Node* root, int data)
{

}