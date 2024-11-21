#include "PreCompile.h"

#include "Inventory.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AInventory::AInventory()
{
	InvenSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	InvenSpriteRenderer->SetCameraEffect(false);
	InvenSpriteRenderer->SetOrder(ERenderOrder::INVEN);
	InvenSpriteRenderer->SetSprite("Inventory2.png", 0);
	//InvenSpriteRenderer->SetComponentScale(FVector2D{ 214 * 3.5f, 74 * 3.5f });
	InvenSpriteRenderer->SetComponentScale(FVector2D{ 216 * 3.5f, 159 * 3.5f });
}

AInventory::~AInventory()
{
}

