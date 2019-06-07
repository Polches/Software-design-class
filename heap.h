#include <iostream>
using namespace std;

class Heap{
public:
   //my variables
   int* A ; // Array containing heap contents.

   int swaps=0;
   Heap(); 
   // Destructor.
   ~Heap(); 

    bool empty() const {return Size == 0;}; 
    void insert( int element); //insert element and restore order
    int remove_min(); //remove root since it's a min heap
    int Capacity ; // Max number of elements (= size of A).
    int Size ; // Current number of elements.

  //repair heap order start from heap buttom
   void go_up_restore(int i);
    //restore order start from top and go down
   void go_down_restore(int i);
    //for swapping array elements
   void swap(int i,int j);

    //to acces left child
   int leftchild(int i);
   //to acces right child index
   int rightchild(int i);
   //to acces parent
   int parent(int i);


   bool isLeft(int i);
   bool isRight(int i);
   void print();
   
};


void Heap::print(){
	for (int i=0; i<Size; i++)
	{
		cout<<A[i]<<" ";}
	cout<<endl;}


Heap::Heap(){
   Capacity = 10000 ; //max number of elements 
   A = new int[Capacity]; //it's an array A of size capacity which contains integers
   Size = 0 ; //curent number of elements 
}

// Destructor
Heap::~Heap(){
   delete[] A; //we delete array A
}


void Heap::insert(int element){
   
   A[Size] = element; //we insert element
   go_up_restore(Size); //restores order. starts from buttom goes to top
   Size ++; //then we increase size
}


bool Heap::isLeft(int i){
	return (i*2+1)<Size; }

bool Heap::isRight(int i){
	return (i*2+2)<Size; 
}

//return is index of left child
int Heap::leftchild(int i){
	if (isLeft(i)){
		return (i*2+1);} 
	}
	

//return is index of right child
int Heap::rightchild(int i){
	
	if (isRight(i))
	{
	return (i*2+2);}
}


int Heap::parent(int i){
	return ((i-1)/2);
}

//repair heap oreder
void Heap::go_up_restore(int i){
	if (A[i]<A[parent(i)]) //compare
	{swap(i, parent(i));
	go_up_restore(parent(i));} //use recursion 
}




void Heap::swap(int i, int j){
    //then we swap array elements
   int temp = A[i];
   A[i] = A[j];
   A[j] = temp ;
   swaps=swaps+1;
}

//remove root
int Heap::remove_min(){

	int store_root=A[0];
	A[0]=A[Size-1]; //root becomes last element

	Size=Size-1; //decrease size

	go_down_restore(0); 

	return store_root; 
}


//we want to restore order from top after root removal
void Heap::go_down_restore(int i){ 

if (isLeft(i)==false && isRight(i)==false)
	{return;}

if (isRight(i)==false && A[i]>A[leftchild(i)])
    {
	swap(i, leftchild(i));
	return;
    }

if (isRight(i)==false && A[i]<A[leftchild(i)])
	{return;}

if(A[leftchild(i)]<=A[rightchild(i)] && isRight(i)==true)
    {
	if (A[i]>A[leftchild(i)]){
		swap(i, leftchild(i));
		//cout<<"I am here"<<endl;
		go_down_restore(leftchild(i));}
	else{
		return;}
    }

if(A[leftchild(i)]>=A[rightchild(i)] && isRight(i)==true)
    {
	if (A[i]>A[rightchild(i)])
	    {
		swap(i, rightchild(i));
		go_down_restore(rightchild(i));
	        
	    }
	else
	    {
		return;
	    }
    }



}





/*

int main()
{
    //CReate a heap with 10 elements randomly generated
    
    Heap* my_heap=new Heap();
    int random_number;
    int heap_size=500;
    for (int i=0; i<heap_size; i++)
    {
        random_number=rand()%1000;
        my_heap->insert(random_number);
    }
    
    
   //cout<<"My heap is "<<endl;
    //my_heap->print();
    
    //create an array
    
    int* my_array=new int[heap_size];
    
    for (int i=0; i<heap_size; i++)
    {
        my_array[i]=my_heap->remove_min();
        
    }
    
    cout<<"my sorted array is "<<endl;
    for (int i=0; i<heap_size; i++)
    {
       cout<<my_array[i]<<" ";
        
    }
    
    cout<<endl;
    
    
    
    



    return 0;
}
*/