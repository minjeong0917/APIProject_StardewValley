#include "PreCompile.h"
#include "FarmMap.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

AFarmMap::AFarmMap()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("Farm.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());

}

AFarmMap::~AFarmMap()
{
}

