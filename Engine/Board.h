#pragma once

#include "Graphics.h"
#include "Vei2.h"
#include "Mouse.h"


class Board
{
public:
	static constexpr int width = 12;
	static constexpr int height = 10;

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

public:
	Board();
	void Draw(Graphics& gfx);
	void ProcessClick(Cell cell, Graphics& gfx, std::pair<int, int>& ms);
	void InitCells();

private:
	static constexpr int CenterHeight = (Graphics::ScreenHeight / 2) - ((float)Dimension::Height / 2);
	static constexpr int CenterWidth = (Graphics::ScreenWidth / 2) - ((float)Dimension::Width / 2);
	Vei2 StartPos;
	Cell CellState[CenterWidth][CenterHeight] = {Cell::Default};
};

