#pragma once
#include <vector>
#include "Entity.h"
#include "Arquero.h"
#include "CONSTANTS.h"

class Grid
{
public:
	int Size = GRID_SIZE;
	std::string grid[GRID_SIZE][GRID_SIZE];
	std::vector<Entity> Arboles;
	std::vector<Arquero> Arqueros;

	Grid() {};
	Grid(std::vector<Arquero> arqueros): Arqueros(arqueros){
		FillTrees();
		FillGrid();
	};
	
	void DrawGrid();

private:
	void FillGrid();

	void FillTrees();
};

