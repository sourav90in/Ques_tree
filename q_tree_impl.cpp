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


Tree_Nd* Ques_Tree::CreateTree(ll_node* nd_ptr)
{
	Tree_Nd* t_nd;
	t_nd = new Tree_Nd;
	t_nd->str = nd_ptr->str;
	if( nd_ptr->type == A_Nd )
	{
		t_nd->left = t_nd->right = NULL;
	}
	else
	{
		t_nd->left = CreateTree(nd_ptr->next);
		t_nd->right = CreateTree(nd_ptr->next);
	}

	return t_nd;

}

void Ques_Tree::Create_Q_Tree(ll_node* ln_ptr)
{
	root = CreateTree(ln_ptr);
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

	while(tmp_node != NULL )
	{
		delete tmp_node;
		tmp_node = this->nd->next;
	}
	delete this;
}

void q_t::TreeToArr( Tree_Nd* tn_ptr, ll_node* ln_ptr )
{
	if(tn_ptr == NULL)
		return;

	if( ln_ptr != NULL )
	{
		ln_ptr->str = tn_ptr->str;
		if( tn_ptr->left == NULL && tn_ptr->right == NULL ) ln_ptr->type = A_Nd;
		else ln_ptr->type = Q_Nd;

		if(ln_ptr->next == NULL )
		{
			ll_node* t_ptr = new ll_node;
			ln_ptr->next = t_ptr;
		}
	}
	TreeToArr(tn_ptr->left, ln_ptr->next);
	TreeToArr(tn_ptr->right, ln_ptr->next);

}


void q_t::FileWriter(dyn_ll* ll_ptr)
{
	ofstream fhl ("qa.txt");
	string qa_line;
	string str;
	if( fhl.is_open() )
	{
		while(ll_ptr->nd->next != NULL )
		{
			qa_line = ( ll_ptr->nd->type == Q_Nd? "Q:\n":"A: \n" );
			fhl << qa_line;
			str = ll_ptr->nd->str;
			fhl << str << "\n";
		}
	}
	fhl.close();
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
		while( getline(fhl, line) )
		{
			getline(fhl,n_line) ;
			if( line == "Q:")
			{
				ll_ptr->nd = new ll_node(n_line,NULL,prev,Q_Nd);
			}
			else
			{
				ll_ptr->nd = new ll_node(n_line,NULL,prev,A_Nd);
			}

			/* Alter the next value of previous node to point to current node */
			if( prev != NULL ) 	prev->next = ll_ptr->nd ;
			ll_ptr->nd->prev = prev;
			/* Save previous node */
			prev = ll_ptr->nd;
		}
		fhl.close();
		return ll_ptr;
	}
	else return NULL;

}

void q_t::PlayGame()
{
	//Scans the file and reads the preorder traversal into the temp DLL
	dyn_ll* ll_ptr = q_t::FileScanner();

	//Convert the read pre-order traversal into a tree;
	Ques_Tree* q_ptr = new Ques_Tree;
	q_ptr->Create_Q_Tree(ll_ptr->nd) ;
	Tree_Nd* t_nd;
	char ans;
	string q_str;
	string a_str;

	while(1)
	{
		t_nd = q_ptr->root;


		cout << "Make a guess bro and hold it...\n";
		cout<<"I will ask you a series of questions.. answer them as Y or N only \n";
		while(t_nd != NULL)
		{
			cout<<t_nd->str;
			cout<<"\n";
			cin>>ans;
			q_ptr->prev = t_nd;
			if(ans == 'y' || ans == 'Y' )
			{
				t_nd = t_nd->left;
			}
			else
			{
				t_nd = t_nd->right;
			}
		}
		cout<<"Was the answer correct?:";
		cin>>ans;
		if(ans == 'y' || ans == 'Y' )
		{
			cout<<"Wohooo";
			cout<<"Play another game:?";
			cin>>ans;
			if( ans == 'y' || ans == 'Y' )
				break;
			else continue;
		}
		else
		{
			cout<<"Type a q to help me learn bro:";
			cin>>q_str;
			cout<<"Also tell me what you were thinking of:";
			cin>>a_str;
			Tree_Nd* nl_ptr = new Tree_Nd;
			Tree_Nd* nr_ptr = new Tree_Nd;
			nl_ptr->str = a_str;
			nr_ptr->str = q_ptr->prev->str;
			nl_ptr->left = nl_ptr->right = nr_ptr->left = nr_ptr->right = NULL;
			q_ptr->prev->str = q_str;
			q_ptr->prev->left = nl_ptr;
			q_ptr->prev->right = nr_ptr;

		}
	}

	// Game is completed now save the tree to array to File in preoder fashion
	q_t::TreeToArr( q_ptr->root, ll_ptr->nd);
	q_t::FileWriter(ll_ptr);

	//Clean up resources
	/*
	 * Cleanup array first
	 * Tree Next
	 */
	delete ll_ptr;

	delete q_ptr;

}


