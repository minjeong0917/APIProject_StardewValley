#include "PreCompile.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include "InventoryBar.h"

AInventoryBar::AInventoryBar()
{
	InvenBarSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	InvenBarSpriteRenderer->SetCameraEffect(false);
	InvenBarSpriteRenderer->SetOrder(ERenderOrder::UI);
	InvenBarSpriteRenderer->SetSprite("UI", 3);
	InvenBarSpriteRenderer->SetComponentScale(FVector2D{ 203 * 3.5f, 26 * 3.5f } );

}

AInventoryBar::~AInventoryBar()
{
}

void AInventoryBar::BeginPlay()
{
	Super::BeginPlay();


}

void AInventoryBar::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
