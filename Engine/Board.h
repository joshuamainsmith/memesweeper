#pragma once

#include "Graphics.h"
#include "Vei2.h"
#include "Keyboard.h"


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
	void ProcessClick(Cell cell);

private:
	Vei2 StartPos;
	static constexpr float CenterWidth = (Graphics::ScreenWidth / 2) - ((float)Dimension::Width / 2);
	static constexpr float CenterHeight = (Graphics::ScreenHeight / 2) - ((float)Dimension::Height / 2);
};

