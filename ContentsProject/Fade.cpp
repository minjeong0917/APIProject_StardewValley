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
void AFade::SetSprite(std::string _SpriteName)
{
	BackSpriteRenderer->SetSprite(_SpriteName);
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

void AFade::FadeOut(float _FadeDir)
{
	FadeValue = 1.0f;
	FadeDir = -2.0f;
	TimeEventer.PushEvent(2.0f, std::bind(&AFade::FadeChange, this), true, false);
}
void AFade::FadeInOut()
{
	FadeValue1 = 0.0f;
	FadeValue2 = 1.0f;
	FadeDir = 1.0f;

	TimeEventer.PushEvent(4.0f, std::bind(&AFade::FadeInOutChange, this), true, false);
}
void AFade::FadeInOutChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue1 += DeltaTime * 0.5F * FadeDir;
	if (0.0f <= FadeValue1 && FadeValue1 <= 1.0f)
	{
		BackSpriteRenderer->SetAlphafloat(FadeValue1);
		return;
	}
	else if (FadeValue1 >= 1.0f && FadeValue2 >= 0.0f)
	{
		FadeValue2 -= DeltaTime * 0.5F * FadeDir;
		BackSpriteRenderer->SetAlphafloat(FadeValue2);
		return;

	}
	return;


}
void AFade::LevelChangeStart()
{
	MainFade = this;
}