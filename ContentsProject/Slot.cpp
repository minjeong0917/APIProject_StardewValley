#include "PreCompile.h"

#include "Slot.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/2DCollision.h>

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

void ASlot::SetOrder(ERenderOrder _RenderOder)
{
	SlotSpriteRenderer->SetOrder(_RenderOder);
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
void ASlot::SetScale(FVector2D _Scale)
{
	SlotSpriteRenderer->SetComponentScale(_Scale);
}

void ASlot::BeginPlay()
{
	Super::BeginPlay();
}

void ASlot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ASlot::CountText()
{
	Text = GetWorld()->SpawnActor<AGold>();
	Text->SetActorLocation(GetLocation() + GetScale().Half());
	Text->SetTextSpriteName("Item.png");
	Text->SetOrder(ERenderOrder::SLOTFont);
	Text->SetTextScale({ 13, 15 });
	Text->SetValue(SlotItemCount);
}

void ASlot::SetItemIndex(int _Index)
{
	ItemIndex = _Index;

}
void ASlot::SetItemSpriteName(std::string _SpriteName)
{
	ItemSpriteName = _SpriteName;
}
