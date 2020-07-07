#include<stdio.h>
#include <Windows.h>
#include<time.h>
#include<wincon.h>
#include<math.h>




void hanoi(int pegs, int start, int end, int temp);
void initialize(int);
void print_grid();
void move(int from, int to);




#define ROW 15
#define COL 71
#define TOW_HEIGHT 12
#define GRID_OFFSET 10
#define TOW_DIST 22
#define PAUSE_TIME 20

//num codes for displaying the grid
#define TOW 1
#define PEG 2
#define BLANK 0



/*Note that the grid will be printed such that row 0 will
be at the bottom.*/
int grid[ROW][COL] = { BLANK };

//columns numbers for the three towers 0,1 and 2
int tow_location[3] = { 12, 35, 58 };

//number of pegs in each tower at any time
int num_pegs[3];

/*a 2d array in addition to the grid. Each element corresponds to a spot
on the tower and each number being the size of peg at that spot. Zero
means no peg*/
int tower[TOW_HEIGHT][3];

HANDLE console;



void main(void)
{
	int tot_pegs;
	printf("Enter Number of Pegs:");
	scanf_s("%d", &tot_pegs);
	system("cls");
	console = GetStdHandle(STD_OUTPUT_HANDLE);



	initialize(tot_pegs);
	print_grid();
	puts("\n\n\n\n");
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
	system("pause");

	
	hanoi(tot_pegs, 0, 2, 1);
	
	puts("\n\n\n\n");
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	system("pause");
}//end main


void hanoi(int pegs, int start, int end, int temp)
{

	if (pegs == 1)
	{
		move(start, end);
		return;
	}

	hanoi(pegs - 1, start, temp, end);
	move(start, end);
	hanoi(pegs - 1, temp, end, start);









}
//------------------------------------------------------------------------------------------------------------------------------------------

/*Initializes the global variables so that
there are 4 pegs in tower 0*/
void initialize(int tot_pegs)
{
	int row, col;
	//initializing towers
	for (col = tow_location[0]; col <= tow_location[2]; col += TOW_DIST + 1)
	{
		for (row = 0; row < TOW_HEIGHT; row++)
		{
			grid[row][col] = TOW;
		}
	}

	//initializing the four pegs on tower 0
	num_pegs[0] = tot_pegs;

	int peg_size = tot_pegs;

	for (row = 0; row < tot_pegs; row++, peg_size--)
	{
		tower[row][0] = peg_size;
		for (col = tow_location[0] - peg_size; col <= tow_location[0] + peg_size; col++)
		{

			grid[row][col] = PEG;
		}

	}



}
//------------------------------------------------------------------------------------------------------------------------------------------


void print_grid()
{
	int row, col;
	COORD cursor;
	cursor.X = cursor.Y = 0;

	//first print the boundary only----------------------------------------------------------
	SetConsoleTextAttribute(console, BACKGROUND_BLUE);

	cursor.X = GRID_OFFSET; cursor.Y = GRID_OFFSET / 2;
	SetConsoleCursorPosition(console, cursor);

	//top boundary
	for (col = 1; col <= COL+2 ; col++)
		printf(" ");


	//printing side boundaries
	for (row = 1; row <= ROW; row++)
	{
		cursor.Y++; cursor.X = GRID_OFFSET;
		SetConsoleCursorPosition(console, cursor);
		printf(" ");

		cursor.X += COL + 1;
		SetConsoleCursorPosition(console, cursor);
		printf(" ");

	}
	cursor.Y++; cursor.X = GRID_OFFSET;
	SetConsoleCursorPosition(console, cursor);
	//bottom boundary
	for (col = 1; col <= COL+2 ; col++)
		printf(" ");


	//now print the towers only------------------------------------------------------------------------
	int x_init = GRID_OFFSET + 1, y_init = (GRID_OFFSET / 2) + 1;
	SetConsoleTextAttribute(console, BACKGROUND_RED);
	
	for (row = ROW - 1; row >= 0; row--)
	{
		for (col = 0; col < COL; col++)
		{
			if (grid[row][col] == TOW)
			{
				cursor.X = x_init + col;
				cursor.Y = y_init + ROW - row-1;
				SetConsoleCursorPosition(console, cursor);
				printf(" ");
			}
		}
	}
	
	//now print the pegs only--------------------------------------------------------------------------
	SetConsoleTextAttribute(console, BACKGROUND_GREEN);

	for (row = ROW - 1; row >= 0; row--)
	{
		for (col = 0; col < COL; col++)
		{
			if (grid[row][col] == PEG)
			{
				cursor.X = x_init + col;
				cursor.Y = y_init + ROW - row - 1;
				SetConsoleCursorPosition(console, cursor);
				printf(" ");
			}
		}
	}
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);




}
//------------------------------------------------------------------------------------------------------------------------------------------

/*moves the peg from indicated tower to indicated tower*/
void move(int from, int to)
{
	system("cls");
	int peg_size = tower[num_pegs[from] - 1][from], row, col;//size of the peg to be moved

	//First to remove the peg from indicated tower

	for (row = num_pegs[from]; row <= TOW_HEIGHT + 1; row++)
	{
		for (col = tow_location[from] - peg_size; col <= tow_location[from] + peg_size; col++)
		{
			
			grid[row][col] = PEG;
			grid[row - 1][col] = ((col==tow_location[from]&&row<=TOW_HEIGHT)?TOW:BLANK);

		}

		print_grid();
		Sleep(PAUSE_TIME);
		system("cls");
	}row--;

	//now to move the peg towards the indicated tower
	int	sign = (tow_location[to] - tow_location[from]) / abs(tow_location[to] - tow_location[from]);
	int	centre_of_peg = tow_location[from];


	for (; centre_of_peg != tow_location[to]; centre_of_peg += sign)
	{
		grid[row][centre_of_peg + sign*(peg_size + 1)] = PEG;
		grid[row][centre_of_peg - sign*peg_size] = BLANK;
		print_grid();
		Sleep(PAUSE_TIME);
		system("cls");
	}


	//now to bring er down
	for (row--; row >= num_pegs[to]; row--)
	{
		for (col = tow_location[to] - peg_size; col <= tow_location[to] + peg_size; col++)
		{

		


			grid[row][col] = PEG;
			grid[row + 1][col] = ((col == tow_location[to]) && (row <= TOW_HEIGHT-2) ? TOW : BLANK);



		}

		print_grid();
		Sleep(PAUSE_TIME);
		system("cls");
	}

	//updating records
	tower[num_pegs[from] - 1][from] = 0;
	tower[num_pegs[to]][to] = peg_size;
	num_pegs[from]--;
	num_pegs[to]++;



	print_grid();
}