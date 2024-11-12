#include "PreCompile.h"

#include "Text.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
AText::AText()
{
	TextSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	TextSpriteRenderer->SetCameraEffect(false);
	TextSpriteRenderer->SetOrder(ERenderOrder::UIFont);
}

AText::~AText()
{

}

void AText::BeginPlay()
{
	Super::BeginPlay();
}

void AText::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AText::SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale)
{
	TextSpriteRenderer->SetSprite(_SprtieName, _SpriteIndex);
	TextSpriteRenderer->SetSpriteScale(_Scale, _SpriteIndex);
}