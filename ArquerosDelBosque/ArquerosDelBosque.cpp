#include <iostream>
#include "Entity.h"
#include "Arquero.cpp"
#include "Grid.cpp"
#include "CONSTANTS.h"

int main()
{ 
	// Register more than 2 archers if you want.	
	std::vector<Arquero> arqueros = { Arquero(9, 0, "A"), Arquero(0, 9, "B") };

	Grid grid(arqueros);

	grid.DrawGrid();

}