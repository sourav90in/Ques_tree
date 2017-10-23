/*
 * q_tree_impl.cpp
 *
 *  Created on: Oct 15, 2017
 *      Author: Sourav
 */



#include "q_tree.h"
#include <fstream>
#include <iostream>
using namespace q_t;


Tree_Nd* Ques_Tree::CreateTree(ll_node* nd_ptr, ll_node** prog_ptr)
{

	if(nd_ptr == NULL)
		return NULL;

	Tree_Nd* t_nd;
	t_nd = new Tree_Nd;
	t_nd->str = nd_ptr->str;
	*prog_ptr = nd_ptr;
	if( nd_ptr->type == A_Nd )
	{
		t_nd->left = t_nd->right = NULL;
	}
	else
	{
		t_nd->left = CreateTree(nd_ptr->next,prog_ptr);

		t_nd->right = CreateTree((*prog_ptr)->next,prog_ptr); //This can be done without crash since its a complete binary tree
	}

	return t_nd;

}

void Ques_Tree::Create_Q_Tree(ll_node* ln_ptr)
{
	root = CreateTree(ln_ptr,&ln_ptr);
}

void Ques_Tree::Node_Cleaner(Tree_Nd* tn_ptr)
{
	if(tn_ptr == NULL )
		return;

	Node_Cleaner(tn_ptr->left);
	Tree_Nd* tmp_ptr = tn_ptr->right;
	delete tn_ptr;
	Node_Cleaner(tmp_ptr);

}

Ques_Tree::~Ques_Tree()
{
	Node_Cleaner(this->root);

	delete this;
}

dyn_ll::~dyn_ll()
{
	ll_node * tmp_node = this->nd;
	cout<<"LL destructor called";

	while(tmp_node != NULL )
	{
		delete tmp_node;
		tmp_node = this->nd->next;
	}
	//delete this;
}


void QTreeToArr( Tree_Nd* tn_ptr, ll_node* ln_ptr,ll_node** prog_ptr )
{
	if(tn_ptr == NULL)
		return;

	if( ln_ptr != NULL )
	{
		*prog_ptr = ln_ptr;
		ln_ptr->str = tn_ptr->str;
		if( tn_ptr->left == NULL && tn_ptr->right == NULL ) ln_ptr->type = A_Nd;
		else ln_ptr->type = Q_Nd;

		//TO DO: Extra node allocated at end of LL incase of new input addition
		if(ln_ptr->next == NULL )
		{
			ll_node* t_ptr = new ll_node;
			ln_ptr->next = t_ptr;
		}

		QTreeToArr(tn_ptr->left, ln_ptr->next, prog_ptr);
		QTreeToArr(tn_ptr->right,(*prog_ptr)->next , prog_ptr );
	}
	else return;

}

void q_t::TreeToArr( Tree_Nd* tn_ptr, ll_node* ln_ptr )
{
	QTreeToArr(tn_ptr, ln_ptr,&ln_ptr);
}


void q_t::FileWriter(dyn_ll* ll_ptr)
{
	ofstream fhl ("qa.txt");
	string qa_line;
	string str1;
	ll_node* tmp_node =ll_ptr->nd;
	if( fhl.is_open() )
	{
		while(tmp_node != NULL )
		{
			qa_line = ( tmp_node->type == Q_Nd? "Q:\r\n":"A:\r\n" );
			cout<<qa_line;
			fhl << qa_line;
			str1 = tmp_node->str;
			cout<<str1<<"\n";
			fhl<< str1<<"\n";
			tmp_node = tmp_node->next;
		}
	}
	fhl.close();
}

//LL Debugging func
void q_t::TraverseLL(ll_node* nd)
{
	while(nd != NULL)
	{
		cout<<nd->str<<"\n";
		nd = nd->next;
	}

}

void q_t::TraverseTree(Tree_Nd* nd)
{
	if(nd == NULL )
		return;
	cout<<nd->str;
	TraverseTree(nd->left);
	TraverseTree(nd->right);
}

dyn_ll* q_t::FileScanner()
{

	ifstream fhl ("qa.txt");
	if( fhl.is_open() )
	{
		string line;
		string n_line;
		dyn_ll* ll_ptr = new dyn_ll;
		ll_node *prev = NULL;
		ll_node *tmp;
		while( getline(fhl, line) )
		{
			getline(fhl,n_line) ;

			if( line == "Q:\r")
			{
				tmp = new ll_node(n_line,NULL,prev,Q_Nd);
			}
			else
			{
				tmp = new ll_node(n_line,NULL,prev,A_Nd);
			}

			/* Alter the next value of previous node to point to current node */
			if( prev != NULL ) 	prev->next = tmp ;
			else ll_ptr->nd = tmp;

			tmp->prev = prev;
			/* Save previous node */
			prev = tmp;
		}
		fhl.close();
		TraverseLL(ll_ptr->nd);
		return ll_ptr;
	}
	else return NULL;

}

void q_t::PlayGame()
{
	//Scans the file and reads the preorder traversal into the temp DLL
	dyn_ll* ll_ptr = FileScanner();

	//Convert the read pre-order traversal into a tree;
	Ques_Tree* q_ptr = new Ques_Tree;
	q_ptr->Create_Q_Tree(ll_ptr->nd) ;
	TraverseTree( q_ptr->root);
	Tree_Nd* t_nd;
	string ans;
	string q_str;
	string a_str;

	while(1)
	{
		t_nd = q_ptr->root;


		cout << "Make a guess bro and hold it...\n";
		cout<<"I will ask you a series of questions.. answer them as Y or N only \n";
		while(t_nd != NULL)
		{
			if( t_nd->left == NULL && t_nd->right == NULL )
			{
				q_ptr->prev = t_nd;
				cout<<"My guess is:"<<t_nd->str;
				break;
			}
			else
			{
				cout<<t_nd->str;
				cout<<"\n";
				getline(cin,ans);
				q_ptr->prev = t_nd;
				if(ans == "y\r" || ans == "Y\r" )
				{
					t_nd = t_nd->left;
				}
				else
				{
					t_nd = t_nd->right;
				}
			}
		}
		cout<<"Was the answer correct? \n";
		getline(cin,ans);
		if(ans == "y\r" || ans == "Y\r" )
		{
			cout<<"Wohooo I win \n";
		}
		else
		{
			cout<<"Type a q to help me learn bro:";
			getline(cin,q_str);
			cout<<"Also tell me what you were thinking of:";
			getline(cin,a_str);
			Tree_Nd* nl_ptr = new Tree_Nd;
			Tree_Nd* nr_ptr = new Tree_Nd;
			nl_ptr->str = a_str;
			nr_ptr->str = q_ptr->prev->str;
			nl_ptr->left = nl_ptr->right = nr_ptr->left = nr_ptr->right = NULL;
			q_ptr->prev->str = q_str;
			q_ptr->prev->left = nl_ptr;
			q_ptr->prev->right = nr_ptr;

		}
		cout<<"Play another game:?";
		getline(cin,ans);
		if(ans == "y\r" || ans == "Y\r" )
			continue;
		else break;
	}

	// Game is completed now save the tree to array to File in preoder fashion
	//TraverseTree( q_ptr->root);
	TreeToArr( q_ptr->root, ll_ptr->nd);
	//TraverseLL(ll_ptr->nd);
	FileWriter(ll_ptr);
	//TraverseLL(ll_ptr->nd);

	//TO DO:Clean up resources
	/*
	 * Cleanup array first
	 * Tree Next
	 */
	delete ll_ptr;

	delete q_ptr;

}


