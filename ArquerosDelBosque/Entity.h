#pragma once
#include <iostream>
#include "Enums.h"

class Entity
{
public:
	Entity() {};
	Entity(int x, int y, const std::string& Char) : X(x), Y(y), Char(Char) {};
	std::string Char = "0";
	int X = 0;
	int Y = 0;
};

