#include "PreCompile.h"

#include "StoreColumn.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/2DCollision.h>

AStoreColumn::AStoreColumn()
{

	{
		ColumnSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ColumnSpriteRenderer->SetCameraEffect(false);
		ColumnSpriteRenderer->SetOrder(ERenderOrder::SLOT);
		ColumnSpriteRenderer->SetComponentScale(FVector2D{ 294 * 3.5f, 28 * 3.5f });
	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale(FVector2D{ 294 * 3.5f, 28 * 3.5f });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::StoreColumn);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);

		DebugOn();
	}
}

AStoreColumn::~AStoreColumn()
{
}

void AStoreColumn::BeginPlay()
{
	Super::BeginPlay();
}

void AStoreColumn::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AStoreColumn::SaveItemInfo(std::string _SpriteName, int _Index, float _Scale)
{
	ItemIndex = _Index;
	ItemSpriteName = _SpriteName;
	ItemScale = _Scale;
}
