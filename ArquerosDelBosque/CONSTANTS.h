#pragma once
#include <iostream>
#include <vector>

//ACTIONS, DIRECTIONS
const std::vector<char> POSSIBLE_ACTIONS = { 'T','M' };
const std::vector<char> POSSIBLE_DIRECTIONS = { 'S','N','E','O' };

//GAME LIMITS
const int GRID_SIZE = 10;
const int NUMBER_OF_TREES = 10;
const int SHOOT_RANGE = 6; //5 sin contar la casilla desde donde se dispara

//INPUTS
inline std::string INPUT_ACTION(std::string c) {
	return "Jugador " + c + ": (M)overse o (T)irar flecha?:";
}
const std::string INPUT_DIRECTION = "Dirección: (S)ur, (N)orte, (E)ste, u (O)este?:";

//MESSAGES
const std::string SHOOT_MISSED = "El disparo no tiene efecto \n";
inline std::string PLAYER_WIN(std::string c) {
	return "Jugador " + c + " gana!!!";
};
const std::string INVALID_INPUT = "Entrada incorrecta, vuelva a ingresar: \n";
const std::string MOVED = "MOVED";
const std::string SHOOTED = "SHOOTED";
