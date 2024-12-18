#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

class Tile
{
public:
	USpriteRenderer* SpriteRenderer = nullptr;
	bool IsMove = true;
	int TileType = -1;
	FVector2D Scale;
	FVector2D Pivot;
	int SpriteIndex = 0;
	int MaxSpriteIndex = 0;
	
	int TreeCount = 1;

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
	void SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, bool _IsMove = true, int _MaxSpriteIndex=0, int TreeCount = 1);
	void TileDestroy(FIntPoint _Index);

	Tile* GetTileRef(FIntPoint _Index);
	Tile* GetTileRef(FVector2D _Location);

	FVector2D IndexToTileLocation(FIntPoint _Index);

	FIntPoint LocationToIndex(FVector2D _Location);

	bool IsIndexOver(FIntPoint _Index);
	float GetTileCurTime(FIntPoint _Index);

	int GetTileMaxIndex(FIntPoint _Index);

	void SetTileCurTime(FIntPoint _Index, float _Time);
	float GetTileTime(FIntPoint _Index);
	void SetTileSprite(FIntPoint _Index, std::string _SpriteName, int _ItemIndex);
	void SetTileIndex(FIntPoint _Index, int _ItemIndex);
	void SetTilePivot(FIntPoint _Index, FVector2D _Pivot);
	
	void CreateTileAnimation(FIntPoint _Index, std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time =0.1f, bool _Loop = true);
	void ChangeTileAnimation(FIntPoint _Index, std::string_view _AnimationName, bool _Force = false);
	void CreateTileAnimation(FIntPoint _Index, std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);

	int GetTreeTileCount(FIntPoint _Index);
	void SetTreeTileCount(FIntPoint _Index, int _Count);
	void SetTileOrder(FIntPoint _Index, float _Order);
	bool IsAniEnd(FIntPoint _Index);

	void CropCheck(float _DeltaTime);
	std::string GetTileSpriteName(FIntPoint _Index);
	int GetTileIndex(FIntPoint _Index);
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


