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
		Bomb
	};

	enum Dimension
	{
		Width = 16 * width,
		Height = 16 * height
	};

public:
	Board();
	Vei2 GetStartPos();
	void Draw(Graphics& gfx);
	void DrawGameOver(Graphics& gfx);
	void ProcessClick(bool flag, Graphics& gfx, std::pair<int, int>& ms);
	int CheckNeighborTiles(Vei2& pos);
	void InitCells();
	bool isGameOver();

private:
	static constexpr int CenterHeight = (Graphics::ScreenHeight / 2) - ((float)Dimension::Height / 2);
	static constexpr int CenterWidth = (Graphics::ScreenWidth / 2) - ((float)Dimension::Width / 2);
	static constexpr int TileDimension = 16;
	Vei2 StartPos;
	Cell CellState[width][height] = {Cell::Default};
	bool GameOver = false;
	bool HasFlag[CenterWidth][CenterHeight] = { false };
};

