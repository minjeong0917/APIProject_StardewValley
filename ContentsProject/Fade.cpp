#include "PreCompile.h"
#include "Fade.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>


AFade* AFade::MainFade = nullptr;

AFade::AFade()
{
	BackSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();

	BackSpriteRenderer->SetSprite("Fade.png");
	FVector2D MapScale = BackSpriteRenderer->SetSpriteScale(1.0f);
	BackSpriteRenderer->SetComponentLocation(MapScale.Half());
	BackSpriteRenderer->SetCameraEffect(false);
	// BackSpriteRenderer->SetAlphaChar(200);
}

AFade::~AFade()
{
}

void AFade::SetOrder(ERenderOrder _Order)
{
	BackSpriteRenderer->SetOrder(_Order);
}

void AFade::SetAlphaChar(float _Alpha)
{
	BackSpriteRenderer->SetAlphaChar(_Alpha);
}

void AFade::FadeChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 0.5F * FadeDir;
	BackSpriteRenderer->SetAlphafloat(FadeValue);

}

void AFade::FadeIn()
{
	FadeValue = 0.0f;
	FadeDir = 1.0f;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}

void AFade::FadeOut()
{
	FadeValue = 1.0f;
	FadeDir = -1.0f;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}

void AFade::LevelChangeStart()
{
	MainFade = this;
}