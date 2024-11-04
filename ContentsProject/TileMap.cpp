#include "PreCompile.h"
#include "TileMap.h"

ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
}

void ATileMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize)
{
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}



}

void ATileMap::SetTile(FIntPoint _Index, int _SpriteIndex)
{
	if (0 > _Index.X)
	{
		return;
	}

	if (0 > _Index.Y)
	{
		return;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return;
	}

	if (nullptr == AllTiles[TileCount.Y][TileCount.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		AllTiles[TileCount.Y][TileCount.X].SpriteRenderer;
	}

}