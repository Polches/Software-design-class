// Example program
#include <iostream>
#include <string>
#include <fstream> //for input file
#include <vector>
#include <cmath> //for log function
using namespace std;
//this function is to open file and read data
//into a 2d vector

int read_number_of_attributes(string file_name)
{
	
	ifstream my_input_file; //file is called my_input_file
	my_input_file.open (file_name.c_str());

	if (my_input_file.is_open()==false)
	{
		cout<<"File is not open "<<endl;
		return -1;
	}


	string line;
	getline(my_input_file, line);
	
	int string_length=line.length();
	int comma_counter=0;
	for (int i=0; i<string_length; i++)
		{
			if (line[i]==',')
				{
					comma_counter=comma_counter+1;
				}				
		}


	my_input_file.close();
	return comma_counter;

}

vector< vector<double>*>* read_data(string file_name)
{
	
	ifstream my_input_file; //file is callled my_input_file
	my_input_file.open (file_name.c_str());

	double number;
	char comma;
	string classification;

	vector< vector<double>* >* table_of_data=new vector< vector<double>* > ;
	int number_of_attributes=read_number_of_attributes(file_name);
	int size_of_internal_vector=number_of_attributes;
	
	vector<double>* internal_vector= new vector<double>;
	vector<string>* classification_vector=new vector<string>;

	while(my_input_file.eof()==false)
	{

		vector<double>* internal_vector= new vector<double>;
		for(int i=0; i<size_of_internal_vector; i++)
			{
				
				my_input_file>>number;
				internal_vector->push_back(number);
				my_input_file>>comma;
					
			}

		table_of_data->push_back(internal_vector);
		my_input_file>>classification;

	}
	
	table_of_data->erase(table_of_data->end()-1);
	
	my_input_file.close();
	return table_of_data;	

}

vector<string>* read_classification(string file_name)
{

	ifstream my_input_file; //file is callled my_input_file
	my_input_file.open (file_name.c_str());
	
	int number_of_attributes=read_number_of_attributes(file_name);

	string classification;
	double number;
	char comma;
	
	int size_of_internal_vector=number_of_attributes;
		
	vector<string>* classification_vector=new vector<string>;

	while(my_input_file.eof()==false)
	{
	
		for(int i=0; i<size_of_internal_vector; i++)
			{
			
				my_input_file>>number;			
				my_input_file>>comma;
			
			}
		my_input_file>>classification;
		classification_vector->push_back(classification);
		
	}

	classification_vector->erase(classification_vector->end()-1);
	
	my_input_file.close();
	return classification_vector;
}


void print_classification_data(vector<string>* your_vector)
{
		int size_classification=your_vector->size();

		for (int i=0; i<size_classification; i++)
			{
				cout<<your_vector->at(i)<<endl;
			}
	
}


void print_vector_data(vector< vector<double>* >* your_data_vector)
{

	int size_data_vector=your_data_vector->size();
	int size_internal_vector=your_data_vector->at(0)->size();

	for (int i=0; i<size_data_vector; i++)
	{
		for (int j=0; j<size_internal_vector; j++)
		{
			cout<<your_data_vector->at(i)->at(j)<<" ";			

		}		
	cout<<endl;
	}

}

void print_space(int number_of_space)
{
	for (int i=0; i<number_of_space; i++)
		{
			cout<<" ";
		}
}

string first_string(vector<string>* flower_data)
		{
			return flower_data->at(0);
		}	

string second_string(vector<string>* flower_data)
		{
			int size=flower_data->size();
			
			string second_string=flower_data->at(0);
			
			for (int i=0; i<size; i++)
				{
					if (second_string!=flower_data->at(i))
						{
							second_string=flower_data->at(i);
							break;
						}
						
				}
		
		return second_string;
}


double entropy_classification(vector<string>* your_flower_data)
{
	double setosa=0.000;
	double versicolor=0.000;
	double size_classification=your_flower_data->size();
	string first_one=first_string(your_flower_data);
	string second_one=second_string(your_flower_data);
	for (int i=0; i<size_classification; i++)
	{
		
		if (your_flower_data->at(i)==first_one)
			{
				setosa=setosa+1.0000;
			}

		if(your_flower_data->at(i)==second_one)
			{

				versicolor=versicolor+1.0000;
			}
				
	}

	if (setosa==0)
		{
			
			return 0;
		}

	if (versicolor==0)
		{
			return 0;	
		}
	double probability_of_setosa=setosa/size_classification;
	double probability_of_versicolor=versicolor/size_classification;
	double log_setosa=log2(probability_of_setosa);
	double log_versicolor=log2(probability_of_versicolor);
	double entropy_of_classification=(-1.0)*(probability_of_setosa)*(log_setosa)-(probability_of_versicolor)*(log_versicolor);
	
	return entropy_of_classification;

}


double one_gain_calculation(int row_split, int col_split, vector< vector<double>* >* your_data_vector, vector<string>* your_flower_data)
{
	double split_number=your_data_vector->at(row_split)->at(col_split);
		
	int external_size=your_data_vector->size();
	int internal_size=your_flower_data->size();

	string string_one=first_string(your_flower_data);
	string second_one=second_string(your_flower_data);

	double counter_larger_split=0;
	double counter_lower_split=0;

	double counter_setosa_larger_split=0;
	double counter_versicolor_larger_split=0;

	double counter_setosa_lower_split=0;
	double counter_versicolor_lower_split=0;

	for (int i=0; i<external_size; i++)
	{
		if (your_data_vector->at(i)->at(col_split) > split_number)
		{
									counter_larger_split=counter_larger_split+1;
										
									if (your_flower_data->at(i)==string_one)
										{
											counter_setosa_larger_split=counter_setosa_larger_split+1;
										}
									if (your_flower_data->at(i)==second_one)
										{
											counter_versicolor_larger_split=counter_versicolor_larger_split+1;	
										}

		}


		if (your_data_vector->at(i)->at(col_split) <= split_number)
		{
				counter_lower_split=counter_lower_split+1;

				if (your_flower_data->at(i)==string_one)
					{
						counter_setosa_lower_split=counter_setosa_lower_split+1;
					}
				if (your_flower_data->at(i)==second_one)
					{
						counter_versicolor_lower_split=counter_versicolor_lower_split+1;	
					}			
				

		}
	}
	
	double prob_setosa_larger_split=counter_setosa_larger_split/counter_larger_split;
	if (counter_larger_split==0)
		{
			prob_setosa_larger_split=0;
		}
	
	double prob_versicolor_larger_split=counter_versicolor_larger_split/counter_larger_split;
		if (counter_larger_split==0)
		{
			prob_versicolor_larger_split=0;
		}


	double log_entropy_larger_split_setosa=log2(prob_setosa_larger_split);
	
	if (prob_setosa_larger_split==0)
	{
		log_entropy_larger_split_setosa=0;
	}

	double log_entropy_larger_split_versicolor=log2(prob_versicolor_larger_split);
	if (prob_versicolor_larger_split==0)
	{
		log_entropy_larger_split_versicolor=0;
	}
	
	double Entropy_larger_split=(-1.000)*prob_setosa_larger_split*log_entropy_larger_split_setosa-prob_versicolor_larger_split*log_entropy_larger_split_versicolor;

	double prob_setosa_lower_split=counter_setosa_lower_split/counter_lower_split;
	if(counter_lower_split==0)
	{
		prob_setosa_lower_split=0;	
	}


	double prob_versicolor_lower_split=counter_versicolor_lower_split/counter_lower_split;
	if(counter_lower_split==0)
	{
		prob_versicolor_lower_split=0;
	}

	double log_entropy_lower_split_setosa=log2(prob_setosa_lower_split);
	if(prob_setosa_lower_split==0)
	{
		log_entropy_lower_split_setosa=0;
	}

	double log_entropy_lower_split_versicolor=log2(prob_versicolor_lower_split);
	if (prob_versicolor_lower_split==0)
	{
		log_entropy_lower_split_versicolor=0;
	}

	double Entropy_lower_split=(-1.000)*(prob_setosa_lower_split)*log_entropy_lower_split_setosa-prob_versicolor_lower_split*log_entropy_lower_split_versicolor;

	double average_entropy=(counter_larger_split/external_size)*Entropy_larger_split+(counter_lower_split)/(external_size)*Entropy_lower_split;

	double entropy_decision=entropy_classification(your_flower_data);
	double gain=entropy_decision-average_entropy;

	return gain;
}

struct max_gain{

	int row_index;
	int column_index;
	double max_value;

};

struct max_gain* max_gain_struct(vector< vector<double>* >* your_data_vector_here, vector<string>* your_flower_data)
{
	
	int size_internal=your_data_vector_here->at(0)->size();
	int size_external=your_data_vector_here->size();
	double my_gain;

	vector< vector<double>* >* external_gain= new vector< vector<double>* >;

	for (int i=0; i<size_external; i++)
	{
			vector<double>* internal_gain=new vector<double>;
			for( int j=0; j<size_internal; j++)
			{
				my_gain=one_gain_calculation(i,j,your_data_vector_here,your_flower_data);
		
				internal_gain->push_back(my_gain);
				
			}
	 		external_gain->push_back(internal_gain);
	}

		
	double max_gain =-1.0;

	struct max_gain* found_max_gain=new struct max_gain;
	
			for( int i=0; i<size_external; i++)
			{
				for (int j=0; j<size_internal; j++)
					{
						
						if (external_gain->at(i)->at(j) >max_gain)
							{
								max_gain=external_gain->at(i)->at(j);
								found_max_gain->max_value=max_gain;
								found_max_gain->row_index=i;
								found_max_gain->column_index=j;
							}

					}
						
			}

	return found_max_gain;

}

struct node{
	
	vector< vector<double>* >* data;
	
	vector<string>* flower_data;
	
	double decision_split;
	int decision_row;
	int decision_column;
	
	bool is_it_homogeneous;

	struct node* right_child;
	struct node* left_child;

	struct node* parent;

	int size_data;
	
};






class decision_tree{
	public:

	struct node* first_node(vector< vector<double>* >* your_data, vector<string>* your_flower_data)
	{
		
		struct node* new_node= new struct node; 
		new_node->data=your_data;
		new_node->flower_data=your_flower_data;
		
		new_node->size_data=your_data->size();
	
		struct max_gain* maximum_gain=max_gain_struct(your_data,your_flower_data );
		new_node->decision_row=maximum_gain->row_index;
		new_node->decision_column=maximum_gain->column_index;
		
		new_node->decision_split=your_data->at(maximum_gain->row_index)->at(maximum_gain->column_index);
		
		new_node->right_child=NULL;
		new_node->left_child=NULL;
		new_node->parent=NULL;

		new_node->is_it_homogeneous=is_data_homog(new_node);

		return new_node;

	}


	void print_node_content(node* your_node)
		{
			cout<<"HERE IS CREATED NODE"<<	endl;
			cout<<"node size is "<<your_node->size_data<<endl;
			cout<<"decision split is "<<your_node->decision_split<<endl;
			cout<<"decision row is "<<your_node->decision_row<<endl;
			cout<<"decision column is "<<your_node->decision_column<<endl;
			cout<<"is is homogeneous? "<<your_node->is_it_homogeneous<<endl;

			for (int a=0; a<your_node->size_data; a++)
				{
					cout<<your_node->flower_data->at(a)<<" ";
				}
			
		}
	

	bool is_data_homog(node* your_node)
		{
				bool homogeneous=true;
				int size_classification=your_node->flower_data->size();
				string first_string=your_node->flower_data->at(0);
				
				for (int i=0; i<size_classification; i++)
					{
					 	if (your_node->flower_data->at(i)!=first_string)
						homogeneous=false;
					
					}
				
			return homogeneous;
		}
	

	struct node* split_function_recursive(struct node* start_node)
	{
		bool homogeneous=is_data_homog(start_node);
			
		if (homogeneous==false)
		{

				vector< vector<double>* >* right_node_data=new vector< vector<double>* >;
				vector<string>* right_node_flower= new vector<string>;
				
				
				vector< vector<double>* >* left_node_data= new vector< vector<double>* >;
				vector<string>* left_node_flower= new vector<string>;

			for (int i=0; i<start_node->size_data; i++)
			{
				if (start_node->data->at(i)->at(start_node->decision_column) >start_node->decision_split)
					{
						right_node_data->push_back(start_node->data->at(i));
						right_node_flower->push_back(start_node->flower_data->at(i));
		
					}

				if (start_node->data->at(i)->at(start_node->decision_column)<=start_node->decision_split)
					{
						left_node_data->push_back(start_node->data->at(i));
						left_node_flower->push_back(start_node->flower_data->at(i));
					}
			}


			struct node* right_node=first_node(right_node_data, right_node_flower);
		
			start_node->right_child=right_node;
			right_node->parent=start_node;
		
			struct node* left_node=first_node(left_node_data, left_node_flower);
			left_node->parent=start_node;
			
			start_node->left_child=left_node;
			
			split_function_recursive(right_node);
			split_function_recursive(left_node);

		}

		if (homogeneous==true)
			{
												
				return start_node;			
			}

	}


	struct node* root_tree( struct node* last_pointer)
	{
		
		struct node* your_root=last_pointer;
		while (your_root->parent!=NULL)
				{
					your_root=last_pointer->parent;
					last_pointer=last_pointer->parent;
				}

		return your_root;
	}


	void print_root_only(node* root)
	{
		int column_split=root->decision_column+1;
		cout<< "Root: Split(A"<<column_split<<">"<<root->decision_split<<")"<<endl;

	}


	void print_tree(node* root)
	{
			
		int static indentation_counter=2;


		if (root->left_child!=NULL && root->left_child->is_it_homogeneous==true)	
			{
				print_space(indentation_counter);
				cout<<" Left leaf: "<<root->left_child->flower_data->at(0)<<" ("<<root->left_child->flower_data->size()<<")"<<endl;

			}
			
		if (root->right_child!=NULL && root->right_child->is_it_homogeneous==true)
			{
				print_space(indentation_counter);
				cout<<" Right leaf: "<<root->right_child->flower_data->at(0)<<" ("<<root->right_child->flower_data->size()<<")"<<endl;

			}

		if (root->left_child!=NULL && root->left_child->is_it_homogeneous==false)
			{
				print_space(indentation_counter);
				cout<<"Split A"<<root->left_child->decision_column<<">"<<root->left_child->decision_split<<endl;
				indentation_counter=indentation_counter+3;
				print_tree(root->left_child);
			}

		
		if (root->left_child!=NULL && root->right_child->is_it_homogeneous==false)
			{

				print_space(indentation_counter);			
				cout<<"Split A"<<root->left_child->decision_column<<">"<<root->left_child->decision_split<<endl;
				indentation_counter=indentation_counter+3;
				print_tree(root->right_child);


			}
	
	}


};

int main(int argc, char* argv[])
{
	
	string my_file_name=argv[1];
	vector< vector<double>* >* my_main_vector_data;
	my_main_vector_data=read_data(my_file_name);
	vector<string>* my_classification_data;
	my_classification_data=read_classification(my_file_name);
	
	int number_of_attributes=read_number_of_attributes(my_file_name);

	double entropy_flowers=entropy_classification(my_classification_data);
	
	string string_2=second_string(my_classification_data);

	struct max_gain* my_max_gain;

	decision_tree* my_tree=new decision_tree;
	struct node* leading_node=new struct node;

	leading_node=my_tree->first_node(my_main_vector_data, my_classification_data);
	//my_tree->print_node_content(leading_node);

	struct node* end_node = new struct node;
	struct node* root_node=new struct node;
	end_node=my_tree->split_function_recursive(leading_node);
	
	root_node=my_tree->root_tree(end_node);
	
	my_tree->print_root_only(root_node);
	my_tree->print_tree(root_node);

return 0;
}
