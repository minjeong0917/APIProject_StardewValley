#include "PreCompile.h"
#include "Gold.h"
#include "ContentsEnum.h"

AGold::AGold()
{


	for (size_t i = 0; i < 10; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		Sprite->SetCameraEffect(false);
		Renders.push_back(Sprite);
	}

}

AGold::~AGold()
{
}

void AGold::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetSprite(TextSpriteName);
	}
}

void AGold::BeginPlay()
{

}

void AGold::Tick(float _DeltaTime)
{

}

void AGold::SetOrder(int _Order)
{
	for (size_t i = 0; i < Renders.size(); i++)
	{
		Renders[i]->SetOrder(_Order);
	}

}

void AGold::SetValue(int _Score)
{
	std::string Number = std::to_string(_Score);

	if (Renders.size() <= Number.size())
	{
		MSGASSERT("자리수를 넘겼습니다.");
		return;
	}


	FVector2D Pos = FVector2D::ZERO;

	for (int i = Number.size() - 1; i >= 0; i--)
	{
		char Value = Number[i] - '0';
		Renders[i]->SetSprite(TextSpriteName, Value);
		Renders[i]->SetComponentScale(TextScale);
		Renders[i]->SetComponentLocation(Pos);
		Pos.X -= TextScale.X + 1.6;
		Renders[i]->SetActive(true);
	}

	for (size_t i = Number.size(); i < Renders.size(); i++)
	{
		Renders[i]->SetActive(false);
	}

}