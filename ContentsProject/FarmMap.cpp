#include "PreCompile.h"
#include "FarmMap.h"
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

AFarmMap::AFarmMap()
{
	{

		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("farm.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}

	{

		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::COLMAP);
		SpriteRenderer->SetSprite("farm_col.png");

		FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}


}


AFarmMap::~AFarmMap()
{
}

void AFarmMap::BeginPlay()
{
	Super::BeginPlay();
}

void AFarmMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AFarmMap::SetSprite(std::string _SpriteName)
{
	SpriteRenderer->SetSprite(_SpriteName);

}

