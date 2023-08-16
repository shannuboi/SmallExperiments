#pragma once

#include <assert.h>
#include <iostream>

class TicTacToe
{
public:
	// initiallize grid to all 0s
	TicTacToe();	
	// returns whether move possible or not
	bool Move(int player, int xloc, int yloc);	
	void Display();
	// 2 means p2 won, 1 means p1 won, 0 means draw, -1 means game running 
	int State() const;	
private:
	int grid[3][3];
};

// Runs one game of tictactoe till completion
void RunTicTacToe()
{
	TicTacToe game;
	std::cout << "TikTacToe\n\n";
	std::cout << "Type, when promted, the row and the column where you want to move\n";
	std::cout << "Legal moves can only be made on spaces with Zeros\n\n";

	while (game.State() == -1)	// Loop runs as long as game runs (-1)
	{
		game.Display();
		std::cout << "Player 1's move\n";
		int col;
		int row;
		do
		{
			std::cout << "Column: ";
			std::cin >> col;

			std::cout << "Row: ";
			std::cin >> row;

		} while (!game.Move(1, col - 1, row - 1));	// keep reasking for move if Invalid
		std::cout << "\n";

		if (game.State() != -1)		// Checking if p1's move finished the game
		{
			break;
		}

		game.Display();
		std::cout << "Player 2's move\n";
		do
		{
			std::cout << "Column: ";
			std::cin >> col;

			std::cout << "Row: ";
			std::cin >> row;

		} while (!game.Move(2, col - 1, row - 1));
		std::cout << "\n";
	}

	game.Display();
	std::cout << "\n";

	if (game.State() == 2)
	{
		std::cout << "Game won by player 2";
	}
	else if (game.State() == 1)
	{
		std::cout << "Game won by player 1";
	}
	else if (game.State() == 0)
	{
		std::cout << "Game drawn";
	}
}

TicTacToe::TicTacToe()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			grid[y][x] = 0;
		}
	}
}

bool TicTacToe::Move(int player, int xloc, int yloc)
{
	assert(player == 1 || player == 2);		// Valid player?

	bool movePossible = (grid[yloc][xloc] == 0) &&		// tile empty?
		(xloc >= 0 && xloc < 3 && yloc >= 0 && yloc < 3);	// tile inside grid?
	if (movePossible)
	{
		grid[yloc][xloc] = player;
		return true;
	}
	else
	{
		std::cout << "Invalid move\n";
		return false;
	}
}

void TicTacToe::Display()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			std::cout << grid[y][x] << "\t";
		}
		std::cout << "\n";
	}
}

int TicTacToe::State() const
{
	//checking all vert and horizontal win conditions
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != 0)	// row i
		{
			return grid[i][0];
		}
		else if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != 0)	// column i
		{
			return grid[0][i];
		}
	}

	//checking diagonals
	if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != 0)
	{
		return grid[0][0];
	}
	else if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[0][2] != 0)
	{
		return grid[0][2];
	}

	//checking draw condition
	bool draw = true;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (grid[y][x] == 0)
			{
				draw = false;
			}
		}
	}

	//if drawn returm 0 else return -1 (game still going)
	return draw ? 0 : -1;
}
