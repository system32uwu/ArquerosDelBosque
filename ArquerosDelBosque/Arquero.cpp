#pragma once
#include "Arquero.h"

inline void Arquero::move(Direction direction) {
	switch (direction)
	{
	case Direction::S:
		if (X + 1 < 10) {
			X++;
		}
		break;
	case Direction::N:
		if (X - 1 > -1) {
			X--;
		}
		break;
	case Direction::E:
		if (Y + 1 < 10) {
			Y++;
		}
		break;
	case Direction::O:
		if (Y - 1 > -1) {
			Y--;
		}
		break;
	default:
		break;
	}
}