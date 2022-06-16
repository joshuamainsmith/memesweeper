#include "Board.h"
#include "SpriteCodex.h"

Board::Board()
	:
StartPos(0,0)
{
}

void Board::Draw(Graphics& gfx)
{
	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y++)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x++)
			gfx.PutPixel(x, y, 192, 192, 192);

	for (int y = StartPos.y; y < Dimension::Height + StartPos.y; y+=16)
		for (int x = StartPos.x; x < Dimension::Width + StartPos.x; x+=16)
			SpriteCodex::DrawTile0(Vei2(x, y), gfx);
}
