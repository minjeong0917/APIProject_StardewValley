#include "PreCompile.h"

#include "UI.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>


AUI::AUI()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetCameraEffect(false);
	SpriteRenderer->SetOrder(ERenderOrder::UI);

	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetCollisionGroup(ECollisionGroup::UI);
		CollisionComponent->SetCollisionType(ECollisionType::Rect);
		CollisionComponent->SetCameraEffect(false);


	}
	DebugOn();

	CollisionComponent->SetCollisionEnter(std::bind(&AUI::CollisionEnter, this, std::placeholders::_1));
	CollisionComponent->SetCollisionEnd(std::bind(&AUI::CollisionEnd, this, std::placeholders::_1));
	CollisionComponent->SetCollisionStay(std::bind(&AUI::CollisionStay, this, std::placeholders::_1));
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

void AUI::CollisionEnter(AActor* _ColActor)
{
	IsCollisionEnter = true;
	IsCollisionEnd = false;
	IsClick = true;
}

void AUI::CollisionEnd(AActor* _ColActor)
{
	IsCollisionEnd = true;
	IsCollisionEnter = false;
	IsCollisionStay = false;

	IsClick = false;

}

void AUI::CollisionStay(AActor* _ColActor)
{
	IsCollisionStay = true;



}


void AUI::SetCollisionActive(bool _IsActive)
{
	CollisionComponent->SetActive(_IsActive);
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

void AUI::SetPivotType(PivotType _Type)
{
	SpriteRenderer->SetPivotType(_Type);

}

void AUI::SetPivot(FVector2D _Pivot)
{
	SpriteRenderer->SetPivot(_Pivot);
}

void AUI::SetComponentScale(FVector2D _Scale)
{
	SpriteRenderer->SetComponentScale(_Scale);
	Scale = _Scale;
}

void AUI::SetCollisionComponentLocation(FVector2D _Location)
{
	CollisionComponent->SetComponentLocation(_Location);
}

void AUI::SetCollisionComponentScale(FVector2D _Scale)
{
	CollisionComponent->SetComponentScale(_Scale);
}
FVector2D AUI::GetLocation()
{
	Location = SpriteRenderer->GetComponentLocation();
	return Location;
}

void AUI::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop /*= true*/)
{
	SpriteRenderer->CreateAnimation(_AnimationName, _SpriteName, _Indexs, _Frame, _Loop);
}
void AUI::ChangeAnimation(std::string_view _AnimationName, bool _Force /*= false*/)
{
	SpriteRenderer->ChangeAnimation(_AnimationName, _Force);

}
