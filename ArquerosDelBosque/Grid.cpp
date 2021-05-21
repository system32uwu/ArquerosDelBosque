#include "Grid.h"

inline void Grid::FillGrid() {
	for (int x = 0; x < Size; x++)
	{
		for (int y = 0; y < Size; y++)
		{
			grid[x][y] = "|    ";
		}
	}
}

inline void Grid::FillTrees() {
	for (int i = 0; i < NUMBER_OF_TREES; i++) {
		bool taken = true;
		srand(time(0));
		while (taken) { //keep generating a random position until it finds one that's not already used
			Entity arbol(rand() % 8 + 1, rand() % 8 + 1, "0");

			//lambda expresion, can be replaced with a for loop checking the same condition
			if (std::find_if(Arboles.begin(), Arboles.end(), [arbol](const Entity& a) {return a.X == arbol.X && a.Y == arbol.Y; }) == Arboles.end()) {
				Arboles.push_back(arbol);
				taken = false;
			}
		}
	}
}

inline void Grid::DrawGrid() {
	printf("\033c"); //reset console window (*nix, Windows 10 >= TH2 )

	for (int x = 0; x < Size; x++)
	{
		std::string row = "";
		bool picked = false;

		for (int y = 0; y < Size; y++)
		{
			for (Entity arbol : Arboles) {
				if (arbol.X == x && arbol.Y == y) {
					std::string value = +"| " + arbol.Char + " ";
					grid[x][y] = value;
					row += value;
					picked = true;
				}
			}

			for (Arquero arquero : Arqueros) {
				if (arquero.X == x && arquero.Y == y) {
					std::string value = "| " + arquero.Char + " ";
					grid[x][y] = value;
					row += value;
					picked = true;
				}
			}

			if (!picked) {
				std::string value = "|   ";
				grid[x][y] = value;
				row += value;
			}

			picked = false;
		}
		std::cout << std::endl;
		for (int i = 0; i < row.length(); i++) {
			std::cout << "-";
		}
		std::cout << std::endl;
		std::cout << row + "|";
	}
	std::cout << std::endl << "\n";
}