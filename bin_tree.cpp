#include <iostream>
using namespace std;


struct node{
	int value;
	node *left;
	node *right;
};

class btree{
public:
	btree();
	~btree();

	void insert(int key);
	node *search(int key);
	void destroy_tree();
	void inorder_print();
	void print_tree();
	void erase(int key);

private:
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);
	void inorder_print(node *leaf);
	void print_node(node *leaf, int level);
	node *root;
};

void btree::print_tree(){
	int level = 0;
	print_node(root, level);
}

void btree::print_node(node *leaf, int level){
	if(leaf != NULL){
		print_node(leaf->left, level + 3);
		for(int i = 0; i < level; ++i)
			cout << " ";
		cout << leaf->value << endl;
		print_node(leaf->right, level + 3);
	}
}


btree::btree(){
	root = NULL;
}

btree::~btree(){
	destroy_tree();
}

void btree::destroy_tree(){
	destroy_tree(root);
}

void btree::destroy_tree(node *leaf){
	if(leaf != NULL){
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::insert(int key, node *leaf){

	if(key < leaf->value){
		if(leaf->left != NULL){
			insert(key, leaf->left);
		}else{
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}else if(key > leaf->value){
		if(leaf->right != NULL){
			insert(key, leaf->right);
		}else{
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
		}
	}else{
		cout << "Already insert node with value " << key << endl;
	}

}

void btree::insert(int key){
	if(root != NULL){
		insert(key, root);
	}else{
		root = new node;
		root->value = key;
		root->left = NULL;
		root->right = NULL;
	}
}

node *btree::search(int key, node *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return leaf;
		}
		if(key < leaf->value){
			return search(key, leaf->left);
		}else{
			return search(key, leaf->right);
		}
	}else{
		return NULL;
	}
}


node *btree::search(int key){
	return search(key, root);
}

void btree::inorder_print(){
	inorder_print(root);
	cout << endl;
}

void btree::inorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

void btree::erase(int key)
{
    node *curr = root;
    node *parent = NULL;
    while (curr && curr->value != key)
    {
        parent = curr;
        if (curr->value > key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }
    if (!curr)
        return;
    if (curr->left == NULL)
    {
        // Вместо curr подвешивается его правое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->right;
        if (parent && parent->right == curr)
            parent->right = curr->right;
        delete curr;
        return;
    }
    if (curr->right == NULL)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->left == curr)
            parent->left = curr->left;
        if (parent && parent->right == curr)
            parent->right = curr->left;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    node *replace = curr->right;
    while (replace->left)
        replace = replace->left;
    int replace_value = replace->value;
    erase(replace_value);
    curr->value = replace_value;
}



int main(){

	btree *tree = new btree();


	tree->insert(10);
	tree->insert(6);
	tree->insert(14);
	tree->insert(5);
	tree->insert(8);
	tree->insert(18);
	tree->print_tree();
	tree->insert(7);
	tree->erase(18);

	tree->print_tree();

	delete tree;

}


