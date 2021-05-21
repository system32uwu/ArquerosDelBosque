#include "Entity.h"
#include "Arquero.cpp"
#include "Grid.cpp"
#include "CONSTANTS.h"
#include "Utils.cpp"
#include <iostream>

int main()
{ 
	srand(time(0));

	Arquero A(4, 9, "A");
	Arquero B(0, 9, "B");

	while (true) {
		int turn = rand() % 2;

		std::string winner = "";

		std::vector<Arquero> arqueros = { A, B };

		Grid grid(arqueros);

		bool disparoNoTuvoEfecto = false;

		Arquero currentPlayer;

		Arquero currentEnemy;

		while (winner == "") {
			grid.DrawGrid();

			if (disparoNoTuvoEfecto) {
				printf(SHOOT_MISSED.c_str());
			}

			if (turn == 0) {
				currentPlayer = grid.Arqueros[0];
				currentEnemy = grid.Arqueros[1];
			}
			else {
				currentPlayer = grid.Arqueros[1];
				currentEnemy = grid.Arqueros[0];
			}

			disparoNoTuvoEfecto = false;

			char action = AskInputAndValidate(POSSIBLE_ACTIONS, INPUT_ACTION(currentPlayer.Char));
			char direction = AskInputAndValidate(POSSIBLE_DIRECTIONS, INPUT_DIRECTION);

			int play = act(direction, grid.Arboles,currentPlayer,currentEnemy,action);

			switch (play)
			{
			case 0: // hits tree
			case -1: // miss
				disparoNoTuvoEfecto = true;
				break;
			case 1: //can move
				currentPlayer.move(direction);
				grid.Arqueros[turn].move(direction);
				break;
			case 2: //hits enemy
				winner = currentPlayer.Char;
				break;
			default:
				break;
			}

			turn = 1 - turn;
		}
		printf(PLAYER_WIN(winner).c_str());
		break;
	}

	

}