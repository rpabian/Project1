/*
 * theather.c
 *
 *  Created on: Feb 26, 2019
 *      Author: itopa
 */
#include <stdio.h>
void printTheater(char seatChart[][30]);
void rowPriceAssign(int row[]);
void printRowPrice(int row[]);
int nextAction();
void buyTicket(char theater[][30], int *totalPointer, int rowPrice[]);
void printSales(int *totalPointer);
void seatsSold(char theater[][30]);
void seatsAvailable(char theater[][30]);
void entireAvailable(char theater[][30]);

void main()
{
	printf("Theater Auditorium\n");
	char theater[15][30];
	for(int i = 0; i < 15; i++)
		for( int j = 0; j < 30; j++)
			theater[i][j] = '#';

	int rowPrice[15];
	rowPriceAssign(rowPrice);

	printTheater(theater);

	int totalSales = 0;
	int *totalPointer = &totalSales;

	int userInput = 0;
	while(userInput != -1)
	{
		userInput = nextAction();
		if(userInput == 1)
		{
			buyTicket(theater, totalPointer, rowPrice);
			continue;
		}
		else if(userInput == 2)
		{
			printSales(totalPointer);
			continue;
		}
		else if(userInput == 3)
		{
			seatsSold(theater);
			continue;
		}
		else if(userInput == 4)
		{
			seatsAvailable(theater);
			continue;
		}
		else if(userInput == 5)
		{
			entireAvailable(theater);
			continue;
		}
		else if(userInput == -1)
			continue;
		else
		{
			printf("Not a valid Input, try again.\n");
			continue;
		}
	}
}

void printTheater(char seatChart[][30])
{
	printf("Remaining seats:\n");
	char seats[] = "Seats";
	printf("%23s\n", seats);
	for(int i = 0; i < 16; i ++)
		for(int j = 0; j < 31; j++)
		{
			if(i == 0)
			{
				if(j == 0)
					printf("%7s", "");
				else
				{
					printf("%d", j%10);
					if(j == 30)
						printf("\n");
				}
			}
			else if( j == 0)
				printf("Row %2d ", i);
			else
			{
				printf("%c", seatChart[i-1][j-1]);
				if(j == 30)
					printf("\n");
			}
		}
}

void rowPriceAssign(int row[])
{
	printf("Enter the Price for each of the 15 Rows.\n");
	for(int i = 0; i < 15; i++)
	{
		printf("Price of Row %d:", i + 1);
		fflush(stdout);
		scanf("%d", &row[i]);
	}
}

void printRowPrice(int row[])
{
	printf("Row Prices: \n");
	for(int i = 0; i < 15; i++)
	{
		printf("Row %2d: %d\n", i + 1, row[i]);
	}
}

int nextAction()
{
	int userInput = 0;
	printf("Enter next Purchase : (1)\n");
	printf("View total Ticket Sales: (2)\n");
	printf("View list of sold seats: (3)\n");
	printf("View seats available in a row: (4)\n");
	printf("View number of seats available in Auditorium: (5)\n");
	printf("Quit: (-1)\n");
	printf("Enter the next Action: ");
	fflush(stdout);
	scanf("%d", &userInput);
	return userInput;
}

void buyTicket(char theater[][30], int *totalPointer, int rowPrice[])
{
	int row = -1;
	int seat = -1;
	int check = 1;
	while(check)
	{
		printf("Enter the row for the ticket that is being purchased:");
		fflush(stdout);
		scanf("%d", &row);
		printf("Enter the seat for the ticket that is being purchased: ");
		fflush(stdout);
		scanf("%d", &seat);
		if(theater[row - 1][seat - 1] == '*')
		{
			printf("Seat is not available, sorry.\n");
			continue;
		}
		else if(row < 1 || row > 15 || seat < 1 || seat > 30)
		{
			printf("Not a valid input, try again.\n");
			continue;
		}
		else
		{
			theater[row - 1][seat - 1] = '*';
			*totalPointer += rowPrice[row - 1];
			int secondCheck = -1;
			while(secondCheck < 0 || secondCheck > 1)
			{
				printf("Do you wish to buy another ticket?\n");
				printf("0(no) or 1(yes):");
				fflush(stdout);
				scanf("%d", &check);
				secondCheck = check;
				if(secondCheck < 0 || secondCheck > 1)
				{
					printf("Not a valid input, try again.\n");
					continue;
				}
			}
		}
	}
	printTheater(theater);
}

void printSales(int *totalPointer)
{
	printf("Total Sales: %d$\n", *totalPointer);
}

void seatsSold(char theater[][30])
{
	printf("List of sold seats:\n ");
	for(int i = 0; i < 15; i++)
		for(int j = 0; j < 31; j++)
		{
			if(j == 0)
				printf("Row %2d:", i + 1);
			else
			{
				if(theater[i][j - 1] == '*')
					printf("Seat %d ", j);
				if(j == 30)
					printf("\n");
			}
		}
}

void seatsAvailable(char theater[][30])
{
	printf("Available seats for each Row:\n");
	for(int i = 0; i < 15; i++)
	{
		int counter = 0;
		for(int j = 0; j < 31; j++)
		{
			if(j == 0)
				printf("Row %2d:", i + 1);
			else
			{
				if(theater[i][j - 1] == '#')
					counter++;
				if(j == 30)
					printf("%d open seats\n", counter);
			}
		}
	}
}

void entireAvailable(char theater[][30])
{
	int counter = 0;
	for(int i = 0; i < 15; i++)
		for(int j = 0; j < 30; j++)
			if(theater[i][j] == '#')
				counter++;
	printf("Available seats in Auditorium: %d Seats\n", counter);
}
