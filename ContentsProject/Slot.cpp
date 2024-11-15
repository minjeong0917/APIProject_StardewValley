#include "PreCompile.h"

#include "Slot.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

#include "ContentsEnum.h"
ASlot::ASlot()
{
	SlotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SlotSpriteRenderer->SetCameraEffect(false);
	SlotSpriteRenderer->SetOrder(ERenderOrder::SLOT);
	SlotSpriteRenderer->SetComponentScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });

	{


		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::SLOT);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);

		DebugOn();
	}

}

ASlot::~ASlot()
{
}

void ASlot::SetSprite(std::string _SprtieName, int _SpriteIndex)
{
	SlotSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
}

void ASlot::SetComponentLocation(FVector2D _Location)
{
	SlotSpriteRenderer->SetComponentLocation(_Location);
}
void ASlot::SetColisionLocation(FVector2D _Location)
{
	CollisionComponent->SetComponentLocation(_Location);

}


void ASlot::BeginPlay()
{
	Super::BeginPlay();
}

void ASlot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}