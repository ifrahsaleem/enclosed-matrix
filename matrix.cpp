//i//ifrah saleem 26238

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

bool InvalidChar(ifstream & file)
	//function that checks whether there are invalid char in the file 
{
	char ch;

	while(file.get(ch)) // read file char by char 
	{
		if( ch != 'x' && ch != 'o' && ch != ' ' && ch != '\n' && ch != '\t') // if the char is not x or o or whitespace 
		{
			file.seekg(0); // go back to the beginning of the file 
			return true; // returns that there is not an invalid char 
		}
	}
	file.clear(); 
	file.seekg(0); // go back to the beginning of the file 
	return false; // returns that there is an invalid char 
}

bool InvalidMatrix(ifstream & file, int & cols, int & row)
{
	char ch;
	int rownum = 0, rnum, count = 0;
	bool check = false;
	int r = 0;
	string line1;
	
	while(getline(file,line1)) // reading file line by line 
	{
		r++;
		row = r;
		istringstream ss(line1);
		while(ss >> ch)
		{
			rownum++; // counts number of cols in file 
		}

		if (count == 0)
		{
			rnum = rownum; // if first line of the file 
			count ++;
		}

		if(rnum != rownum) // if number of cols in previous row is not equal to cols in current row  
		{
			file.clear();
			file.seekg(0); // go to beginning of file
			check = true; 
			return check; // the matrix is invalid 
		}
		
		if(rnum == rownum) // if number of cols in previous row is equal to cols in current row 
			rownum = 0; // re-initialize number of cols to 0 
	}
	cols = rnum;
	file.clear();
	file.seekg(0);
	return check; // matrix is valid 
}

vector<vector<char>> StoreMatrix(int row, int cols, ifstream & file)
{
	char ch;
	vector<vector<char>> mat (row, vector<char>(cols));
	string line1;
	int R = 0, C =0;
	while(getline(file,line1)) // read file line by line 
	{
		istringstream ss(line1);
		
		while(ss >> ch)
		{
				mat[R][C] = ch; // new matrix stores the char
				C++;
		}
		C = 0;
		R++;
	}

	return mat;
}

void PrintMatrix(vector<vector<char>> & mat) // function that prints the stored matrix
{
	cout << endl << "Input Matrix: " << endl;

	for(unsigned int i = 0; i < mat.size(); i++) // iterate over the rows 
	{
		cout << endl;
		for(unsigned int j = 0; j < mat[0].size(); j++) // iterate over the columns
		{
			cout << mat[i][j] << " ";
		}

		cout << endl;

	}

	cout << endl;
}

bool CoordCheck(int x, int y, int row, int cols) // function that checks the validity of the coordinates 
{
	if ( x == -1 && y == -1) // if X = -1 & Y = -1
		return true; // coordinates are valid 

	else if ( x < 0 || y < 0) // if either X or Y is negative 
		return false; // coordinate is invalid 

	else if (x > row-1 || y > cols-1) // if X or Y coordinate is greater than the number of rows or columns respectively 
		return false; // invalid coordinate 

	else 
		return true; // valid coordinate 
}

void PathCoord(vector<int> vec_x, vector<int> vec_y, bool enclosed_area) // function that prints the coordinates of visited cells, stored in vec_x and vec_y
{
	int x = 0, y = 0;

	cout << endl; 

	if (enclosed_area)
		cout << endl << "Found an enclosed area. The coordinates of the followed path: " << endl;
	else
		cout << endl << "Cannot found an enclosed area starting with given coordinate. The coordinates of the followed path: " << endl;

	while ( x != (vec_x.size()) && y != (vec_y.size()))
	{
		cout << endl << vec_x[x] << " " << vec_y[y] << endl;
		x++;
		y++;
	}
}

void Pathway(vector<vector<char>> & mat, int row, int cols, int x, int y)
{
	bool check = true, enclosed_area = false;
	vector<vector<int>> mymat(row,vector<int>(cols, 0)); // another matrix to keep track of visited cells, initially all cells are 0
	vector<int> vec_x, vec_y; // vectors storing visited x and y coordinates 
	char current = mat[x][y];
	int start_cell_x = x;
	int start_cell_y = y;
	mymat[x][y] = 1;
	vec_x.push_back(x);
	vec_y.push_back(y);
	int move = 0;

	while (check) 
	{
		//*** Nine Test Cases ***//

		if (x == 0 && y == 0) // very first cell first row, first column 
		{ 
			enclosed_area = false;
			int X = x;
			int Y = y;
			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right // if right cell has x and unvisited 
			{
				current = mat[x][y+1];
				mymat[x][y+1] = 1; // the current cell is now visited 
				y = y + 1; // changing the previous value of y to current y
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}
			
			else if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down // if down cell has x and unvisited 
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1; // / the current cell is now visited 
				x = x + 1; // changing the previous value of x to current x
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else 
			{
				check = false; // there is no neighboring cell which is x and unvisited
			}

			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 ) // if previously visited cell on the bottom is x
			{
				if (X + 1 == start_cell_x && Y == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}

			if(mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1) // if previously visited cell on the right is x
			{
				if (X == start_cell_x && Y + 1 == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway
				}
			}

		}

		//--------------------------------------------------------------------------------------------------------------------------

		else if (y > 0 && y < cols-1 && x == 0) // first row, 2nd column till 2nd last column 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right // if right cell has x and unvisited 
			{
				current = mat[x][y+1];
				mymat[x][y+1] = 1; // the current cell is now visited 
				y = y + 1; // changing the previous value of y to current y
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}
			
			else if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down // if down cell has x and unvisited 
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1; // / the current cell is now visited 
				x = x + 1; // changing the previous value of x to current x
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left // if left cell has x and unvisited
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1; // current cell is now visited
				y = y - 1; // changing previous value of y to current y
				vec_x.push_back(x);//updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}
			
			if(mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1) // if previously visited cell on the right is x
			{
				if (X == start_cell_x && Y + 1 == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway
				}
			}

			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 ) // if previously visited cell on the bottom is x
			{
				if (X + 1 == start_cell_x && Y == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1) // // if previously visited cell on the left is x
			{
				if (X == start_cell_x && Y - 1 == start_cell_y) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}
		}

		//----------------------------------------------------------------------------------------------------------------------------

		else if (y == cols - 1 && x == 0) // last column, first row 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down // if down cell has x and unvisited 
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1; // / the current cell is now visited 
				x = x + 1; // changing the previous value of x to current x
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}
			else if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left // if left cell has x and unvisited
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1; // current cell is now visited
				y = y - 1; // changing previous value of y to current y
				vec_x.push_back(x);//updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}
			
			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 ) // if previously visited cell on the bottom is x
			{
				if (X + 1 == start_cell_x && Y == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1) // // if previously visited cell on the left is x
			{
				if (X == start_cell_x && Y - 1 == start_cell_y) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}
		}

		//---------------------------------------------------------------------------------------------------------------

		else if (y == 0 && x > 0 && x < row -1) // first column, from 2nd to 2nd last row 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right // if right cell has x and unvisited 
			{
				current = mat[x][y+1];
				mymat[x][y+1] = 1; // the current cell is now visited 
				y = y + 1; // changing the previous value of y to current y
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}
			
			else if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down // if down cell has x and unvisited 
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1; // / the current cell is now visited 
				x = x + 1; // changing the previous value of x to current x
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up // if up cell has x and unvisited
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1; // / the current cell is now visited 
				x = x - 1; // changing the previous value of x to current x
				vec_x.push_back(x); //updating vectors with new coordinates 
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}

			if(mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1) // if previously visited cell on the right is x
			{
				if (X == start_cell_x && Y + 1 == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway
				}
			}

			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 ) // if previously visited cell on the bottom is x
			{
				if (X + 1 == start_cell_x && Y == start_cell_y && move != 1) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway 
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1) // if previously visited cell on the top is x
			{
				if (X - 1== start_cell_x && Y == start_cell_y) // check whether its the first movement and whether the coordinates are the 
					                                                         // starting coordinates
				{
					enclosed_area = true; // it is an enclosed pathway
				}
			}
		}
		
		//---------------------------------------------------------------------------------------------------------------------

		else if (x > 0 && x < row -1 && y == cols - 1) // last column, from 2nd row till 2nd last row 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1;
				x = x + 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1;
				y = y - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1;
				x = x - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1)
			{
				if (X == start_cell_x && Y - 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 && move != 1)
			{
				if (X + 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1 )
			{
				if (X - 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}

		}

		//--------------------------------------------------------------------------------------------------------------

		else if (x > 0 && x < row -1 && y > 0 && y < cols-1) // 2 column till 2nd last column, 2 row till 2nd last row
		{
			enclosed_area = false;
			int X  = x;
			int Y = y;

			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right 
			{

				current = mat[x][y+1];
				mymat[x][y+1] = 1;
				y = y + 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x+1][y] == 'x' && mymat[x+1][y] == 0)//down
			{
				current = mat[x+1][y];
				mymat[x+1][y] = 1;
				x = x + 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1;
				y = y - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1;
				x = x - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1)// && Y - 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y - 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1 && move != 1)//&& Y + 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y + 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X+1][Y] == 'x' && mymat[X+1][Y] == 1 && move != 1)// && (X + 1) != prev_move_y && X != prev_move_x)
			{
				if (X + 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1)//&& (X - 1) != prev_move_y && Y != prev_move_x)
			{
				if (X - 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}
		}

		//---------------------------------------------------------------------------------------------------------

		else if (x == row - 1 && y == 0) // first column, last row 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right 
			{
				current = mat[x][y+1];
				mymat[x][y+1] = 1;
				y = y + 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1;
				x = x - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}

			if (mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1 && move != 1)// && Y + 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y + 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1)// && X - 1 != prev_move_y && Y != prev_move_x)
			{
				if (X - 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}
		}

		//------------------------------------------------------------------------------------------------------

		else if ( x == row - 1 && y > 0 && y < cols-1) // last row, 2nd column to 2nd last column
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x][y+1] == 'x' && mymat[x][y+1] == 0 )// right 
			{
				current = mat[x][y+1];
				mymat[x][y+1] = 1;
				y = y + 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1;
				y = y - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1;
				x =  x - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}

			else
			{
				check = false;
			}

			if (mat[X][Y+1] == 'x' && mymat[X][Y+1] == 1 && move != 1 )//&& Y + 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y + 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1 )//&& Y - 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y + 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1 )//&& X - 1 != prev_move_y && X != prev_move_x)
			{
				if (X - 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}
		}

		//-------------------------------------------------------------------------------------------------------

		else if (x == row -1 && y == cols - 1) // last row, last column 
		{
			enclosed_area = false;
			int X = x;
			int Y = y;

			if (mat[x][y-1] == 'x' && mymat[x][y-1] == 0)//left
			{
				current = mat[x][y-1];
				mymat[x][y-1] = 1;
				y = y - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else if (mat[x-1][y] == 'x' && mymat[x-1][y] == 0)//up
			{
				current = mat[x-1][y];
				mymat[x-1][y] = 1;
				x = x - 1;
				vec_x.push_back(x);
				vec_y.push_back(y);
			}
			else
			{
				check = false;
			}

			if (mat[X][Y-1] == 'x' && mymat[X][Y-1] == 1 && move != 1)// && Y - 1 != prev_move_y && X != prev_move_x)
			{
				if (X == start_cell_x && Y + 1 == start_cell_y)
				{
					enclosed_area = true;
				}
			}

			if (mat[X-1][Y] == 'x' && mymat[X-1][Y] == 1 && move != 1 )//&& X - 1 != prev_move_y && Y != prev_move_x)
			{
				if (X - 1== start_cell_x && Y == start_cell_y)
				{
					enclosed_area = true;
				}
			}
		}
		move++; // counts the number of moves 
	}
	PathCoord(vec_x, vec_y, enclosed_area);
}

int main()
{
	string fname, s, f;
	ifstream input1;
	int cols, row;
	bool checker = false;
	vector<vector<char>> mat;

	do
	{
		cout << "Please enter file name: " ;
		cin >> fname; // entering file name 

		input1.open(fname.c_str()); // opening file 

		if (input1.fail()) // if file fails to open
			cout << endl << "Cannot find a file named " << fname << endl << endl;
	} while (input1.fail()); // keep asking until file successfully opens

	if(InvalidChar(input1)) // if the file includes invalid char
		cout << endl << fname << " includes invalid char(s)" << endl;
	
	else if(InvalidMatrix(input1, cols, row))// if file does not include a valid matrix
		cout << endl << fname << " is invalid matrix, does not contain same amount of char each row!" << endl;
 
	else // if file includes valid char and valid matrix 
	{
		mat = StoreMatrix(row, cols, input1); // function that stores the matrix by reading file 
		PrintMatrix(mat); // function that prints the stored matrix 
		int X, Y;
		
		do
		{
			cout << endl << "Please enter starting coordinates, first row X then column Y: " ;
	
			if (cin >> X >> Y) // if coordinates entered are integers
			{
				checker = CoordCheck(X, Y, row, cols); // function that checks of coordinates are correct 
				if (checker == true) 
				{
					if (Y != -1 && X != -1 && mat[X][Y] != 'o') // if the X and Y coordinate are not -1 and the cell is not unoccupied
					{
						Pathway(mat, row, cols, X, Y); // function that finds the pathway 
					}
				}
			}

			else // if coordinates are not integer
			{
				cin.clear();  
				cin >> s >> f;
			}

			if (X == -1 && Y == -1) // if coordinates are X = -1 and Y = -1
				cout << endl << "Terminating... " << endl; 

			else if (checker == false) // if coordinates are invalid 
			{
				cout << endl << "Invalid Coordinates" << endl;
			}

			else if (checker == true && mat[X][Y] == 'o') // if the coordinates are correct but the cell is unoccupied 
				cout << endl << "This cell is not occupied!" << endl; 

		} while (((X != -1) && (Y != -1))); // keep asking coordinates until X = -1 and Y = -1 are not entered 
	}
	return 0;
}