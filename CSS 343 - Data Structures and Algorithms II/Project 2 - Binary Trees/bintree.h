//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
//File: bintree.h
//Owner: Khuzaima Mushtaq
//Purpose: This is the header file for the BinTree Class required
//in lab 2.
//ADT Description and Assumptions: The binary tree ADT is a data structure
//that has a root and the root has 2 sub-roots a right one and a left one.
//It is assumed that the right subroot is greater than the parent root, and
//the left subroot is lower than the parent root. each sub-root can have
//its own sub-root, if a sub-root does not have any more sub-roots its
//called a leaf. 
#include "nodedata.h"
#pragma once
class BinTree {

	/*The functions << header.
	* Assumptions: Does an in-order traversal of the Tree and prints the
	* data in-order. 
	*/
	friend ostream& operator<<(ostream&, const BinTree&);

public:

	/*Binary Tree constructor.
	* sets the initial root node to nullptr
	*/
	BinTree();

	/*Binary Tree Copy Constructor
	* Assumes that copy funtion works as desired
	* makes two different trees, the trees do not point at each other
	*/
	BinTree(const BinTree &);

	/*Binary Tree Destructor
	* Assumes that makeEmpty function works as intended
	* deletes all Nodes and sub Nodes in the tree
	* set root = nullptr
	*/
	~BinTree(); // destructor, calls makeEmpty

	//true if tree is empty, otherwise false
	bool isEmpty() const; 

	/*Helper function for the BinTree destructor
	* assumes emptyHelper function works as intended
	*/
	void makeEmpty(); // make the tree empty so isEmpty returns true

	/*Binary Tree Assignment Operator
	* Assumes copy function works as intended
	* makes a copy of the input and assigns that to the calling BinTree
	*/
	BinTree& operator=(const BinTree &);

	/*Binary Tree euqality operator
	*Assumes equalHelper function works as intended
	* returns true if the data and the structure of the trees are the same
	*/
	bool operator==(const BinTree &) const;

	/*BinaryTree inequality Operator
	* Assumes equalHelper function works as intended
	* returns true if the data or the strucutre of the tree are not the same
	*/
	bool operator!=(const BinTree &) const;

	/*BinaryTree Insert Function
	* Assumes insertHelper works as intended
	* NodeData is the data to be inserted
	* returns true if NodeData is inserted, false if not
	*/
	bool insert(NodeData*);

	/*BinaryTree retrieve Function
	* Assumes retriveHelper works as intended
	* const NodeData is the NodeData to retrive
	* NodeData *& is where the NodeData is stored if found
	* returns true if const NodeData count, false if not
	*/
	bool retrieve(const NodeData&, NodeData*&) const;

	/*BinaryTree displaySideways function
	* Assume it works, provided by instructor
	* Assumes sideways functions works as intended
	* prints the Tree side ways. 
	*/
	void displaySideways() const;

	/*BinaryTree getDepth Funtion
	* Assumes getDepthHelper works as intended
	* Assumes that the Binary Tree does not behave like a binary
	* search tree
	* Searches for NodeData and returns the depth if found
	* returns 0 if not found
	*/
	int getDepth(const NodeData &) const;

	/*Binary Tree to Array Function
	* Assumes TtoAHelper works as intended
	* Assumes max arraysize is 100
	* Leaves BinTree empty and with no pointers to the array
	*/
	void bstreeToArray(NodeData*[]);

	/*Array to BinaryTree function
	* Assumes NodeData*[] is sorted
	* Assumes AtoBHelper works as intended
	* Leaves array empty with no points to data in the tree;
	*/
	void arrayToBSTree(NodeData*[]);

private:

	/*Node Struct as defined in the assignment
	* Assumes has a left subtree ptr and a right subtree ptr
	* has a NodeData ptr;
	*/
	struct Node {
		NodeData* data; // pointer to data object
		Node* left; // left subtree pointer
		Node* right; // right subtree pointer
	};

	Node* root; // root of the tree

    // Helper functions

	/*copy Constructur help function
	* assumes Node is root of tree
	*  returns a new tree root which is identical to the input tree
	*/
	Node* copy(const Node*);

	/* getDepth Helper Function
	* returns true if NodeData is found in Node tree
	* increments int everytime a subroot is accessed increasing the depth
	*/
	int getDepthHelper(const NodeData &, Node*, int) const;

	/* << Operator helper Function
	* traverses the tree Node* in-order
	* returns ostream output of the tree
	*/
	ostream& outputHelper(Node*, ostream&) const;

	/* == and != operator helper Function
	* checks if the structure and data of the two trees is the same
	* returns true if same, false if not
	*/
	bool equalHelper(const Node*, const Node*) const;

	/*inset Helper Function
	* returns true if inserted, false if not
	* Assumes Node is valid tree, NodeData is valid data
	* adheres to the BinTree ADT while inserting values
	*/
	bool insertHelper(Node*, NodeData*);

	/*arraytoBSTree Helper Function
	* assumes min and max are correct
	* returns a root Node* that contains the tree made from NodeData*[]
	*/
	Node* AtoBHelper(NodeData*[], int min, int max);

	/* bstreeToArray Helper Function
	* uses int to keep track of array indexing as it traverses the tree
	* and puts the data in the array
	* deletes deferences to data from tree
	*/
	int TtoAHelper(Node*,NodeData* [], int);

	/*retrive Helper Function
	* return true if NodeData found and points NodeData*& to NodeData
	* in tree. else, returns false, and NodeData*& stays nullptr
	*/
	bool retriveHelper(Node*, const NodeData&, NodeData*&) const;

	/*makeEmpty Helper Function
	* traverses the Node* assumsed to be the root
	* delete all NodeData and Nodes and sets all NodeData and Nodes to
	* nullptr
	*/
	void emptyHelper(Node*) const;

	/*displaySideways Helper Function
	* assumed it works as intended
	* provided by instrutor
	*/
	void sideways(Node*, int) const;
//	...
};
