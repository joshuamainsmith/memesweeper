#include "Board.h"
#include "SpriteCodex.h"

Board::Board()
	:
StartPos(CenterWidth, CenterHeight)
{
	InitCells();
}

void Board::Draw(Graphics& gfx)
{
	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y++)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x++)
			gfx.PutPixel(x, y, 192, 192, 192);

	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y += TileDimension)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x += TileDimension)
		{
			switch (CellState[x / TileDimension][y / TileDimension])
			{
			case Cell::Default:
				SpriteCodex::DrawTileButton(Vei2(x, y), gfx);
				if (HasFlag[x / TileDimension][y / TileDimension])
					SpriteCodex::DrawTileFlag(Vei2(x, y), gfx);
				break;
			case Cell::Bomb:
				if (GameOver)
					SpriteCodex::DrawTileBomb(Vei2(x, y), gfx);
				else
				{
					SpriteCodex::DrawTileButton(Vei2(x, y), gfx);
					if (HasFlag[x / TileDimension][y / TileDimension])
						SpriteCodex::DrawTileFlag(Vei2(x, y), gfx);
				}
				break;
			case Cell::Empty:
				SpriteCodex::DrawTile0(Vei2(x, y), gfx);
				break;
			}			
		}
}

void Board::DrawGameOver(Graphics& gfx)
{
	if (GameOver)
	{
		// Draw Gameover Screen
	}
}

void Board::ProcessClick(bool flag, Graphics& gfx, std::pair<int, int>& ms)
{
	switch (CellState[(ms.first / TileDimension)][(ms.second / TileDimension) - 1])
	{
	case Cell::Bomb:
		if (!flag)
			GameOver = true;
		else
			HasFlag[(ms.first / TileDimension)][(ms.second / TileDimension) - 1] = true;
		break;
	case Cell::Default:
		if (flag)
		{
			HasFlag[(ms.first / TileDimension)][(ms.second / TileDimension) - 1] = true;
			break;
		}
		CellState[(ms.first / TileDimension)][(ms.second / TileDimension) - 1] = Cell::Empty;
		break;
	}
	
}

void Board::CheckNeighborTiles(Vei2& pos)
{
	int Count = 0;
	if (pos.x > 0 && pos.y > 0 && pos.x < Dimension::Width && pos.y < Dimension::Height)
	{

	}
}

void Board::InitCells()
{
	for (int y = 0; y < CenterHeight; y++)
		for (int x = 0; x < CenterWidth; x++)
		{
			if (x % 2 == 0)
				CellState[x][y] = Cell::Bomb;
		}
}

bool Board::isGameOver()
{
	return GameOver;
}
