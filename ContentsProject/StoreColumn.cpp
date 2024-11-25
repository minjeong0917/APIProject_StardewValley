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
		ColumnSpriteRenderer->SetComponentScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
	}
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale(FVector2D{ 14 * 3.5f, 14 * 3.5f });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::SLOT);
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