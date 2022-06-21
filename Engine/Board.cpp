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
				int count = CheckNeighborTiles(Vei2(x / TileDimension, y / TileDimension));
				if (count == 0)
					SpriteCodex::DrawTile0(Vei2(x, y), gfx);
				else if (count == 1)
					SpriteCodex::DrawTile1(Vei2(x, y), gfx);
				else if (count == 2)
					SpriteCodex::DrawTile2(Vei2(x, y), gfx);
				else if (count == 3)
					SpriteCodex::DrawTile3(Vei2(x, y), gfx);
				else if (count == 4)
					SpriteCodex::DrawTile4(Vei2(x, y), gfx);
				else if (count == 5)
					SpriteCodex::DrawTile5(Vei2(x, y), gfx);
				else if (count == 6)
					SpriteCodex::DrawTile6(Vei2(x, y), gfx);
				else if (count == 7)
					SpriteCodex::DrawTile7(Vei2(x, y), gfx);
				else if (count == 8)
					SpriteCodex::DrawTile8(Vei2(x, y), gfx);
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

int Board::CheckNeighborTiles(Vei2& pos)
{
	int Count = 0;
	if (pos.x > 0 && pos.y > 0 && pos.x < Dimension::Width && pos.y < Dimension::Height)
	{
		if (CellState[pos.x - 1][pos.y - 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x][pos.y - 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x + 1][pos.y - 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x + 1][pos.y] == Cell::Bomb)
			Count++;
		if (CellState[pos.x + 1][pos.y + 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x][pos.y + 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x - 1][pos.y + 1] == Cell::Bomb)
			Count++;
		if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
			Count++;
	}

	return Count;
}

void Board::InitCells()
{
	for (int y = 0; y < Dimension::Height; y++)
		for (int x = 0; x < Dimension::Width; x++)
		{
			if (x % 2 == 0 && y % 2 == 0)
				CellState[x][y] = Cell::Bomb;
		}

}

bool Board::isGameOver()
{
	return GameOver;
}
