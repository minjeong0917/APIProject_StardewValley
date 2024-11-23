#include "PreCompile.h"
#include "Gold.h"
#include "ContentsEnum.h"

AGold::AGold()
{
    for (size_t i = 0; i < 200; i++)
    {
        Sprite = CreateDefaultSubObject<USpriteRenderer>();
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

        //MSGASSERT("자리수를 넘겼습니다.");
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
    int IsTextOver = 1;
    if (Renders.size() <= _Text.size())
    {
        for (size_t i = 0; i < _Text.size() - Renders.size(); i++)
        {
            Renders.push_back(Sprite);
        }
        return;
    }

    FVector2D Pos = FVector2D::ZERO;

    for (int i = 0; i < _Text.size(); i++)
    {
        char Value = _Text[i] - 'A';

        if (Value <= -20 )
        {
            Value = 29;
        }
        else if (Value > -20 && Value <0)
        {
            Value = 26;
        }

        Renders[i]->SetSprite(TextSpriteName, Value);
        Renders[i]->SetComponentScale(TextScale);
        Renders[i]->SetComponentLocation(Pos);

        if (Value == 'm' - 'A')
        {
            Pos.X += static_cast<float>(TextScale.X);
        }
        else if (Value > 27)
        {
            Pos.X += static_cast<float>(TextScale.X - 10.0f);
        }
        else if (Value == 26)
        {
            Pos.X += static_cast<float>(TextScale.X - 20.0f);
        }
        else
        {
            Pos.X += static_cast<float>(TextScale.X);
        }

        if (Pos.X > 245 && Value == 29)
        {

            Pos.X = 5;
            Pos.Y += TextScale.Y;
            IsTextOver +=1;
        }

        Renders[i]->SetActive(true);
    }

    for (size_t i = _Text.size(); i < Renders.size(); i++)
    {
        Renders[i]->SetActive(false);
    }

    TextOverCount = IsTextOver;
}
