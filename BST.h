#pragma once
#include <iostream>

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template <typename DataType>
class BST
{
public:
    
    BST();      // Declaration of the constructor


    bool empty() const;       // Declaration of the function that tests if the BST is empty or not


    bool search(const DataType& item) const; // Declaration of the search function


    void insert(const DataType& item); // Declaration of the insert function


    void remove(const DataType& item); // Declaration of the remove function


    void preorder(ostream& out) const;   // Declaration of the preorder function which will preorderly traverse
    
    
    void leafCount(void) const;         // Declaration of the leafCount function which will count the leaves

    
    void nodeSibling(const DataType& item) const; // Declaration of the nodeSibiling function which will find and output the siblings of each node. 

private:
    
    class BinNode
    {
    public:
        DataType data;
        BinNode* left;
        BinNode* right;

        BinNode()                           // Default constructor for the BinNode class
            : left(0), right(0)
        {}

        BinNode(DataType item)                  // Explicit value constructor for the BinNode class
            : data(item), left(0), right(0)
        {}

    };

    typedef BinNode* BinNodePointer;

    
    void search2(const DataType& item, bool& found, BinNodePointer& locptr, BinNodePointer& parent) const; //Private function member that is used to search for nodes. Used in other function declarations.

    void preorderAux(ostream& out, BST<DataType>::BinNodePointer subtreePtr) const; // Auxilary function that is called by the preorder function.

    void leafcountAux(BST<DataType>::BinNodePointer subtreeRoot, int& count) const; // Auxilary function that is called by the leafCount function.

   
    BinNodePointer myRoot; // Data member

}; 


template <typename DataType>        // Definition of the BST constructor
inline BST<DataType>::BST()
    : myRoot(0)
{}

template <typename DataType>
inline bool BST<DataType>::empty() const        // Definition of the empty function that tests if the BST is empty or not
{
    return myRoot == 0;
}


template <typename DataType>
bool BST<DataType>::search(const DataType& item) const      // Definition of the search function
{
    BST<DataType>::BinNodePointer locptr = myRoot;
    bool found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // If statement that checks if the item entered is less.
            locptr = locptr->left;      // Goes down to the left if it is less.
        else if (locptr->data < item)  // Else if statement that checks if the item entered is greater.
            locptr = locptr->right;     // Goes down to the right if it is greater.
        else                           // Else statement that means the item is found
            found = true;
    }
    return found;                         // Returns that the node is found
}


template <typename DataType>
inline void BST<DataType>::insert(const DataType& item)         // Definition of the insert function
{
    BST<DataType>::BinNodePointer
        locptr = myRoot,   
        parent = 0;        
    bool found = false;     
    while (!found && locptr != 0)           // Similar while loop as the search function 
    {
        parent = locptr;
        if (item < locptr->data)       // If statement that checks if the item entered is less.
            locptr = locptr->left;      // Goes down to the left if it is less.
        else if (locptr->data < item)  // Else if statement that checks if the item entered is greater.
            locptr = locptr->right;     // Goes down to the right if it is greater.
        else                           // Else statement that means the item is found
            found = true;
    }
    if (!found)                         // If the item is not found, begin to go through the code to insert a node.
    {                                 
        locptr = new BST<DataType>::BinNode(item);              // Creates a new node containing an item
        if (parent == 0)               
            myRoot = locptr;           
        else if (item < parent->data)  // This will check if the item is less than the parent, and insert to the left if so
            parent->left = locptr;
        else                           // Otherwise, it will insert to the right.
            parent->right = locptr;
    }
    else
        cout << "" << item << " is already in the tree" << endl;        // Else statement that will tell the user that the item they are trying to insert in the tree is already present. 
    
}


template <typename DataType>
void BST<DataType>::remove(const DataType& item)                            // Definition of the remove function
{
    bool found;                      
    BST<DataType>::BinNodePointer
        x,                       
        parent;                
    search2(item, found, x, parent);

    if (!found)                                             // First check to see if the item the user entered is found
    {
        cout << "" << item << " is not found in the BST" << endl;       // If not found, output that the item they entered is not found.
        return;
    }
    
    if (x->left != 0 && x->right != 0)
    {                               
   
        BST<DataType>::BinNodePointer xSucc = x->right;             // Created to find x's successor & parent
        parent = x;                   
        while (xSucc->left != 0)      // Goes down and to the left
        {
            parent = xSucc;
            xSucc = xSucc->left;
        }

        x->data = xSucc->data;          // The node that will ultimately be removed.
        x = xSucc;
    } 

    
    BST<DataType>::BinNodePointer       // Case when the node has either 0 or 2 children. 
        subtree = x->left;             // Pointer to the subtrees, left and right.
    if (subtree == 0)
        subtree = x->right;
    if (parent == 0)                  // The root gets removed
        myRoot = subtree;
    else if (parent->left == x)       // Points to the left child of the parent
        parent->left = subtree;
    else                              // Points to the right child of the parent
        parent->right = subtree;
    delete x;
    cout << "" << item <<  " is deleted" << endl;   // Outputting the item that the user calls to get deleted
}


template <typename DataType>
void BST<DataType>::search2(const DataType& item, bool& found, BST<DataType>::BinNodePointer& locptr, BST<DataType>::BinNodePointer& parent) const  // Definition of the search2 function
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // If statement that checks if the item entered is less.
        {
            parent = locptr;            // Will go down and to the left if so
            locptr = locptr->left;
        }
        else if (locptr->data < item)  // Else if statement that checks if the item entered is greater.
        {
            parent = locptr;            // Will go down and to the right if so
            locptr = locptr->right;
        }
        else                            // Else statement that means the item is found
            found = true;
    }
}


template <typename DataType>
inline void BST<DataType>::preorder(ostream &out) const     // Definition of the preorder function
{
    preorderAux(out, myRoot);                               // Calls the auxilary function.
    
}

template <typename DataType>
void BST<DataType>::preorderAux(ostream& out, BST<DataType>::BinNodePointer subtreeRoot) const      // Definition of the preorder auxilary function
{
    if (subtreeRoot != 0)                       // First checks if subtreeRoot is not NULL. If passes, go through with the rest of the operation.
    {       

        out << subtreeRoot->data << "  ";       // V operation

        if (subtreeRoot->left != 0)                             // Checks if the left node is NULL.
                                                                // \t are tabs for formatting outputs.
            cout << "\t\t\t\t " << subtreeRoot->left->data;     // Prints the info of the left child.
        else
            cout << "\t\t\t\tNIL ";                             // If it is NULL, print 'NIL'

        if (subtreeRoot->right != 0)                                        // Checks if the right node is NULL.
            cout << "\t\t\t\t " << subtreeRoot->right->data << endl;        // Prints the info of the right child.
        else
            cout << "\t\t\t\tNIL" << endl;                              

        preorderAux(out, subtreeRoot->left);    // L operation
        preorderAux(out, subtreeRoot->right);   // R operation

    }

}

template <typename DataType>
void BST<DataType>::leafCount(void) const {
    
    int leaves = 0;                                 // Create a variable called leaves that starts at 0

    leafcountAux(myRoot, leaves);                                   // Calling the auxilary function that is essentially the counter. 
    cout << "There are " << leaves << " number of leaves in the BST." << endl;      // Outputs the number of leaves.

}


template <typename DataType>
void BST<DataType>::leafcountAux(BST<DataType>::BinNodePointer subtreeRoot, int& count) const {        // Definition of the leafcount auxilary function
    if (subtreeRoot != 0) {                                                                                 // Check to make sure that subtreeRoot is not NULL.

        if (subtreeRoot->left == 0 && subtreeRoot->right == 0 && subtreeRoot != myRoot)
            ++count;                                                                        // If the conditions of the if statement are met, increment the counter. 
        
        leafcountAux(subtreeRoot->left, count);                             // Traversing the left subtree    
           
        leafcountAux(subtreeRoot->right, count);                        // Traversing the right subtree 

    }
}

template <typename DataType>
void BST<DataType>::nodeSibling(const DataType& item) const{

    BST<DataType>::BinNodePointer
        locptr = myRoot,   
        parent = 0;        
    bool found = false;

    while (!found && locptr != 0) {             // Same loop used in previous functions
        
        if (item < locptr->data) {              // If statement that checks if the item entered is less.
            parent = locptr;                    
            locptr = locptr->left;              // Will go down and to the left if so
        }
        else if (locptr->data < item) {         // Else if statement that checks if the item entered is greater.
            parent = locptr;
            locptr = locptr->right;             // Will go down and to the right if so
        }
        else
            found = true;                    // Else statement that means the item is found
    }
       
    if (found) {                                            // First checker to see if the item is found

        if (parent == 0)                                    // If the root is entered, there will be no sibling.
            cout << "" << item << " has no sibling" << endl;
           
        else if (parent->left != 0 && parent->right != 0) {             // Checking that the parent pointing to left and right is not NULL.
            
            if (item == parent->left->data)
                cout << "The sibling of " << item << " is " << parent->right->data << endl;             // Outputting the sibling of the right node.

            if (item == parent->right->data)
                cout << "The sibling of " << item << " is " << parent->left->data << endl;              // Outputting the sibling of the left node.
        }
        else
            cout << "" << item << " has no sibling." << endl;                                       // Else statement that tells the user that there is no sibling for the entered node.
    }

    else
        cout << "Invalid entry, " << item << " is not in the BST" << endl;      // Else statement to the main if statement that tells the user that what they entered is not found, meaning it is not in the BST.
}






#endif
