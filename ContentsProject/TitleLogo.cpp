#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

ATitleLogo::ATitleLogo()
{

	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("Logo.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation(Size.Half());

}

ATitleLogo::~ATitleLogo()
{
}

