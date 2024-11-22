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

void AGold::SetValue(int _Gold)
{
    std::string Number = std::to_string(_Gold);

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

void AGold::SetText(std::string _Text)
{
    if (Renders.size() <= _Text.size())
    {
        MSGASSERT("자리수를 넘겼습니다.");
        return;
    }

    FVector2D Pos = FVector2D::ZERO;

    for (int i = 0; i < _Text.size(); i++)
    {
        char Value = _Text[i] - 'A';

        Renders[i]->SetSprite(TextSpriteName, Value);
        Renders[i]->SetComponentScale(TextScale);
        Renders[i]->SetComponentLocation(Pos);


        if (Value > 27)
        {
            Pos.X += static_cast<float>(TextScale.X - 13.0f);
        }
        else
        {
            Pos.X += static_cast<float>(TextScale.X);
        }
        Renders[i]->SetActive(true);
    }

    for (size_t i = _Text.size(); i < Renders.size(); i++)
    {
        Renders[i]->SetActive(false);
    }
}
