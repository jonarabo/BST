#include <iostream>
using namespace std;

#include "BST.h"

int main()
{
	int choice;
	BST<char> charBST;

	while (1) {																						// Creating a while loop to output the menu for the user.

		cout << "-------------------------------MENU-------------------------------" << endl;
		cout << "1. Insert Node(s)" << endl;
		cout << "2. Traverse Preorder" << endl;
		cout << "3. Search BST" << endl;
		cout << "4. Delete Node" << endl;
		cout << "5. Leaf Count" << endl;
		cout << "6. Sibling Of A Node" << endl;
		cout << "7. Quit" << endl;

		cout << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;																		// Telling the user to enter the function they would like to use. 

		switch (choice) {

		case 1:																				// If 1 is selected, the user would like to insert nodes into the BST.
			cout << "You have selected to insert node(s) in the BST" << endl;
			char insert;
			for (;;)
			{
				cout << "Item to insert (~ to stop): ";
				cin >> insert;																// Asking the user to insert the characters 
				if (insert == '~') break;													// If ~ is pressed, the function quits and it goes back to the main menu.
				cout << "Inserted" << endl;
				charBST.insert(insert);														// Calling the insert function.
				
			}
			continue;
			break;
		
		case 2:																				// If 2 is selected, the user would like to see the preorder traversal of the BST.
			cout << "Preorder Traversal of BST:" << endl << endl;							// All formatting			
			cout << "Node Info";
			cout << "\t\t Left Child Info";
			cout << "\t\t Right Child Info" << endl;
			cout << "----------";
			cout << "\t\t ---------------";
			cout << "\t\t ----------------" << endl;
			charBST.preorder(cout);															// Calling the preorder function
			cout << endl;
			continue;
			break;
		
		case 3:																				// If 3 is selected, the user would like to search for an item in the BST.
			cout << "You have selected to search for an item in the BST" << endl;

			for (;;)
			{
				cout << "Enter the item you want to search for: (~ to stop) " << endl;
				cin >> insert;															 // Asking the user to insert a character to search for in the BST.
				if (insert == '~') break;
				cout << insert << (charBST.search(insert) ? " is found in the BST" : " is not found in the BST") << endl;		// Calling the search function. Tells the user if the char they entered is or is not found in the BST.
			}
			continue;
			break;
		
		case 4:																					// If 4 is selected, the user would like to delete an item from the BST.
			cout << "You have selected to delete a node from the BST" << endl;
			
			for (;;)
			{
				cout << "Enter the item you want to delete: (~ to stop) ";
				cin >> insert;																// Asking the user to insert a character to delete from the BST.
				if (insert == '~') break;
				charBST.remove(insert);														// Calls the remove function

			}
			continue;
			break;
		
		case 5:																					// If 5 is selected, the user would like to display the number of leaves in the BST.
			cout << endl;
			cout << "You have selected to view the number of leaves in the BST" << endl;
			cout << endl;
			charBST.leafCount();																// Calls the leafCount function
			continue;
			break;
		
		case 6:																					// If 6 is selected, the user would like to display sibling of an item in the BST.
			cout << "You have selected to find the sibling of an item" << endl;			
			for (;;)
			{
				cout << "Enter the item you want to find the sibling of (~ to stop): ";
				cin >> insert;																 // Asks the user to insert the character they would like to see the sibling of.
				if (insert == '~') break;
				charBST.nodeSibling(insert);												// Calling the nodeSibling function

			}
			continue;
			break;
		
		case 7:																				// If 7 is selected, the user would like to quit out of the menu. Terminates the program.
			break;
		}
		break; 
	}
}