#include "PreCompile.h"
#include "TitleLogo.h"

#include <EngineCore/EngineAPICore.h>


ATitleLogo::ATitleLogo()
{

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();


}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	Super::BeginPlay();
}
void ATitleLogo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

FVector2D ATitleLogo::GetScale()
{
	return SpriteRenderer->GetComponentScale();
}


void ATitleLogo::SetSprite(std::string _SptriteName , int _Index, float _Scale)
{
	SpriteRenderer->SetSprite(_SptriteName, _Index);
	SpriteRenderer->SetSpriteScale(_Scale);
}

void ATitleLogo::SetOrder(ERenderOrder _Order)
{
	SpriteRenderer->SetOrder(_Order);

}
void ATitleLogo::SetCameraEffect(bool _Effect)
{
	SpriteRenderer->SetCameraEffect(_Effect);
}


void ATitleLogo::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	SpriteRenderer->CreateAnimation(_AnimationName, _SpriteName, _Indexs, _Frame, _Loop);
}
void ATitleLogo::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	SpriteRenderer->ChangeAnimation(_AnimationName, _Force);

}


