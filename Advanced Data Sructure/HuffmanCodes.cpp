#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

// charactor information, store input, build our Huffman Tree
class node {
public:
	char cha; // charactor
	int fre; // frequency
	int codeLength; // code length, calculated by ourselves
	node * left; // pointer used in Huffman Tree
	node * right; // pointer used in Huffman Tree
	node() : codeLength(0), left(nullptr), right(nullptr){} // initialized with nullptr
};

// comparison class used in priority_queue
class MyCompare {
public:
	// since it is a min heap, the comparison is reversed
	bool operator() (node * a, node * b) const {
		return a->fre > b->fre ? true : false;
	}
};

// build student's Huffman Tree
class checkTree {
public:
	bool exist; // there is a charactor in this node
	checkTree * left; // pointer used in Huffman Tree
	checkTree * right; // pointer used in Huffman Tree
	checkTree() : exist(false), left(nullptr), right(nullptr) {} // initialized with nullptr
};

// min heap, sorted by frequency
typedef priority_queue<node *, vector<node *>, MyCompare> MyHeap;
// build a Huffman Tree
void huffmanCoding(MyHeap & heap);
// traverse and set cost of each node
void setCodeLength(node * nico, int n);
// judge if it is a prefix array
bool isDup(vector<string> stud);

int main()
{
	int charNum;
	while (cin >> charNum && charNum != 0) {
		// read input
		MyHeap heap;
		vector<node *> record;
		for (int i = 0; i < charNum; ++i) {
			node * temp = new node;
			cin >> temp->cha >> temp->fre;
			record.push_back(temp);
			heap.push(temp);
		}
		// build Huffman Tree
		huffmanCoding(heap);
		setCodeLength(heap.top(), 0);
		// calculate total cost
		int cost = 0;
		for (int i = 0; i < charNum; ++i) {
			cost += record[i]->fre * record[i]->codeLength;
		}

		int studNum;
		cin >> studNum;
		for (int i = 0; i < studNum; ++i) {
			char tempCha;
			string tempString;
			vector<string> stud;
			int studCost = 0;
			// read students
			for (int j = 0; j < charNum; ++j) {
				cin >> tempCha >> tempString;
				stud.push_back(tempString);
				studCost += record[j]->fre * tempString.size();
			}
			// Judge 1: student's cost is not equal to the least cost
			if (studCost != cost) {
				cout << "No" << endl;
				continue;
			}
			// Judge 2: check prefix
			if (isDup(stud)) {
				cout << "No" << endl;
				continue;
			}
			else {
				cout << "Yes" << endl;
				continue;
			}
		}
	}

	return 0;
}

void huffmanCoding(MyHeap & heap)
{
	int size = heap.size();
	// build huffman tree
	for (int i = 1; i < size; ++i) {
		node * temp = new node;
		temp->left = heap.top(); // top: get the value
		heap.pop(); // pop: remove the value from heap
		temp->right = heap.top();
		heap.pop();
		temp->fre = temp->left->fre + temp->right->fre; // add together and form a new node
		heap.push(temp);
	}
}

void setCodeLength(node * nico, int n)
{
	// recursion stop
	if (nico == nullptr) {
		return;
	}
	nico->codeLength = n;
	// Preorder traversal with argument(level)
	setCodeLength(nico->left, n + 1);
	setCodeLength(nico->right, n + 1);
}

bool isDup(vector<string> stud)
{
	// build a tree according to student's answer
	checkTree * root = new checkTree;

	for (unsigned i = 0; i < stud.size(); ++i) {
		checkTree * nico = root;
		// right answer includes at least charactor
		if (stud[i].size() == 0) {
			return true;
		}
		for (unsigned j = 0; j < stud[i].size(); ++j) {
			// 0: left subtree
			if (stud[i].at(j) == '0') {
				if (nico->left == nullptr) {
					nico->left = new checkTree;
				}
				nico = nico->left;
			}
			// 1: right subtree
			else if (stud[i].at(j) == '1') {
				if (nico->right == nullptr) {
					nico->right = new checkTree;
				}
				nico = nico->right;
			}
			// neither 0 or 1: invalid input
			else {
				return true;
			}
			// an existed node have children -> duplication
			if (nico->exist) {
				return true;
			}
		}
		// search done, mark this node
		nico->exist = true;
		// an existed node have children -> duplication
		if (nico->left != nullptr || nico->right != nullptr) {
			return true;
		}
	}

	return false;
}
