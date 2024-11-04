#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class Tile
{
public:
	USpriteRenderer* SpriteRenderer;
	bool IsMove = true;
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

	void SetTile(FIntPoint _Index, int _SpriteIndex);

protected:

private:
	std::vector<std::vector<Tile>> AllTiles;
	FIntPoint TileCount;
};


