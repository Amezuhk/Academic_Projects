//----------------------------------------------------------------------------
//File: bintree.cpp
//Owner: Khuzaima Mushtaq
//Purpose: This is the implementation file for the BinTree Class required
//in lab 2.

#include "bintree.h"

/*Binary Tree constructor.
* sets the initial root node to nullptr
*/
BinTree::BinTree() {
	root = nullptr;
}

/*Binary Tree Copy Constructor
* Assumes that copy funtion works as desired
* makes two different trees, the trees do not point at each other
*/
BinTree::BinTree(const BinTree & toCopy) {
	root = copy(toCopy.root);
}

/*copy Constructur help function
* assumes Node is root of tree
*  returns a new tree root which is identical to the input tree
*/
BinTree::Node* BinTree::copy(const Node* current) {
	if (current == nullptr) {
		return nullptr;
	}
	Node* newNode = new Node; //new root node to return
	//set data
	newNode->data = new NodeData;
	newNode->right = nullptr;
	newNode->left = nullptr;
	*newNode->data = *current->data;

	newNode->left = copy(current->left); //recursively copy left
	newNode->right = copy(current->right); //recursively copy right

	return newNode;
}

/*Binary Tree Assignment Operator
* Assumes copy function works as intended
* makes a copy of the input and assigns that to the calling BinTree
*/
BinTree& BinTree::operator=(const BinTree & input) {
	if (*this == input) { //self assugbnebt
		return *this;
	}
	if (root != nullptr) { //make sure we dont have memory leaks
		makeEmpty();
	}
	root = copy(input.root);
	return *this;
	
}

/*Binary Tree Destructor
* Assumes that makeEmpty function works as intended
* deletes all Nodes and sub Nodes in the tree
* set root = nullptr
*/
BinTree::~BinTree() {
	makeEmpty();
}

//true if tree is empty, otherwise false
bool BinTree::isEmpty() const {
	if (root == nullptr)
		return true;
	else
		return false;
}

/*makeEmpty Helper Function
* traverses the Node* assumsed to be the root
* delete all NodeData and Nodes and sets all NodeData and Nodes to
* nullptr
*/
void BinTree::emptyHelper(Node* current) const {
	if (current != nullptr) {

		//traverse to leaves first
		emptyHelper(current->left);

		emptyHelper(current->right);

		delete current->data; //delete leaves
		current->data = nullptr;
		delete current;
		current = nullptr;

	}

}

/*Helper function for the BinTree destructor
* assumes emptyHelper function works as intended
*/
void BinTree::makeEmpty() {
	emptyHelper(root);
	root = nullptr;
}

/*inset Helper Function
* returns true if inserted, false if not
* Assumes Node is valid tree, NodeData is valid data
* adheres to the BinTree ADT while inserting values
*/
bool BinTree::insertHelper(Node* current, NodeData* input) {
	if (*input == *current->data) { //duplicate data
		return false;
	}else if (*input > *current->data) { 
		if (current->right != nullptr) { // still not at leaf
			insertHelper(current->right, input); //traverse to leaf
		}
		else {
			current->right = new Node; // insert data
			current->right->data = input;
			current->right->right = nullptr;
			current->right->left = nullptr;
			return true;
		}
	}
	else if (*input < *current->data) { 
		if (current->left != nullptr) {
			insertHelper(current->left, input); //still not at leaf
		}
		else {
			current->left = new Node; //insert data
			current->left->data = input;
			current->left->right = nullptr;
			current->left->left = nullptr;
			return true;
		}

	}
	return true;
}

/*BinaryTree Insert Function
* Assumes insertHelper works as intended
* NodeData is the data to be inserted
* returns true if NodeData is inserted, false if not
*/
bool BinTree::insert(NodeData* input) {
	if (isEmpty()) { //empty tree
		root = new Node;
		root->data = input;
		root->left = nullptr;
		root->right = nullptr;
		return true;
	}
	else {
		return insertHelper(root, input);
	}
}

/*Binary Tree euqality operator
*Assumes equalHelper function works as intended
* returns true if the data and the structure of the trees are the same
*/
bool BinTree::operator==(const BinTree &input) const {
	return equalHelper(root, input.root);
}

/*BinaryTree inequality Operator
* Assumes equalHelper function works as intended
* returns true if the data or the strucutre of the tree are not the same
*/
bool BinTree::operator!=(const BinTree &input) const {
	return !equalHelper(root, input.root);
}

/* == and != operator helper Function
* checks if the structure and data of the two trees is the same
* returns true if same, false if not
*/
bool BinTree::equalHelper(const Node* current, const Node* input) const {
	if (current == nullptr && input == nullptr) { //nulls are equal
		return true;
	}
	else if (current == nullptr || input == nullptr) { //one has sub root
		//other does not
		return false;
	}
	else { //check if data is equal
		return (*current->data == *input->data) &&
			(equalHelper(current->left, input->left)) &&
			(equalHelper(current->right, input->right));
		//recursively check if left and right nodes are equal
	}
}

/*BinaryTree retrieve Function
* Assumes retriveHelper works as intended
* const NodeData is the NodeData to retrive
* NodeData *& is where the NodeData is stored if found
* returns true if const NodeData count, false if not
*/
bool BinTree::retrieve(const NodeData& input, NodeData*& toReturn) const {
	return retriveHelper(root, input, toReturn);
}

/*retrive Helper Function
* return true if NodeData found and points NodeData*& to NodeData
* in tree. else, returns false, and NodeData*& stays nullptr
*/
bool BinTree::retriveHelper(Node* current, const NodeData& input,
	NodeData*& toReturn) const {
	if (current != nullptr) {
		if (*current->data == input) {// found data
			toReturn = current->data;
			return true; // retrived
		}
		// recursively check the whole tree
		if (input > *current->data) {
			return retriveHelper(current->right, input, toReturn);
		}
		else {
			return retriveHelper(current->left, input, toReturn);
		}

	}
	else {
		return false; //if not found, return false
	}
}

/*The functions << header.
* Assumptions: Does an in-order traversal of the Tree and prints the
* data in-order.
*/
ostream& operator<<(ostream& output, const BinTree& input) {
	return input.outputHelper(input.root, output) << endl;
}

/* << Operator helper Function
* traverses the tree Node* in-order
* returns ostream output of the tree
*/
ostream& BinTree::outputHelper(Node* input, ostream& output) const {
	if (input == nullptr) {
		return output;
	}
	//traverse in-order
	outputHelper(input->left, output);

	output << *input->data << " ";

	outputHelper(input->right, output);
}

/*BinaryTree getDepth Funtion
* Assumes getDepthHelper works as intended
* Assumes that the Binary Tree does not behave like a binary
* search tree
* Searches for NodeData and returns the depth if found
* returns 0 if not found
*/
int BinTree::getDepth(const NodeData& input) const {
	return getDepthHelper(input, root, 1);
}

/* getDepth Helper Function
* returns true if NodeData is found in Node tree
* increments int everytime a subroot is accessed increasing the depth
*/
int BinTree::getDepthHelper(const NodeData & input, Node* current,
	int depth) const {

	if (current == nullptr)
		return 0;
	if (*current->data == input) 
			return depth;
	//depth + 1 for each level increase

	int depthHelper = getDepthHelper(input, current->left, depth + 1);
	if(depthHelper == 0)  //if not 0, NodeData was found in left branch
		depthHelper = getDepthHelper(input, current->right, depth + 1);
	
	return depthHelper;
}

/*Binary Tree to Array Function
* Assumes TtoAHelper works as intended
* Assumes max arraysize is 100
* Leaves BinTree empty and with no pointers to the array
*/
void BinTree::bstreeToArray(NodeData* output[]) {
	int i = 0;
	TtoAHelper(root, output, i);
	makeEmpty();
}

/* bstreeToArray Helper Function
* uses int to keep track of array indexing as it traverses the tree
* and puts the data in the array
* deletes deferences to data from tree
*/
int BinTree::TtoAHelper(Node* current, NodeData* output[], int index) {
	if (current == nullptr)
		return index;
	//in-order traversal
	if (current->left != nullptr) {
		index = TtoAHelper(current->left, output, index);
	}
	output[index] = current->data;
	current->data = nullptr;
	//current->left = nullptr;
	index++; //only increased when data inserted
	if (current->right != nullptr) {
		index = TtoAHelper(current->right, output, index);
	}
	
	return index;
}

/*Array to BinaryTree function
* Assumes NodeData*[] is sorted
* Assumes AtoBHelper works as intended
* Leaves array empty with no points to data in the tree;
*/
void BinTree::arrayToBSTree(NodeData* data[]) {
	int max = 0;
	int min = 0;
	for (int i = 0; i < 100; i++) { //determine max
		if (data[i] == nullptr) {
			max = i;
			break;
		}
	}
	root = AtoBHelper(data, min, max-1);
	for (int i = 0; i < 100; i++)
		data[i] = NULL;
}

/*arraytoBSTree Helper Function
* assumes min and max are correct
* returns a root Node* that contains the tree made from NodeData*[]
*/
BinTree::Node* BinTree::AtoBHelper(NodeData* data[], int low, int high) {
	if (low > high)
		return nullptr;
	int mid = (low + high) / 2;

	Node* toReturn = new Node;
	toReturn->data = data[mid];

	toReturn->left = AtoBHelper(data, low, mid - 1);

	toReturn->right = AtoBHelper(data, mid + 1, high);

	return toReturn;

}

// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

/*displaySideways Helper Function
* assumed it works as intended
* provided by instructor
*/
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;     // display information of object
		sideways(current->left, level);
	}
}
