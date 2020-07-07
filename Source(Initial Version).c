#include<stdio.h>
#include <Windows.h>
#include<time.h>
#include<wincon.h>
#include<math.h>




void hanoi(int pegs,int start, int end, int temp);
void initialize(int );
void print_code(int code);
void print_grid();
void move(int from,int to);




#define ROW 15
#define COL 71
#define TOW_HEIGHT 12
#define GRID_OFFSET 10
#define TOW_DIST 22
#define PAUSE_TIME 0.1

//num codes for displaying the grid
#define TOW 1
#define PEG 2
#define BLANK 0



/*Note that the grid will be printed such that row 0 will
be at the bottom.*/
int grid[ROW][COL] = { BLANK };

//columns numbers for the three towers 0,1 and 2
int tow_location[3] = {12, 35, 58 };

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
	system("pause");

	char buffer[1000];
	setvbuf(stdout, buffer, _IOFBF, sizeof(buffer));
	hanoi(tot_pegs, 0, 2, 1);

	puts("\n\n\n\n");
	fflush(stdout);
	system("pause");
}//end main


void hanoi(int pegs,int start, int end, int temp)
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

	for (row = 0; row < tot_pegs; row++,peg_size--)
	{
		tower[row][0] = peg_size;
		for (col = tow_location[0] - peg_size; col <= tow_location[0] + peg_size; col++)
		{
			if (col == tow_location[0])
				continue;

			grid[row][col] = PEG;
		}
		
	}



	




}
//------------------------------------------------------------------------------------------------------------------------------------------

//prints a char based on the given code
void print_code(int code)
{
	char to_print;
	
	switch (code)
	{
	case BLANK:
		to_print = ' ';
		break;

	case TOW:
		to_print = '|';
		break;
	case PEG:
		to_print = '_';
		break;
	default:
		break;

	}//end switch
	printf("%c", to_print);
}
//------------------------------------------------------------------------------------------------------------------------------------------
void print_grid()
{
	//skipping few lines
	for (int spaces = 1; spaces <= GRID_OFFSET/2; spaces++)
		printf("\n");

	//printing spaces
	for (int spaces = 1; spaces <= GRID_OFFSET; spaces++)
		printf(" ");

	//top boundary
	for (int i = 0; i <= (COL+1)/2; i++)
		printf("o ");
	puts("");


	//printing grid with side boundaries
	for (int row = ROW-1; row >=0; row--)
	{
		//printing spaces
		for (int spaces = 1; spaces <= GRID_OFFSET; spaces++)
			printf(" ");
		

		//printing left bound
		printf("o");

		for (int col = 0; col < COL; col++)
		{
			print_code(grid[row][col]);
			
		}
		//printing right bound
		puts("o");
	}

	//printing spaces
	for (int spaces = 1; spaces <= GRID_OFFSET; spaces++)
		printf(" ");

	//bottom boundary
	for (int i = 0; i <= (COL+1)/2; i++)
		printf("o ");

	puts("");
	fflush(stdout);


}

//------------------------------------------------------------------------------------------------------------------------------------------

/*moves the peg from indicated tower to indicated tower*/
void move(int from,int to)
{
	system("cls");
	int peg_size = tower[num_pegs[from]-1][from],row,col;//size of the peg to be moved

	//First to remove the peg from indicated tower

	for (row = num_pegs[from]; row <= TOW_HEIGHT+1; row++)
	{
		for (col = tow_location[from] - peg_size; col <= tow_location[from] + peg_size; col++)
		{
			//skipping the tower column 
			if ((col == tow_location[from]) && (row < TOW_HEIGHT))
			{
				continue;
			}
			else if ((col == tow_location[from]) && (row == TOW_HEIGHT))
			{
				grid[row][col] = PEG;
				continue;
			}
			
			
				grid[row][col] = PEG;
				grid[row - 1][col] = BLANK;
			
		
			
		}
		
		print_grid();
		Sleep(PAUSE_TIME);
		system("cls");
	}row--;

	//now to move the peg towards the indicated tower
	int	sign = (tow_location[to] - tow_location[from]) / abs(tow_location[to] - tow_location[from]);
	int	centre_of_peg=tow_location[from];
	
	
	for (; centre_of_peg != tow_location[to]; centre_of_peg += sign)
	{
		grid[row][centre_of_peg + sign*(peg_size+1)] = PEG;
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
			
			if ((col == tow_location[to]) && (row < TOW_HEIGHT-1))
			{
				continue;
			}
			else if (col == tow_location[to] && (row == TOW_HEIGHT - 1))
			{
				grid[row+1][col] = BLANK;
				continue;
			}


			grid[row][col] = PEG;
			grid[row + 1][col] = BLANK;



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