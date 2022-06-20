#include "Board.h"
#include "SpriteCodex.h"

Board::Board()
	:
StartPos(CenterWidth, CenterHeight)
{
}

void Board::Draw(Graphics& gfx)
{
	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y++)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x++)
			gfx.PutPixel(x, y, 192, 192, 192);

	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y+=16)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x += 16)
		{
			if (CellState[x / 16][y / 16] == Cell::Default)
				SpriteCodex::DrawTileButton(Vei2(x, y), gfx);
			else if (CellState[x / 16][y / 16] == Cell::Empty)
				SpriteCodex::DrawTile0(Vei2(x, y), gfx);
		}
}

void Board::ProcessClick(Cell cell, Graphics& gfx, std::pair<int, int>& ms)
{
	if (cell == Cell::Empty)
	{
		CellState[(ms.first / 16)][(ms.second / 16) - 1] = Cell::Empty;
	}
}

void Board::InitCells()
{
}
