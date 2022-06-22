#include "Board.h"
#include "SpriteCodex.h"
#include <random>

Board::Board()
	:
StartPos(CenterWidth, CenterHeight)
{
	InitCells();
}

Vei2 Board::GetStartPos()
{
	return StartPos;
}

void Board::Draw(Graphics& gfx)
{
	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y++)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x++)
			gfx.PutPixel(x, y, 192, 192, 192);

	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y += TileDimension)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x += TileDimension)
		{
			int in_x = (x - StartPos.x) / TileDimension;
			int in_y = (y - StartPos.y) / TileDimension;
			switch (CellState[in_x][in_y])
			{
			case Cell::Default:
				SpriteCodex::DrawTileButton(Vei2(x, y), gfx);
				if (HasFlag[in_x][in_y])
					SpriteCodex::DrawTileFlag(Vei2(x, y), gfx);
				break;
			case Cell::Bomb:
				if (GameOver)
					SpriteCodex::DrawTileBomb(Vei2(x, y), gfx);
				else
				{
					SpriteCodex::DrawTileButton(Vei2(x, y), gfx);
					if (HasFlag[in_x][in_y])
						SpriteCodex::DrawTileFlag(Vei2(x, y), gfx);
				}
				break;
			case Cell::Empty:
				int count = CheckNeighborTiles(Vei2(in_x, in_y));
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
	int x = (ms.first - StartPos.x) / TileDimension;
	int y = (ms.second - StartPos.y) / TileDimension;
	switch (CellState[x][y])
	{
	case Cell::Bomb:
		if (!flag && !HasFlag[x][y])
			GameOver = true;
		else
			HasFlag[x][y] = true;
		break;
	case Cell::Default:
		if (flag)
		{
			HasFlag[x][y] = true;
		}
		else if (!HasFlag[x][y])
			CellState[x][y] = Cell::Empty;
		break;
	}	
}

int Board::CheckNeighborTiles(Vei2& pos)
{
	int Count = 0;
	if (pos.x > 0 && pos.y > 0 && pos.x < width - 1 && pos.y < height - 1)
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
	else
	{

		if (pos.x == 0)
		{
			// top left corner
			if (pos.y == 0)
			{
				if (CellState[pos.x + 1][pos.y] == Cell::Bomb)
					Count++;
				if (CellState[pos.x + 1][pos.y + 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x][pos.y + 1] == Cell::Bomb)
					Count++;
			}

			// bottom left corner
			else if (pos.y == height - 1)
			{
				if (CellState[pos.x + 1][pos.y] == Cell::Bomb)
					Count++;
				if (CellState[pos.x + 1][pos.y - 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x][pos.y - 1] == Cell::Bomb)
					Count++;
			}

			// left
			else
			{
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
			}
		}

		else if (pos.x == width - 1)
		{
			// top right corner
			if (pos.y == 0)
			{
				if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
					Count++;
				if (CellState[pos.x - 1][pos.y + 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x][pos.y + 1] == Cell::Bomb)
					Count++;
			}

			// bottom right corner
			else if (pos.y == height - 1)
			{
				if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
					Count++;
				if (CellState[pos.x - 1][pos.y - 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x][pos.y - 1] == Cell::Bomb)
					Count++;
			}

			// right
			else 
			{
				if (CellState[pos.x][pos.y - 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x - 1][pos.y - 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
					Count++;
				if (CellState[pos.x - 1][pos.y + 1] == Cell::Bomb)
					Count++;
				if (CellState[pos.x][pos.y + 1] == Cell::Bomb)
					Count++;
			}
		}

		// top
		else if (pos.y == 0)
		{
			if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
				Count++;
			if (CellState[pos.x - 1][pos.y + 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x][pos.y + 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x + 1][pos.y + 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x + 1][pos.y] == Cell::Bomb)
				Count++;
		}

		// bottom
		else if (pos.y == height - 1)
		{
			if (CellState[pos.x - 1][pos.y] == Cell::Bomb)
				Count++;
			if (CellState[pos.x - 1][pos.y - 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x][pos.y - 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x + 1][pos.y - 1] == Cell::Bomb)
				Count++;
			if (CellState[pos.x + 1][pos.y] == Cell::Bomb)
				Count++;
		}
	}

	return Count;
}

void Board::InitCells()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);	

	int x = xDist(rng);
	int y = yDist(rng);
	for (int c = 0; c < 10; c++)
	{
		while (CellState[x][y] == Cell::Bomb)
		{
			x = xDist(rng);
			y = yDist(rng);
		}

		CellState[x][y] = Cell::Bomb;
	}
}

bool Board::isGameOver()
{
	return GameOver;
}
