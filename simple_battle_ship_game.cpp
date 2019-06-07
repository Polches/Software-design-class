#include <cstdlib>
#include <iostream>
using namespace std;


//Why should I use heap memory allocation instead of stack?



class Board{
	//I make everything public now
public:
	//my variables
	char** grid;
	int x_coordinate;
	int y_coordinate;
	//my functions
	//print function.I need to print a 2-D array
	void print_board();
	void put_Battleship();

	void fill_the_board();
	void put_cruiser();
	void put_cargo_ship(); //A cargo ship. Length 2. Five of those.
	void put_submarine(); //size is 1. symbol is _. number of them os 10.
	//void pit_cargo_ship();
	Board();//constructor, for memory allocation
	~Board();//destructor, to free allocated memeory

};


Board::Board(){

	//cout<<"i AM INSIDE A CONSTRUCTOR"<<	endl;
	grid=new char*[8];
	int filled=0;
	while (filled!=8){
		char* line=new char[8]; //line is a pointer to an array of size 8
		grid[filled]=line; 
		filled=filled+1;
   }
}





Board::~Board()
{
	//Before I can remove board array, I need to remove sub arrays;

	for (int i=0; i<8; i++)
	{
		delete[] grid[i];
	}

	delete[] grid;
}


void Board::put_Battleship(){

	//First I need to generate coordinates;
	//grid[1][1]='B';
	x_coordinate=rand()%8;
	//cout<<"Generated x coordinate is "<<x_coordinate<<endl;
	//i have restruictios for y corrdinate
	//I need to have at least 4 cells to put Battleship vertically	
	y_coordinate=rand()%8;

	bool valid=false;
	while (valid==false){
		if (x_coordinate>=5){ //if y>= 5 then it's an invalid coordinate and we need a new one
			x_coordinate=rand()%8;}

		else{
			valid=true;	}
		}
//now I have good valid coordinates
//I changed my int array into char array

		if (valid==true) {
		  int add=0;
		  for (int i=0; i<4; i++){
			
		    grid[x_coordinate+i][y_coordinate]='B';

          }
		//add=add+8;
		}


		//cout<<"Generated y coordinate is "<<y_coordinate<<endl;


}


//now I need to put a cruisor. size of which is 3.

void Board::put_cruiser(){
	//the first I need to do is to generate random coordinates
	for (int i=0; i<2; i++)
	{
		x_coordinate=rand()%8;
		y_coordinate=rand()%8;
		//I must make sure I dont go outside of the scope for cruisor
		//I must make sure that I dont go into the same cells as my battleship
		bool valid_cell=false;

		while (valid_cell==false)
		{
		 	if (grid[x_coordinate][y_coordinate]!=' ' || x_coordinate>=6 ||
		 	 	grid[x_coordinate+1][y_coordinate]!=' ' || grid[x_coordinate+2][y_coordinate]!=' ')

		 	{
		 		valid_cell=false;
		 		x_coordinate=rand()%8;
		 		y_coordinate=rand()%8;
		 	}
		 	else
		 	{
		 		valid_cell=true;
		 	}

		}

			grid[x_coordinate][y_coordinate]='C';
			grid[x_coordinate+1][y_coordinate]='C';
			grid[x_coordinate+2][y_coordinate]='C';


	}
	
}



void Board::put_cargo_ship(){

	//I need to put 5 cargo ships length of 2. 


	for (int i=0; i<5; i++)

	{
		x_coordinate=rand()%8;
		y_coordinate=rand()%8;
		bool valid_cell=false;

		while(valid_cell==false)
		{

			if (7==x_coordinate || grid[x_coordinate][y_coordinate]!=' ' || grid[x_coordinate+1][y_coordinate]!=' ')
			{
				valid_cell=false;
				x_coordinate=rand()%8;
				y_coordinate=rand()%8;

			}
			else
			{
				valid_cell=true;
				break;
			}
		}	

		grid[x_coordinate][y_coordinate]='S';
		grid[x_coordinate+1][y_coordinate]='S';
	}
}




void Board::print_board(){

	cout<<"--------------------------"<<endl;
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			cout<<grid[i][j];
		}
		cout<<endl;}
	cout<<"---------------------------"<<endl;

}



void Board::fill_the_board()
{
	//so I have my grid and I am just gonna fill it 

	///cout<<"I am inside fill the board function"<<endl;
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			//cout<<"I am inside a nested loop in my fill the board function"<<endl;
			//cout<<"my x and y coordinates are "<<i<<" "<<j<<endl;
			grid[i][j]= ' ';
		}
	}
}


void Board::put_submarine()
{

	for (int i=0; i<10; i++)
	{
		x_coordinate=rand()%8;
		y_coordinate=rand()%8;

		bool valid_cell=false;

		while(valid_cell==false)
		{
			if (grid[x_coordinate][y_coordinate]!=' ')
			{
				x_coordinate=rand()%8;
				y_coordinate=rand()%8;
			}
			else
			{
				valid_cell=true;
			}		
		}

		grid[x_coordinate][y_coordinate]='_';
	}

}



int main(){

	cout<<"I am here inside main program"<<endl;
	for (int i=0; i<100; i++)
	{
		Board* my_board=new Board();
		my_board->fill_the_board(); //I fill the boeard with empty spaces
		my_board->put_Battleship(); //Now I put battle ship inside the board
		//my_board->print_board();   //

		//cout<<"Here ia m gonna use put_cruiser function"<<endl;
		my_board->put_cruiser();
		my_board->put_cargo_ship();
		my_board->put_submarine();
		my_board->print_board();

		delete my_board;

	}
	return 0;
}
