#include <iostream>
#include <limits> //for cin errors
#include <cstdio> //for printf()

using namespace std;

bool checkInput(int in);
int** placeMNums(int in);
void sumOfSquare(int **arr, int in);

int main(){
	cout << "\nINPUT>> Enter the size of a magic square: ";
	int sqNum; cin >> sqNum;

	/*
		The block of code below accounts for different possibilities on incorrect input.
		As such it prints errors for the user depending on the type of incorrect input they enter. 
	*/

	bool cond = checkInput(sqNum);
	
	do{
		if(checkInput(sqNum)){	
			cout << "\nSuccess!";	
			break;	
		}
		else{
			if(!cond)
				cout << "\nPlease enter valid input (an odd number between 3 and 15): ";
			while(!(cin >> sqNum)){
				cout << "\nPlease enter valid input (you entered input that was too large or not of data type \"integer\"): ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}	
	} while(!cond);

	int **arr = placeMNums(sqNum); 

	sumOfSquare(arr, sqNum); 

	for(int i=0; i<sqNum; ++i){ //deallocates space taken by dynamic array
		delete [] arr[i];
	}
	delete [] arr;

	return 0;
}

//verifies that the input is an odd number between 3 and 15
bool checkInput(int in){
	bool cond;

	switch(in){
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
			cond = true;
			break;
		default:
			cond = false; 
	}
	return cond;
}

//creates 2D array to store values of magic square, prints the square, and returns the 2D array
int** placeMNums(int in){
	int **mSquare = new int* [in]; //mSquare is 2D dynamic array, this line initializes the "rows"

	for(int i=0; i<in; ++i){
		mSquare[i] = new int[in]; //initializes "columns"
	}

	
	int num = 1;
	mSquare[0][in/2] = num; //algorithm involves placing 1 in middle of first row


	int i, j, countI; 
	int tempI=0, tempJ=0; 

	for(i=in-1, j=(in/2)+1, countI=0; countI < (in*in)-1; --i, ++countI){
		int countJ = 0;
		if(i < 0) //if "up and right" leaves square, wraps to last row
			i = in-1;
		while(countJ < 1){
			if(j == in) //if "up and right" leaves square, wraps to first column
				j=0;
			if(mSquare[i][j] != 0){ //checks to see if next spot in square has num
				i = tempI + 1;
				j = tempJ - 1;
			}
			mSquare[i][j] = ++num; //increments and places numbers in magic square
			++j;
			++countJ;
		}
		tempI = i;
		tempJ = j;
	}
	

	cout << "\nOUTPUT>> One magic square is: " << endl << endl;
	for(int k=0; k<in; ++k){ //prints out array
		for(int j=0; j<in; ++j)
			printf("%3d ", mSquare[k][j]);
		printf("\n");
	}

	return mSquare;

}

//calculates and prints the sums of every row, column, and diagonal in the magic square 
void sumOfSquare(int **arr, int in){
	int sumR, sumC, sumD1, sumD2;

	cout << "\nOUTPUT>> Checking the sums of every row: ";
	for(int i=0; i<in; ++i){
		sumR = 0;
		for(int j=0; j<in; ++j){
			sumR += arr[i][j];
		}
		cout << sumR << " ";
	}
	cout << endl;


	cout << "OUTPUT>> Checking the sums of every column: ";
	for(int j=0; j<in; ++j){
		sumC = 0;
		for(int i=0; i<in; ++i){
			sumC += arr[i][j];
		}
		cout << sumC << " ";
	}
	cout << endl;

	cout << "OUTPUT>> Checking the sums of diagonals: ";
	sumD1=0;
	for(int i=0, j=0; i<in; ++i, ++j){ //[0][0] to [in-1][in-1] diagonal
		sumD1 += arr[i][j];
	}
	cout << sumD1 << " ";	

	sumD2=0;
	for(int i=0, j=in-1; i < in; ++i, --j){ //[0][in-1] to [in-1][0] diagonal
		sumD2 += arr[i][j];
	}
	cout << sumD2 << " " << endl;
}






















