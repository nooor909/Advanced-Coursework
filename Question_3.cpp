// Advanced Algorithms Coursework
// Question 3

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class Node {
public:
	string key;
	Node* left;
	Node* right;
	int height;

	Node(string k) {
		key = k;
		left = nullptr;
		right = nullptr;
		height = 1;
	}
};

class AVLTree {
private:
	Node* root;

	// Getting the height of the tree
	int getHeight(Node* node) {
		if (node == nullptr)
			return 0;
		else
			return node->height;
	}

	// Getting the balance factor
	int getBalance(Node* node) {
		if (node == nullptr)
			return 0;
		int leftHeight = getHeight(node->left);
		int rightHeight = getHeight(node->right);
		return leftHeight - rightHeight;
	}

	// Updating the height of the tree
	void updateHeight(Node* node) {
		if (node != nullptr) {
			int leftHeight = getHeight(node->left);
			int rightHeight = getHeight(node->right);
			node->height = 1 + max(leftHeight, rightHeight);
		}
	}

	// Rotations (Right and Left)
	Node* rightRotate(Node* y) {
		Node* x = y->left;
		Node* z = x->right;
		x->right = y;
		y->left = z;
		updateHeight(y);
		updateHeight(x);
		return x;
	}

	Node* leftRotate(Node* x) {
		Node* y = x->right;
		Node* z = y->left;
		y->left = x;
		x->right = z;
		updateHeight(x);
		updateHeight(y);
		return y;
	}

	// Inserting the key into the AVL tree
	Node* insert(Node* node, string key) {
		if (node == nullptr)
			return new Node(key);
		if (key < node->key)
			node->left = insert(node->left, key);
		else if (key > node->key)
			node->right = insert(node->right, key);
		else
			return node;

		updateHeight(node);

		int balance = getBalance(node);

		// Left Left Case
		if (balance > 1 && key < node->left->key)
			return rightRotate(node);
		// Right Right Case
		if (balance < -1 && key > node->right->key)
			return leftRotate(node);
		// Left Right Case
		if (balance > 1 && key > node->left->key) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}
		// Right Left Case
		if (balance < -1 && key < node->right->key) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	void inorder(Node* node) {
		if (node == nullptr)
			return;
		inorder(node->left);
		cout << node->key << " ";
		inorder(node->right);
	}

	// Collecting all words in the given range
	void collectRange(Node* node, string low, string high, int& count, int limit = 20) {
		if (node == nullptr)
			return;

		if (node->key >= low)
			collectRange(node->left, low, high, count, limit);

		if (node->key >= low && node->key < high) {
			if (count < limit)
				cout << " - " << node->key << endl;
			count++;
		}
		if (node->key < high)
			collectRange(node->right, low, high, count, limit);
	}

public:
	AVLTree() {
		root = nullptr;
	}

	void insertWord(string key) {
		root = insert(root, key);
	}

	void printInOrder() {
		inorder(root);
		cout << endl;
	}

	// Finding all words with the given prefix
	void FindAllWithPrefix(string prefix) {
		if (root == nullptr || prefix.empty()) {
			cout << "No matches found." << endl;
			return;
		}

		string upper = prefix + '\xFF';
		int allMatches = 0;

		collectRange(root, prefix, upper, allMatches);

		if (allMatches == 0) {
			cout << "No matches found." << endl;
		}
		else if (allMatches > 20) {
			cout << "... and " << (allMatches - 20) << " more." << endl;
		}
	}
};

int main() {
	AVLTree tree;
	ifstream file("dictionary.txt");

	if (!file.is_open()) {
		cout << "There was an error with opening the file. Please make sure you added the right file. " << endl;
		return 0;
	}

	string word;
	while (file >> word) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		tree.insertWord(word);
	}
	file.close();

	string prefix;
	while (true) {
		cout << "Enter a prefix : ";
		cin >> prefix;
		if (prefix.empty())
			break;
		transform(prefix.begin(), prefix.end(), prefix.begin(), ::tolower);
		tree.FindAllWithPrefix(prefix);
	}
}