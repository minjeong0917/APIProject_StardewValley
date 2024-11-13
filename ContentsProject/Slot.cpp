#include "PreCompile.h"

#include "Slot.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
ASlot::ASlot()
{
	SlotSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SlotSpriteRenderer->SetCameraEffect(false);
	SlotSpriteRenderer->SetOrder(ERenderOrder::SLOT);

	SlotSpriteRenderer->SetComponentScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
}

ASlot::~ASlot()
{
}

void ASlot::SetSprite(std::string _SprtieName, int _SpriteIndex)
{
	SlotSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);


}