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


void Ques_Tree::CreateTree(dyn_ll* ll_ptr)
{
	ll_node* tmp_nd = ll_ptr->nd;
	/* Previous subtree that was formed */
	Tree_Nd* t_prev_nd = NULL;
	Tree_Nd* t_nd = NULL;
	Tree_Nd* t_nd_l = NULL;
	Tree_Nd* t_nd_r = NULL;
	//Reach end of list first
	while( tmp_nd->next != NULL ) tmp_nd = tmp_nd->next;

	/* Need to think this */
	while( tmp_nd->prev != NULL )
	{
		while(tmp_nd->prev->type != Q_Nd )
		{
			tmp_nd = tmp_nd->prev;
		}

		//Alloc Tree Node for this Q node and then make l and r as next two As.
		t_nd = new Tree_Nd;
		t_nd_l = new Tree_Nd;
		if( tmp_nd->next->next->type == A_Nd ) t_nd_r = new Tree_Nd;

		t_nd->str = tmp_nd->str;
		t_nd->left = t_nd_l;

		t_nd_l->str = tmp_nd->next->str;
		t_nd_l->left = t_nd_l->right = NULL;

		if( tmp_nd->next->next->type == A_Nd )
		{
			t_nd->right = t_nd_r;
			t_nd_r->str = tmp_nd->next->next->str;
			t_nd_r->left = t_nd_r->right = NULL;
		}
		else t_nd->right = t_prev_nd;

		t_prev_nd = t_nd;
	}


}

void PlayGame()
{
	//Scans the file and reads the preorder traversal into the temp DLL
	dyn_ll* ll_ptr = FileScanner();

	//Convert the read pre-order traversal into a tree;
	Ques_Tree* q_ptr = new Ques_Tree;
	q_ptr->CreateTree(ll_ptr) ;

}

dyn_ll* FileScanner()
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
		return ll_ptr;
	}
	else return NULL;

}


