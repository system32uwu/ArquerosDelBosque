#pragma once
#include <iostream>
#include <vector>
#include "CONSTANTS.h"
#include "Entity.h"
#include "Arquero.cpp"

inline char AskInputAndValidate(std::vector<char> possibleLetters, std::string message) {
	char letter = 'G'; //letra aleatoria que no es direccion valida.
	bool error = false;

	while (letter == 'G') {
		
		if (error) {
			printf(INVALID_INPUT.c_str());
		}

		std::string input;

		printf(message.c_str());

		std::cin >> input;

		if (!input.empty()) {
			for (char l : possibleLetters) {
				if (toupper(input[0]) == l) {
					letter = l;
				}
			}
		}

		error = true;
	}
	return letter;
}

//0: hits tree (shooting | moving ), 1: can walk to direction, 2: hits player (shooting), -1: didn't hit anything (shooting).
inline int act(char direction, std::vector<Entity> arboles, Arquero currentPlayer, Arquero currentEnemy, char action) {

	int shooting = false;

	if (action == 'T') {
		shooting = true;
	}

	if (direction == 'S') {
		if (shooting) {
			for (int i = currentPlayer.X; i < currentPlayer.X + SHOOT_RANGE; i++) {
				for (Entity tree : arboles) {
					if (currentPlayer.Y == tree.Y && tree.X == i) {
						return 0; //tree in front
					}
					else if (currentEnemy.Y == currentPlayer.Y && currentEnemy.X == i) {
						return 2; //hits enemy
					}
				}
			}
		}
		else {
			for (Entity tree : arboles) {
				if (currentPlayer.Y == tree.Y && tree.X == currentPlayer.X + 1) {
					return 0;
				}
			}
		}
	}else if (direction == 'N') {
		if (shooting) {
			for (int i = currentPlayer.X + SHOOT_RANGE; i > currentPlayer.X; i--) {
				for (Entity tree : arboles) {
					if (currentPlayer.Y == tree.Y && tree.X == i) {
						return 0; //tree in front
					}
					else if (currentEnemy.Y == currentPlayer.Y && currentEnemy.X == i) {
						return 2; //hits enemy
					}
				}	
			}
		}
		else {
			for (Entity tree : arboles) {
				if (currentPlayer.Y == tree.Y && tree.X == currentPlayer.X - 1) {
					return 0;
				}
			}
		}
	} else if (direction == 'E') {
		if (shooting) {
			for (int i = currentPlayer.Y; i < currentPlayer.Y + SHOOT_RANGE; i++) {
				for (Entity tree : arboles) {
					if (currentPlayer.X == tree.X && tree.Y == i) {
						return 0;
					}
					else if (currentEnemy.X == currentPlayer.X && currentEnemy.Y == i) {
						return 2;
					}
				}
			}
		}
		else {
			for (Entity tree : arboles) {
				if (currentPlayer.X == tree.X && tree.Y == currentPlayer.Y + 1) {
					return 0;
				}
			}
		}
	}
	else if (direction == 'O') {
		if (shooting) {
			for (int i = currentPlayer.Y + SHOOT_RANGE; i > currentPlayer.Y; i--) {
				for (Entity tree : arboles) {
					if (currentPlayer.X == tree.X && tree.Y == i) {
						return 0;
					}
					else if (currentEnemy.X == currentPlayer.X && currentEnemy.Y == i) {
						return 2;
					}
				}
			}
		}
		else {
			for (Entity tree : arboles) {
				if (currentPlayer.X == tree.X && tree.Y == currentPlayer.Y - 1) {
					return 0;
				}
			}
		}
	}

	if (shooting) {
		return -1; //shoot didn't hit
	}
	else {
		return 1; //can move
	}
}