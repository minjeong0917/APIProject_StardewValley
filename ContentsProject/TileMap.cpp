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

void ATileMap::SetTileIndex(std::string_view _SpriteName, FIntPoint _Index, FVector2D _Pivot, FVector2D _SpriteScale, int _SpriteIndex, bool _IsMove, int _MaxSpriteIndex, int TreeCount)
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
    AllTiles[_Index.Y][_Index.X].TreeCount = TreeCount;

}
void ATileMap::SetTileOrder(FIntPoint _Index, float _Order)
{
    USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
    FindSprite->SetOrder(_Order);
}

void ATileMap::CreateTileAnimation(FIntPoint _Index, std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time /*= 0.1f*/, bool _Loop /*= true*/)
{
    USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
    FindSprite->CreateAnimation(_AnimationName, _SpriteName, _Start, _End, Time,  _Loop );
}
void ATileMap::ChangeTileAnimation(FIntPoint _Index, std::string_view _AnimationName, bool _Force /*= false*/)
{
    USpriteRenderer* FindSprite = AllTiles[_Index.Y][_Index.X].SpriteRenderer;
    FindSprite->ChangeAnimation(_AnimationName, _Force);
}

void ATileMap::SetTilePivot(FIntPoint _Index, FVector2D _Pivot)
{
    if (AllTiles[_Index.Y][_Index.X].SpriteRenderer == nullptr)
    {
        return;
    }
    FVector2D TileLocation = IndexToTileLocation(_Index);
    AllTiles[_Index.Y][_Index.X].Pivot = _Pivot;
    AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetComponentLocation(TileLocation + TileSize.Half() + _Pivot);
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
    AllTiles[_Index.Y][_Index.X].TreeCount = 5;

}

std::string ATileMap::GetTileSpriteName(FIntPoint _Index)
{
    std::string Name = AllTiles[_Index.Y][_Index.X].SpriteRenderer->GetCurSpriteName();
    return Name;
}

int ATileMap::GetTileIndex(FIntPoint _Index)
{
    int Index = AllTiles[_Index.Y][_Index.X].SpriteIndex;
    return Index;
}

int ATileMap::GetTileMaxIndex(FIntPoint _Index)
{
    int Index = AllTiles[_Index.Y][_Index.X].MaxSpriteIndex;
    return Index;
}

float ATileMap::GetTileCurTime(FIntPoint _Index)
{
    float CurTime = AllTiles[_Index.Y][_Index.X].CurTime;
    return CurTime;
}


void ATileMap::SetTileCurTime(FIntPoint _Index, float _Time)
{
    AllTiles[_Index.Y][_Index.X].CurTime = _Time;
}

float ATileMap::GetTileTime(FIntPoint _Index)
{
    return AllTiles[_Index.Y][_Index.X].Time;
}
int ATileMap::GetTreeTileCount(FIntPoint _Index)
{
    return AllTiles[_Index.Y][_Index.X].TreeCount;
}
void ATileMap::SetTreeTileCount(FIntPoint _Index, int _Count)
{
    AllTiles[_Index.Y][_Index.X].TreeCount = _Count;
}
void ATileMap::SetTileSprite(FIntPoint _Index, std::string _SpriteName, int _ItemIndex)
{
    AllTiles[_Index.Y][_Index.X].SpriteRenderer->SetSprite(_SpriteName, _ItemIndex);
}

void ATileMap::SetTileIndex(FIntPoint _Index, int _ItemIndex)
{
        AllTiles[_Index.Y][_Index.X].SpriteIndex = _ItemIndex;
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