/*
 * q_tree.h
 *
 *  Created on: Oct 14, 2017
 *      Author: Sourav
 */

#ifndef Q_TREE_H_
#define Q_TREE_H_

#include <cstdio>
#include <cstdlib>
#include <string>

namespace q_t
{
using namespace std;
class Ques_Tree;
struct ll_node;
struct dyn_ll;
struct Tree_Nd;
enum Node_type
{
	Q_Nd = 0,
	A_Nd = 1
};
struct dyn_arr;
dyn_ll* FileScanner();
void FileWriter(dyn_ll*);
void PlayGame();
void TreeToArr(Tree_Nd*,ll_node*);
}

/* Doubly linked list for faster read and write */
struct q_t::ll_node
{
	string str;
	struct ll_node *next;
	struct ll_node *prev;
	Node_type      type;
	ll_node(string st, ll_node *nxt=NULL, ll_node *prv=NULL,Node_type typ=Q_Nd ):str(st),next(nxt),prev(prv), type(typ) {}
	ll_node() { next = prev = NULL; }
	//~ll_node();
};

struct q_t::dyn_ll
{
	ll_node* nd;
	dyn_ll() { nd = NULL; }
	~dyn_ll();
};

struct q_t::Tree_Nd
{
	string str;
	Tree_Nd* left;
	Tree_Nd* right;
};

class q_t::Ques_Tree
{
private:
	q_t::Tree_Nd* root;
	q_t::Tree_Nd* prev; //To be used during parsing to locate pos to insert newly gathered data
	Tree_Nd* CreateTree(ll_node*);
	void Node_Cleaner(Tree_Nd*);
public:
	Ques_Tree():root(NULL),prev(NULL) { }
	~Ques_Tree();
	void Create_Q_Tree(ll_node*);
	friend void q_t::TreeToArr(Tree_Nd*,ll_node*);
	friend void q_t::PlayGame();
};

#endif /* Q_TREE_H_ */
