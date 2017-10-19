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
using std::string;
using std::ifstream;
using std::ofstream;
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
void FileWriter(Ques_Tree);
void PlayGame();
}

/* Doubly linked list for faster read and write */
struct q_t::ll_node
{
	string str;
	struct ll_node *next;
	struct ll_node *prev;
	Node_type      type;
	ll_node(string st, ll_node *nxt=NULL, ll_node *prv=NULL,Node_type typ=Q_Nd ):str(st),next(nxt),prev(prv), type(typ) {}
	~ll_node();
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
public:
	Ques_Tree():root(NULL),prev(NULL) { }
	void CreateTree(dyn_ll*);
	//void InsertNode(string);
	//void DeleteNode(string);
};

/*
 * Your program also have to be able to write the tree to an output file and read it back in.
 * That way your question tree can grow each time a user runs the program.
 * To be able to read and write the tree, we need a set of rules for how to represent
 * the tree which we’ll refer to as the standard format for a question tree.
 * A tree is specified by a nonempty sequence of line pairs, one for each node of the tree.
 * The first line of each pair should contain either the text “Q:” to indicate that it is a question node
 * (i.e., a branch node) or the text “A:” to indicate that it is an answer node (i.e., a leaf node).
 * The second line of each pair should contain the text for that node (the question or answer).
 * The nodes should appear in preorder (i.e., in the order produced by a preorder traversal of the tree).
 */

#endif /* Q_TREE_H_ */
