#include <cstdlib>
#include <iostream>
using namespace std;
#include "ensc251_lab3.h"
#include <chrono> 
//using namespace std::chrono; 


// I used this website as a reference to incorporate time measurnment tools:
//http://www.techiedelight.com/measure-elapsed-time-program-chrono-library/

//I used wikipedia to implemet AA tree code
//https://en.wikipedia.org/wiki/AA_tree




struct node{

 int value;
 node* right;
 node* left;
 int level;

};


class tree
{
public:
	int depth=0; //my level of the aa tree basically level of the root
	int number_skew;
	int number_split;

	//I USE THIS TO FIND DEPTH
	int some_function(node* T)
	{

		node* cursor;
		cursor=T;
		if (T->right==NULL)
		{
			return 0;
		} 

		while (cursor->right!=NULL)
		{
			if (cursor->level==cursor->right->level)
			{

				depth=depth+0; //DO NOT ADD DEPTH. ON THE SAME LEVEL
				//node* temp;
				cursor->right=cursor->right->right;

			}

			else
			{
				depth=depth+1;
				cursor->right=cursor->right->right;
			}
		}
		//T->right=T->right;
		return depth;
	}	


	node* skew(node* T)
	{

		if (T==NULL)
		{
			return NULL;
		}

		else if (T->left==NULL)
		{
			return T;
		}

		
		else if (T->left->level==T->level) 
		{
			number_skew=number_skew+1;
			node* PTR=T->left;
			T->left=PTR->right;  //now left   
			PTR->right=T;
			return PTR; 
		}
		else 
			return T; 

	}


	node* split(node* T)
	{
		//cout<<"I am here"<<endl;
		if (T==NULL) //no tree nothing to fix
		{
			return NULL;
		}

		else if (T->right==NULL || T->right->right==NULL)
		{
			return T;
		}


		else if (T->level==T->right->right->level) //that is the case
													//WE HAVE right nodes on the same level					
		{
			number_split=number_split+1;
			node* R=T->right;
			T->right=R->left;
			R->left=T;
			R->level=R->level+1; 
			depth=R->level; //I did this to put level

			return R; //WE NOW RETURN A NEW ROOT 
		}

		else {

			//in any other case we dont do anything
			//we just have the same number of levels
			//everything is fine
			return T;
		}



	}


	//NOW I NEED INSERT A NEW VALUE
	//I NEED TO SEE IF THIS VALUE IS INSIDE A TREE ALREADY AND ONLY THEN I CAN INSERT

	//IF THE VALUE DOESNT EXIST I ADD IT AT THE END




	node* insert(int X, node* T)
	{

		if (T==NULL) //I also use this to insert a new node
		{
			
			node* new_node=new node;

			new_node->value=X;
			new_node->left=NULL;
			new_node->right=NULL;


			new_node->level=1;
			return new_node; 
			
		}

		if (X < T->value )
		{
			T->left=insert(X, T->left);  
		}

		if (X>T->value)
		{
			//cout<<"i am here right"<<endl;
			T->right=insert(X, T->right);
			//cout<<"I am ever here???"<<endl;
		}

		if (X==T->value)
		{
			//do not insert please
			return T;
		}

		T=skew(T);
		T=split(T);

		return T;
	}

};



int main(){
	tree* my_tree=new tree; //my_tree points to my tree
	node* START;

	cout<<"AA tree insertion time starts now "<<endl;
	auto start = chrono::steady_clock::now();


	START=my_tree->insert(5, NULL);

	for (int i=0; i<10000; i++)
	{

		START=my_tree->insert(i, START);
		
	}

	cout<<"AA tree insertion time ends now "<<endl;
	auto end = chrono::steady_clock::now();
	


	int time1=chrono::duration_cast<chrono::nanoseconds>(end - start).count();
cout << "Time taken to insert 10 000 items into AA tree is "<< time1<<endl;


	int store_depth;
	store_depth=my_tree->some_function(START);

	cout<<"Depth of the tree after 10 000 insertions is "<<store_depth<<endl;

	cout<<"Number of splits and skews perforemed is "<<my_tree->number_split+my_tree->number_skew<<endl;

	
//_________________________________________________

	Heap* my_heap =new Heap;

	int heap_size=10000;


	cout<<"Now heap statistics "<<endl;
	auto start1 = chrono::steady_clock::now();


	int random_number;
	for (int i=0; i<heap_size; i++)
    {
        random_number=rand()%1000;
        my_heap->insert(random_number);
    }

    auto end1 = chrono::steady_clock::now();


    int time2=chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();

    cout << "Time taken to insert 10 000 items into a heap is "<<time2 <<endl;


	cout<<"Number of swaps in a heap which were completed, during insertion,  is "<<my_heap->swaps<<endl;


	cout<<"Heap insertion time vs AA tree insertion time is "<<time2<<" "<<time1<<endl;

    cout<<"SORTED HEAP ITEMS ARE "<<endl;

    int my_value;
    for (int i=0; i<heap_size; i++)
    {
        my_value=my_heap->remove_min();
        cout<<my_value<<" ";
        
    }

    //cout<<""


	return 0;
}
