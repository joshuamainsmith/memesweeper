#include "Board.h"
#include "SpriteCodex.h"

void Board::Draw(Graphics& gfx)
{
	pos.x = 0;
	pos.y = 0;
	SpriteCodex::DrawTile0(pos, gfx);
}
