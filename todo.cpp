//
//  COMP 2012H Programming Assignment 1: Sudoku
//  Filename: todo.cpp
//  - This is the file you need to submit to Canvas.
//  - Remember to create a zip file with this file.
//  - The zip file should be named todo_<STUDENTID>.zip.
//

#include "helper.h"
#include "todo.h"
#include <iostream>
#include <algorithm>
/***********************************************************************
 * TODO_1: Check whether the inserted value is compliant
 *         with the rules of Sudoku.
 ***********************************************************************/

bool input_is_valid(int value, int row, int col, const char grid[][9]) {
	/// ADD YOUR CODE HERE
	// hey please enter a number in[1..9].
	if (value>9 || value <1) return false;

	char valToGrid =(value+'0');
	// row and column
    for (int i=0;i<9;i++){
    	if ( valToGrid == grid[row][i]) return false;
    	if ( valToGrid == grid[i][col]) return false;
    }
    // for the square
    for (int j= 3*(col/3) ; j<3*(col/3) +3 ; j++){

    	for (int i= 3*(row/3); i<3*(row/3) +3; i++) {
    	//	cout<< valToGrid << "compare "<<grid[i][j] <<endl;
    		if ( valToGrid == grid[i][j]) return false;
    	}
    }

    return true;
}

/***********************************************************************
 * TODO_2: Ask coordinate inputs from the user, and a value to insert.
 *         Check whether the user's input is valid. If the user's input
 *         is valid, insert the value and update the current grid.
 *         Otherwise, print an error message.
 ***********************************************************************/

void edit_cell(const char initial_grid[][9], char grid[][9]) {
	/// ADD YOUR CODE HERE
	cout << "Enter the coordinates of the cell:" ;
	char arr[2]; // for cin
	int value;
	int col=0;

	cin >> arr[0] >> arr[1] ;
	cout<<endl;
	cout << " Enter the value at \' " << arr[0] << arr[1] << " \': ";
	cin >> value;

	if (arr[0] < 'a') col = arr[0] - 'A'; // assume no input mismatch.
		else col = arr[0]- 'a';
	int row = arr[1] -'1'; // the 1st row is row 0 -_-

	if(grid[row][col] != ' '){
		cout << "ERROR: Cell \'" << arr[0] << arr[1] << "\' is read-only";
		return;
	}

	bool isValid = input_is_valid(value,row,col,grid);

	if (isValid ==false ){
		cout << "Error: value \'" << value << "\' in cell \' " << arr[0] << arr[1] <<"\' is invalid";
		return;
	}

	grid[row][col] = value+'0';
}

/***********************************************************************
 * TODO_3: Ask coordinate inputs from the user. Remove the value from
 *         the current grid if the cell has not been filled in the
 *         beginning.
 ***********************************************************************/

void remove_cell(const char initial_grid[][9], char grid[][9]) {
	/// ADD YOUR CODE HERE
	    cout << "Enter the coordinates of the cell:";
		char arr[2]; // for cin
		cin >> arr[0] >>arr[1];

		int col=0;
		    if (arr[0] <'a') col = arr[0] - 'A';
			else col = arr[0]- 'a';
		    // same as edit cell above
		int row = arr[1] -'1';

		if(initial_grid[row][col]!=' '){
			cout << "ERROR: Cell \'" << arr[0] << arr[1]  << "\' is read-only";
			return;
		}

		grid[row][col]  = initial_grid[row][col] ; // reset to  empty. The initial value must be empty.

}

/***********************************************************************
 * TODO_4: Check whether all the cells in the grid have been
 *         correctly filled.
 ***********************************************************************/

bool check_end_game(const char grid[][9]) {
	/// ADD YOUR CODE HERE
	for (int j=0;j<9;j++)
		for (int i=0;i<9;i++)
			if (grid[i][j] == ' ') return false;	// if there is a empty spot it is not the end.
	return true; // the end.
}

/***********************************************************************
 * TODO_5: Automatic Sudoku solver.
 *         Complete all the empty cells with the
 *         correct solution if it exists.
 ***********************************************************************/

bool sudoku_solver(char grid[][9]) {
	/// ADD YOUR CODE HERE
	if (check_end_game(grid))return true; //if the grid is filled then this is solved.
	int Row,Col;
    Row=Col=0;
    while(grid[Row][Col] !=' ' ){
    		if (Col < 8) {
    			Col = Col+1;
    		}
    		else{
    			Row++;
    			Col= 0;
    		}
    }
    for (int i=1;i<10;i++)// who will win : int i=1 or int candidate  = 1???
    	if ( input_is_valid(i,Row,Col,grid) ) { //find a valid input
    		grid[Row][Col]=i+'0';
    		if (sudoku_solver(grid))//go recursion
    			return true;
    		grid[Row][Col] = ' ';
    	}
    //if the for loop ends without returning true , no value can satisfy the cell.
    return false;
}

/***********************************************************************
 * TODO_6: Generate a complete valid board.
 ***********************************************************************/
int myRandom(int i) { return rand() % i; }
bool generate_board(char grid[][9]) {
	/// ADD YOUR CODE HERE
	if (check_end_game(grid))return true;
		int Row,Col;
	    Row=Col=0;
	    while(!(grid[Row][Col]==' ')){
	    	if (Row < 9)
	    	{
	    		if (Col < 8) {
	    			Col = Col+1;
	    		}else{
	    			Row++;
	    			Col= 0;
	    		}
	    	}
	    }
	    int value[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		random_shuffle(&value[0], &value[9], myRandom);
		int ranNum =0;
	    for (ranNum=0;ranNum<9;ranNum++)
	    	if (input_is_valid(value[ranNum],Row,Col,grid)){
	    		grid[Row][Col]=value[ranNum]+'0';//randomly put a input into the grid
	    		break;
	    	}
	    if (ranNum==9) return false;
	    // if value is false in the next grid
	    while (!generate_board(grid) ){
	    	ranNum++; // go to the next input.
	    	while(ranNum<9)
	    		{	if (input_is_valid(value[ranNum],Row,Col,grid)){
	    				grid[Row][Col]=value[ranNum]+'0';
	    				break;
	    				}
	    			ranNum++;
	    		}
	    	if (ranNum>=9) {
	    		grid[Row][Col]=' ';
	    		return false;
	    	}
	    }
	    return true;
}

/***********************************************************************
 * TODO_7: Generate a Sudoku puzzle with unique solution.
 ***********************************************************************/
int sudoku_uniqueCounter(char grid[][9] ,short count) {
	/// ADD YOUR CODE HERE
	if (check_end_game(grid)) return 1+count; //base case is filled grid;
	int Row,Col;
    Row = Col = 0 ;
    while( grid[Row][Col] != ' ' ){
    	if (Col == 8 ) {
			Col = 0 ;
			Row = Row +1;
			if (Row == 9) return count+1 ;// for checking purpose
		}
    	else Col = Col + 1 ;

    }
    int j=0;
	// try to find 2 solutions
    for (int i=1; i<=9 && count <2 ; ++i ){
       	if (input_is_valid(i,Row,Col,grid)){
       		//find a valid input
   			grid[Row][Col]=i+'0';
   			count = sudoku_uniqueCounter(grid, count);
   			j++;
   			grid[Row][Col] =' ';    // reset grid is needed for recursive use
       	}
   	}
    // when the for loop is done go to this part.
    return count;// the count is important so return it
}
void generate_unique_puzzle(char grid[][9]) {			
	/// ADD YOUR CODE HERE
	int pos[81];
	for(int i=0;i<81;++i)
		pos[i]=i;
	random_shuffle(&pos[0],&pos[81],myRandom);
	// e is the number of position tested (entry )
	for(int e =0; e < 81; ++e){
		 int Row,Col;
		 Row= Col =0;
		 int  Cur = 0;// current value.
		 while(pos[e] != Cur) {
			 Cur++;
			 if (Col < 8) {
			  Col = Col+1;
			    }
			 else{
				 Row= Row +1;
			    Col= 0;
			    }
		}
		char CVal = grid[Row][Col]; //store value for undo purpose
		grid[Row][Col]=' ';		 // set to empty
		char Dgrid[9][9];
		duplicate_grid(grid,Dgrid);
		if (sudoku_uniqueCounter(Dgrid,0) != 1)// try to find if it is unique
				grid[Row][Col] = CVal ;  // undo
	}
}


