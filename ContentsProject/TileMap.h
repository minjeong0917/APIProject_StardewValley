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
	int SpriteIndex = 0;
	int MaxSpriteIndex = 0;

	float Time = 72000;
	float CurTime = 0.0f;


	std::string GetSpriteName() const
	{
		if (SpriteRenderer != nullptr)
		{
			return SpriteRenderer->GetCurSpriteName();
		}
		return "NONE";
	}

	void TileSpriteAlpha(float _alpha) const
	{
		SpriteRenderer->SetAlphafloat(_alpha);
	}

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

	void Create(FIntPoint _Count, FVector2D _TileSize);

	void SetTileLocation(std::string_view _SpriteName, FVector2D _Location, int _SpriteIndexool, bool _IsMove = true);

	void SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, int _SpriteIndex, bool _IsMove = true);
	void SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, bool _IsMove = true, int _MaxSpriteIndex=0);
	void TileDestroy(FIntPoint _Index);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);


	void CropCheck(float _DeltaTime);

	FVector2D GetTileSize()
	{
		return TileSize;
	}
protected:

private:
	std::vector<std::vector<Tile>> AllTiles;

	FIntPoint TileCount;
	FVector2D TileSize;
};


