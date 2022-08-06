
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;


class bst {
	private:
	int value;
	bst* left;
	bst* right;
	void addnode(bst *node);
	void addbalancednode(bst *node);
	void insertorreplaceleft(bst *node);
	void insertorreplaceright(bst *node);
	public:
	bst(int n) {this->value=n; this->left=NULL;this->right=NULL;}
	~bst() {delete this->left;delete this->right;}
	bst* getleft() {return this->left;}
	bst* getright() {return this->right;}
	int  getvalue() {return this->value;}
	void addbalanced(bst *node);
	bool isnullnode(bst *node) {return node==NULL;}
	bool isnullleft()  {return isnullnode(this->getleft());} 
	bool isnullright() {return isnullnode(this->getright());} 
	void addvalue(int value);
	void addbalanced(int value);
	bool isvalidleft();
	bool isvalidright();
	bool isvalidbst();
	int  height();
	friend std::ostream& operator<<(std::ostream& os, const bst *node) {
		if (node == NULL) {
			return os << "NULL";
		} else {
			return os <<"left: "   << node->left 
 				  << "value: " << std::to_string(node->value)
				  << endl 
				  << "right: " << node->right;
		}
	}
};

void bst::insertorreplaceleft(bst *node) {
	if (this->isnullleft()){
		this->left = node;
	} else {
		this->getleft()->addnode(node);
	}
}

void bst::insertorreplaceright(bst *node) {
	if (this->isnullright()){
		this->right = node;
	} else {
		this->getright()->addnode(node);
	}
}

void bst::addnode(bst *node){
	if (node->value>this->getvalue()){
		insertorreplaceright(node);
	} else {
		insertorreplaceleft(node);
	}
}

int bst::height(){
	if (this==NULL) {
		return 0;
	} else {
		return 1 + max(this->left->height(), this->right->height());
	}
}

void bst::addbalancednode(bst *node){
	if (this->isnullleft()) {
		this->left=node;
	} else {
		if (this->isnullright()){
			this->right=node;
		} else {
			if (this->left->height() < this->right->height()){
				this->left->addbalancednode(node);
			} else {
				this->right->addbalancednode(node);
			}
		}
	}
}

void bst::addvalue(int a){
	this->addnode(new bst(a));
}

void bst::addbalanced(int a){
	this->addbalancednode(new bst(a));
}

bool bst::isvalidleft(){
	return this->left == NULL || this->value >= this->left->value;
}

bool bst::isvalidright(){
	return this->right == NULL || this->value < this->right->value;
}

bool bst::isvalidbst(){
	return this == NULL || (this->isvalidleft() && this->isvalidright()); 
}

int main(int argc, char *argv[]){
	bst *root = new bst(6);
	std::vector<int> vs = {10,5,7,3,9,4,8,1,2};
	auto addfunction = [=](int n){root->addvalue(n);};
	std::for_each(vs.begin(),vs.end(),addfunction);
	cout << "tree: " << root << endl;
	cout << "resultado: " << root->isvalidbst() << endl;
	cout << "height: " << root->height() << endl;
	bst *nobst = new bst(1);
	auto addnodefunction = [=](int n){nobst->addbalanced(n);};
	std::for_each(vs.begin(),vs.end(),addnodefunction);
	cout << "tree: " << nobst << endl;
	cout << "resultado: " <<  nobst->isvalidbst() << endl;
	cout << "height: " << nobst->height() << endl;
	delete(root);
	delete(nobst);
	return 0;
}
