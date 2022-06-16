#pragma once

#include "Graphics.h"
#include "Vei2.h"


class Board
{
public:
	static constexpr int width = 10;
	static constexpr int height = 8;

public:
	Board();
	void Draw(Graphics& gfx);

private:
	Vei2 StartPos;

public:
	enum class Cell
	{
		Default,
		Empty,
		Flag,
		Bomb
	};

	enum Dimension
	{
		Width = 16 * width,
		Height = 16 * height
	};
};

