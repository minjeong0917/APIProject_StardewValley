#include "PreCompile.h"

#include "SelectedItem.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ASelectedItem::ASelectedItem()
{
	ItemSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ItemSpriteRenderer->SetCameraEffect(false);
	ItemSpriteRenderer->SetOrder(ERenderOrder::SelectedItem);
	
}


ASelectedItem::~ASelectedItem()
{
}

void ASelectedItem::SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	ItemSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	ItemSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);

}

void ASelectedItem::BeginPlay()
{
	Super::BeginPlay();
	Text = GetWorld()->SpawnActor<AGold>();
}

void ASelectedItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void ASelectedItem::CountText()
{
	Text = GetWorld()->SpawnActor<AGold>();
	Text->SetTextSpriteName("Item.png");
	Text->SetOrder(ERenderOrder::SLOTFont);
	Text->SetTextScale({ 13, 15 });
	//Text->SetValue(SlotItemCount, 1.3f);
}

void ASelectedItem::CountTextLocation(FVector2D _Loc)
{
	Text->SetActorLocation(_Loc);
}
void ASelectedItem::SetValue(int _Gold, float _Inter)
{
	Text->SetValue(_Gold, _Inter);
}