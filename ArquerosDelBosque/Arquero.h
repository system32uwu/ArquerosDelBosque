#pragma once
#include <iostream>
#include "Entity.h"

class Arquero : public Entity
{
public:
	Arquero() {};
	Arquero(int x, int y, const std::string& Char): Entity(x, y, Char) {};
	void move(Direction direction);
};

