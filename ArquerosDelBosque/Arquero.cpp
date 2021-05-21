#pragma once
#include "Arquero.h"
#include "CONSTANTS.h"

inline void Arquero::move(char direction) {
	switch (direction)
	{
	case 'S':
		if (X + 1 < 10) {
			X++;
		}
		break;
	case 'N':
		if (X - 1 > -1) {
			X--;
		}
		break;
	case 'E':
		if (Y + 1 < 10) {
			Y++;
		}
		break;
	case 'O':
		if (Y - 1 > -1) {
			Y--;
		}
		break;
	}
}