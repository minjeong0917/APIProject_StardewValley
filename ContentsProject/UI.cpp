#include "PreCompile.h"

#include "UI.h"
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

AUI::AUI()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetCameraEffect(false);
	SpriteRenderer->SetOrder(ERenderOrder::UI);

}

AUI::~AUI()
{
}

void AUI::BeginPlay()
{
	Super::BeginPlay();
}

void AUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AUI::SetSprite(std::string _SpriteName, int _Index, float _Scale)
{
	SpriteRenderer->SetSprite(_SpriteName, _Index);
	SpriteRenderer->SetSpriteScale(_Scale);
}

void AUI::SetOrder(ERenderOrder _Order)
{
	SpriteRenderer->SetOrder(_Order);

}

void AUI::SetComponentScale(FVector2D _Scale)
{
	SpriteRenderer->SetComponentScale(_Scale);
	Scale = _Scale;
}

void AUI::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	SpriteRenderer->CreateAnimation(_AnimationName, _SpriteName, _Indexs, _Frame, _Loop);
}
void AUI::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	SpriteRenderer->ChangeAnimation(_AnimationName, _Force);

}
