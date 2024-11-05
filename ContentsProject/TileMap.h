#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class Tile
{
public:
	USpriteRenderer* SpriteRenderer;
	bool IsMove = true;
	int TileType = -1;
	FVector2D Scale;
	FVector2D Pivot;
};


class ATileMap : public AActor
{
public:
	// constrcuter destructer
	ATileMap();
	~ATileMap();

	// delete Function
	ATileMap(const ATileMap& _Other) = delete;
	ATileMap(ATileMap&& _Other) noexcept = delete;
	ATileMap& operator=(const ATileMap& _Other) = delete;
	ATileMap& operator=(ATileMap&& _Other) noexcept = delete;

	void Create(std::string_view _Sprite, FIntPoint _Count, FVector2D _TileSize);

	void SetTileLocation(FVector2D _Location, int _SpriteIndex);

	void SetTileIndex(FIntPoint _Index, int _SpriteIndex);
	void SetTileIndex(FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex);


	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);

protected:

private:
	std::vector<std::vector<Tile>> AllTiles;
	FIntPoint TileCount;
	std::string SpriteName;
	FVector2D TileSize;
};


