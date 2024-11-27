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

void AText::SetValue(int _Text)
{

	std::string Number = std::to_string(_Text);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}

	FVector2D Pos = FVector2D::ZERO;

	for (int i = static_cast<int>(Number.size() - 1); i >= 0; i--)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X -= static_cast<float>(TextScale.X + 1.6);
		Renders[i]->SetActive(true);
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}

}

void AText::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void AText::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AText::Copy(AText* _Text)
{
	TextSpriteName = _Text->TextSpriteName;
	TextScale = _Text->TextScale;
	SetSprite(_Text->TextSpriteRenderer->GetCurSpriteName(), _Text->TextSpriteRenderer->GetCurIndex(), 1.0f);
}