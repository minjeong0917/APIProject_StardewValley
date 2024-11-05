#include "PreCompile.h"
#include "TileMap.h"

ATileMap::ATileMap()
{
}

ATileMap::~ATileMap()
{
}

// Ÿ���� 
void ATileMap::Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize)
{
	SpriteName = _Sprite;
	TileSize = _TileSize;
	TileCount = _Count;

	AllTiles.resize(_Count.Y);

	for (size_t y = 0; y < AllTiles.size(); y++)
	{
		AllTiles[y].resize(_Count.X);;
	}




}

FVector2D ATileMap::IndexToTileLocation(FIntPoint _Index)
{
	return FVector2D(_Index.X * TileSize.X, _Index.Y * TileSize.Y);
}

FIntPoint ATileMap::LocationToIndex(FVector2D _Location)
{
	FVector2D Location = _Location / TileSize;

	return FIntPoint(Location.iX(), Location.iY());
}

// ���콺 ��ġ�� �÷��̾� ��ġ�� ��������.
void ATileMap::SetTileLocation(FVector2D _Location, int _SpriteIndex)
{
	FIntPoint Point = LocationToIndex(_Location);

	if (true == IsIndexOver(Point))
	{
		return;
	}

	SetTileIndex(Point, _SpriteIndex);
}

bool ATileMap::IsIndexOver(FIntPoint _Index)
{
	if (0 > _Index.X)
	{
		return true;
	}

	if (0 > _Index.Y)
	{
		return true;
	}

	if (TileCount.X - 1 < _Index.X)
	{
		return true;
	}

	if (TileCount.Y - 1 < _Index.Y)
	{
		return true;
	}

	return false;
}

void ATileMap::SetTileIndex(FIntPoint _Index, int _SpriteIndex)
{
	SetTileIndex(_Index, { 0,0 }, TileSize, _SpriteIndex);
}

void ATileMap::SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex)
{
	if (true == IsIndexOver(_Index))
	{
		return;
	}


	if (nullptr == AllTiles[_Index.Y][_Index.X].SpriteRenderer)
	{
		USpriteRenderer* NewSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

		NewSpriteRenderer->SetComponentScale(TileSize);
		AllTiles[_Index.Y][_Index.X].SpriteRenderer = NewSpriteRenderer;
	}


	USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
	FindSprite->SetSprite(SpriteName, _SpriteIndex);

	FVector2D TileLocation = IndexToTileLocation(_Index);
	FindSprite->SetComponentScale(_SpriteScale);

	FindSprite->SetOrder(_Index.Y);

	AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
}
