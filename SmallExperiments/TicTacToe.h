#pragma once

#include <assert.h>
#include <iostream>

class TicTacToe
{
public:
	enum class GameState
	{
		Running,
		Draw,
		P1won,
		P2won
	};
public:
	// initiallize grid to all 0s
	TicTacToe();

	// returns whether move possible or not
	// If possible move is done
	bool Move(int player, int xloc, int yloc);

	void Display();

	GameState State() const;
private:
	int grid[3][3];
};

// Runs one game of tictactoe till completion
void RunTicTacToe()
{
	TicTacToe game;
	std::cout << "TicTacToe\n\n";
	std::cout << "Type, when promted, the row and the column where you want to move\n";
	std::cout << "Legal moves can only be made on spaces with squares\n\n\n";

	while (game.State() == TicTacToe::GameState::Running)
	{
		game.Display();
		std::cout << "Player 1's move (X)";
		int col;
		int row;
		do
		{
			std::cout << "\nColumn: ";
			std::cin >> col;

			std::cout << "Row: ";
			std::cin >> row;

		} while (!game.Move(1, col - 1, row - 1));	// keep reasking for move if invalid
		std::cout << "\n\n";

		if (game.State() != TicTacToe::GameState::Running)		// Checking if p1's move finished the game
		{
			break;
		}

		game.Display();
		std::cout << "Player 2's move (O)";
		do
		{
			std::cout << "\nColumn: ";
			std::cin >> col;

			std::cout << "Row: ";
			std::cin >> row;

		} while (!game.Move(2, col - 1, row - 1));
		std::cout << "\n";
	}

	game.Display();
	std::cout << "\n";

	if (game.State() == TicTacToe::GameState::P2won)
	{
		std::cout << "Game won by player 2";
	}
	else if (game.State() == TicTacToe::GameState::P1won)
	{
		std::cout << "Game won by player 1";
	}
	else if (game.State() == TicTacToe::GameState::Draw)
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
	const unsigned char BLANK = 254;
	for (int y = 0; y < 3; y++)
	{
		std::cout << " ";
		for (int x = 0; x < 3; x++)
		{
			char c = BLANK;
			if (grid[y][x] == 1) c = 'X';
			if (grid[y][x] == 2) c = 'O';
			std::cout << c << "  ";
		}
		std::cout << "\n";
	}
}

TicTacToe::GameState TicTacToe::State() const
{
	//checking all vert and horizontal win conditions
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != 0)	// row i
		{
			if (grid[i][0] == 1)
				return GameState::P1won;
			else
				return GameState::P2won;
		}
		else if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != 0)	// column i
		{
			if (grid[0][i] == 1)
				return GameState::P1won;
			else
				return GameState::P2won;
		}
	}

	//checking diagonals
	if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != 0)
	{
		if (grid[0][0] == 1)
			return GameState::P1won;
		else
			return GameState::P2won;
	}
	else if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[0][2] != 0)
	{
		if (grid[0][2] == 1)
			return GameState::P1won;
		else
			return GameState::P2won;
	}

	//checking draw condition
	bool draw = true;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (grid[y][x] == 0)
				draw = false;
		}
	}

	if (draw)
		return GameState::Draw;
	else
		return GameState::Running;
}