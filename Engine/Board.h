#pragma once

#include "Graphics.h"
#include "Vei2.h"


class Board
{
public:
	enum class Cell
	{
		Default,
		Empty,
		Flag,
		Bomb
	};

	void Draw(Graphics& gfx);

private:
	Vei2 pos;
};

