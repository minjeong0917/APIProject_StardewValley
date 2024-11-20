#include "PreCompile.h"
#include "TileMap.h"

#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"


ATileMap::ATileMap()
{


}

ATileMap::~ATileMap()
{
}

void ATileMap::Create(FIntPoint _Count, FVector2D _TileSize)
{
    TileSize = _TileSize;
    TileCount = _Count;

    AllTiles.resize(_Count.Y);

    for (size_t y = 0; y < AllTiles.size(); y++)
    {
        AllTiles[y].resize(_Count.X);
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


void ATileMap::SetTileLocation(std::string_view _SpriteName, FVector2D _Location, int _SpriteIndex, bool _IsMove)
{
    FVector2D TilePos = _Location - GetActorLocation();

    FIntPoint Point = LocationToIndex(TilePos);

    if (true == IsIndexOver(Point))
    {
        return;
    }

    SetTileIndex(_SpriteName, Point, _SpriteIndex, _IsMove);
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

void ATileMap::SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, int _SpriteIndex, bool _IsMove)
{
    SetTileIndex(_SpriteName, _Index, { 0,0 }, TileSize, _SpriteIndex, _IsMove);
}

void ATileMap::SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, bool _IsMove, int _MaxSpriteIndex)
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
    FindSprite->SetSprite(_SpriteName, _SpriteIndex);

    FVector2D TileLocation = IndexToTileLocation(_Index);
    FindSprite->SetComponentScale(_SpriteScale);

    FindSprite->SetOrder(_Index.Y * TileSize.Y + 1);

    AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
    AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
    AllTiles[_Index.Y][_Index.X].Scale = _SpriteScale;
    AllTiles[_Index.Y][_Index.X].SpriteIndex = _SpriteIndex;
    AllTiles[_Index.Y][_Index.X].IsMove = _IsMove;
    AllTiles[_Index.Y][_Index.X].MaxSpriteIndex = _MaxSpriteIndex;

}

Tile* ATileMap::GetTileRef(FVector2D _Location)
{
    FIntPoint Point = LocationToIndex(_Location);

    return GetTileRef(Point);
}

Tile* ATileMap::GetTileRef(FIntPoint _Index)
{
    if (true == IsIndexOver(_Index))
    {
        return nullptr;
    }

    return &AllTiles[_Index.Y][_Index.X];
}

void ATileMap::TileDestroy(FIntPoint _Index)
{
    AllTiles[_Index.Y][_Index.X].IsMove = true;
    AllTiles[_Index.Y][_Index.X].CurTime = 0.0f;
    AllTiles[_Index.Y][_Index.X].MaxSpriteIndex = 0;
    AllTiles[_Index.Y][_Index.X].Pivot = { 0,0 };
    AllTiles[_Index.Y][_Index.X].Scale = { 0,0 };
    AllTiles[_Index.Y][_Index.X].SpriteIndex = 0;
    AllTiles[_Index.Y][_Index.X].SpriteRenderer = nullptr;

}

void ATileMap::CropCheck(float _DeltaTime)
{
    for (size_t y = 0; y < AllTiles.size(); y++)
    {
        for (size_t x = 0; x < AllTiles[y].size(); x++)
        {
            if(nullptr == AllTiles[y][x].SpriteRenderer)
            {
                continue;
            }

            std::string Name = AllTiles[y][x].SpriteRenderer->GetCurSpriteName();

            int Index = AllTiles[y][x].SpriteIndex;


            AllTiles[y][x].CurTime += _DeltaTime;

            if (AllTiles[y][x].CurTime > AllTiles[y][x].Time)
            {
                if (AllTiles[y][x].SpriteIndex == AllTiles[y][x].MaxSpriteIndex)
                {
                    continue;
                }
                AllTiles[y][x].SpriteIndex = ++Index;
                AllTiles[y][x].SpriteRenderer->SetSprite(Name, Index);
                AllTiles[y][x].CurTime = 0.0f;
            }

        }
    }


}